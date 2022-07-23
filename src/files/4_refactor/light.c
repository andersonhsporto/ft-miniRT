/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:16 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/23 02:37:40 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_shadowed(t_comps *comps, t_mini *data)
{
	const t_coo			*path = vector_subtration(data->light->point, \
													comps->over_point); //data
	const double		distance = vector_abs(path, path);
	const t_intersec	*hit = get_shadow_hit(comps->over_point, path, data);

	if (hit && (hit->t < distance))
	{
		free((t_intersec*)hit);
		free((t_coo*)path);
		return (1);
	}
	else
	{
		free((t_intersec*)hit);
		free((t_coo*)path);
		return (0);
	}
}

static void	set_light_params(t_comps *args, t_ltparams *params, t_mini *data)
{
	params->effective_color = vector_multipli(args->color, data->light->intensity);
	params->light_v = vector_normalize(vector_subtration(data->light->point, args->over_point));
	params->ambient = vector_multipli_scalar(data->light->ambient, params->effective_color);
	params->light_dot_normal = vector_abs(args->normal_vec, params->light_v);
}

t_coo	*norm_light(t_coo *diffuse, t_coo *specular, t_coo *ambient)
{
	const t_coo *tmp = vector_addition(diffuse, specular);
	t_coo		*rgb;

	rgb = vector_addition(tmp, ambient);
	free((t_coo*)tmp);
	free((t_coo*)diffuse);
	free((t_coo*)specular);
	free((t_coo*)ambient);
	if (rgb->x > 1)
		rgb->x = 1;
	if (rgb->y > 1)
		rgb->y = 1;
	if (rgb->z > 1)
		rgb->z = 1;
	return (rgb);
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
		params.diffuse = vector_multipli_scalar(data->light->diffuse * params.light_dot_normal,
			params.effective_color);
		params.reflect_v = reflect(vector_multipli_scalar(-1, params.light_v),
			args.normal_vec);
		params.reflect_dot_eye = vector_abs(params.reflect_v, args.eye_vec);
		if (params.reflect_dot_eye <= 0)
			params.specular = create_vector(0, 0, 0, 0);
		else
			params.specular = vector_multipli_scalar(data->light->specular *
			(pow(params.reflect_dot_eye, data->light->shininess)), data->light->intensity);
	}
	return (norm_light(params.diffuse, params.specular, params.ambient));
}
