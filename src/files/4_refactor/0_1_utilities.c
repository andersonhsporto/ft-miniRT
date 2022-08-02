/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_1_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:05:05 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/02 01:11:15 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	ray_position(t_ray *ray, double t)
{
	t_coo	temp;

	temp = vector_multipli_scalar_temp(t, &ray->direction);
	return (vector_addition_temp(&ray->origin, &temp));
}

t_coo	*reflect(t_coo *v, t_coo *n)
{
	t_coo	*var;
	t_coo	*res;

	var = vector_multipli_scalar(2.0 * vector_abs(v, n), n);
	res = vector_subtraction(v, var);
	free(var);
	return (res);
}

t_caster	*init_intersec_list(void)
{
	t_caster	*list;

	list = (t_caster *)malloc(sizeof(t_caster) * 1);
	list->cont = 0;
	list->intersec = NULL;
	return (list);
}

void	prepare_computations(t_comps *comps, t_ray *rt, t_mini *data)
{
	t_coo	*scalar;

	comps->t = data->hit->t;
	comps->position = ray_position(rt, comps->t);
	comps->eye_vec = vector_multipli_scalar(-1, &rt->direction);
	get_obj_props(comps, data->hit->obj_type, data->hit->obj_pos, data);
	if (vector_abs(comps->normal_vec, comps->eye_vec) < 0)
	{
		comps->inside = 1;
		comps->normal_vec = vector_multipli_scalar(-1, comps->normal_vec);
	}
	else
		comps->inside = 0;
	scalar = vector_multipli_scalar(EPSILON, comps->normal_vec);
	comps->over_point = vector_addition(&comps->position, scalar);
	free(scalar);
	free(data->hit);
}
