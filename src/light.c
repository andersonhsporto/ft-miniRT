/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:16 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/07 11:03:42 by algabrie         ###   ########.fr       */
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
	//intersec = plane_intersection(rc, comps->obj);
	hit = hiter_point(intersec);
	if (hit && hit->t < distance)
		result = 0;
	else
		result = 1;
	return (result);
}

static void	set_light_params(t_comps *args, t_ltparams *params, t_light *lt)
{
	params->effective_color = vector_multipli(args->material->color,
	lt->intensity);
	params->light_v = vector_normalize(vector_subtration(args->over_point, lt->posi));
	params->ambient = vector_multipli_scalar(args->material->ambient, params->effective_color);
	params->light_dot_normal = vector_abs(params->light_v, args->normal_vec);
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
		params.diffuse = vector_multipli_scalar((args.material->diffuse * params.light_dot_normal),
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
	vector_addition(params.diffuse, params.specular), params.ambient));
}
