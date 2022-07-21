/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:16 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/21 00:11:12 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_shadowed(t_comps *comps, t_poly *poly, t_mini *data)
{
	t_coo		*path;
	double		distance;
	int			result;
	t_intersec	*hit;

	path = vector_subtration(data->light->point, comps->over_point); //data
	distance = vector_abs(path, path);
	hit = get_shadow_hit(comps->over_point, path, poly, data);
	if (hit && hit->t < distance)
		result = 1;
	else
		result = 0;
	return (result);
}

static void	set_light_params(t_comps *args, t_ltparams *params, t_mini *data)
{
	params->effective_color = vector_multipli(args->material->color, data->light->intensity);
	params->light_v = vector_normalize(vector_subtration(data->light->point, args->over_point));
	params->ambient = vector_multipli_scalar(args->material->ambient, params->effective_color);
	params->light_dot_normal = vector_abs(args->normal_vec, params->light_v);
}

t_coo	*lighting(t_comps args, int in_shadow, t_mini *data)
{
	t_ltparams	params;

	set_light_params(&args, &params, data);
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
			(pow(params.reflect_dot_eye, args.material->shininess)), data->light->intensity);
	}
	return (vector_addition(
	vector_addition(params.diffuse, params.specular), params.ambient));
}
