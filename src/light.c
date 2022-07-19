/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:16 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/16 18:11:35 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	is_shadowed(t_comps *comps, t_light *light, t_poly *poly)
{
	t_coo	*path;
	double	distance;
	t_ray	*rc;
	t_intersec	*hit;
	t_caster	*intersec;
	int	result;

	path = vector_subtration(light->posi, comps->over_point);
	distance = vector_abs(path, path);
	rc = create_ray(comps->over_point, vector_normalize(path));
	intersec = (t_caster *)malloc(sizeof(t_caster));
	intersec = init_intersec_list(intersec);

	all_sphere_intersec(intersec, rc, poly);
	all_plane_intersec(intersec, rc, poly);
	all_cylinder_intersec(intersec, rc, poly);
	hit = hiter_point(intersec);
	if (hit && hit->t < distance)
		result = 1;
	else
		result = 0;
	return (result);
}

static void	set_light_params(t_comps *args, t_ltparams *params, t_light *lt)
{
	params->effective_color = vector_multipli(args->material->color,
	lt->intensity);
	params->light_v = vector_normalize(vector_subtration(lt->posi, args->over_point));
	params->ambient = vector_multipli_scalar(args->material->ambient, params->effective_color);
	params->light_dot_normal = vector_abs(args->normal_vec, params->light_v);
}

t_coo	*lighting(t_comps args, t_light *current_light, int in_shadow)
{
	t_ltparams	params;

	set_light_params(&args, &params, current_light);
	if (params.light_dot_normal < 0 || in_shadow == 1)
	{
		params.diffuse = create_vector(0, 0, 0, 0);
		params.specular = create_vector(0, 0, 0, 0);
	}
	else
	{
		params.diffuse = vector_multipli_scalar(args.material->diffuse * params.light_dot_normal,
			params.effective_color);
		params.reflect_v = reflect(vector_multipli_scalar(-1, params.light_v),
			args.normal_vec);
		params.reflect_dot_eye = vector_abs(params.reflect_v, args.eye_vec);
		if (params.reflect_dot_eye <= 0)
			params.specular = create_vector(0, 0, 0, 0);
		else
			params.specular = vector_multipli_scalar(args.material->specular *
			(pow(params.reflect_dot_eye, args.material->shininess)), current_light->intensity);
	}
	return (vector_addition(
	vector_addition(params.diffuse, params.ambient), params.specular));
}

t_coo	*slighting(t_coo *position, t_light *light, t_coo *eye, t_material *material, t_coo *normal, int is_shadow)
{
	t_coo	*temp = material->color;
	t_coo	*effectivecolor = vector_multipli(temp, light->intensity);
	t_coo	*lightvec = vector_normalize(vector_subtration(light->posi, position));
	t_coo	*ambienteColor = vector_multipli_scalar(material->ambient, temp);
	t_coo	*difusecolor;
	t_coo	*specularcolor;

	double	lDOtn = vector_abs(lightvec, normal);
	if (lDOtn <= 0.0 || is_shadow)
	{
		difusecolor = create_vector(0.0, 0.0, 0.0, 0.0);
		specularcolor = create_vector(0.0, 0.0, 0.0, 0.0);
	}
	else
	{
		difusecolor = vector_multipli_scalar(lDOtn, vector_multipli_scalar(material->diffuse, effectivecolor));
		t_coo	*refle = reflect(vector_multipli_scalar(-1.0, lightvec), normal);
		double	rDote = vector_abs(refle, eye);
		if (rDote <= 0.0)
			specularcolor = create_vector(0.0, 0.0, 0.0, 0.0);
		else
		{
			//Shinniness ou Brilho e depois do rDote
			double	factor = pow(rDote, 200.0);
			specularcolor = vector_multipli_scalar(material->specular * factor, light->intensity);
		}
	}
	return vector_addition(vector_addition(ambienteColor, specularcolor), difusecolor);
}
