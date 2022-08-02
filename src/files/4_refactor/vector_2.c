/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:02:57 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/02 01:29:01 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coo	get_cylinder_normal_temp(double height, t_coo *o_point)
{
	double	dist;
	double	min;
	double	max;

	max = height / 2.0;
	min = -1.0 * max;
	dist = pow(o_point->x, 2) + pow(o_point->z, 2);
	if (dist < 1 && (o_point->y >= max - EPSILON))
		return (create_vector_temp(0, 1, 0, 0));
	else if (dist < 1 && (o_point->y <= min + EPSILON))
		return (create_vector_temp(0, -1, 0, 0));
	else
		return (create_vector_temp(o_point->x, 0, o_point->z, 0));
}

t_coo	normal_object_type_temp(t_coo o_point, double *obj_type_height)
{
	t_coo	temp;

	temp = create_vector_temp(0, 0, 0, 1);
	if (obj_type_height[0] == sphere)
		return (vector_subtraction_temp(&o_point, &temp));
	else if (obj_type_height[0] == plane)
		return (create_vector_temp(0, 1, 0, 0));
	else if (obj_type_height[0] == cylinder)
		return (get_cylinder_normal_temp(obj_type_height[1], &o_point));
	return (create_vector_temp(0, 0, 0, 0));
}
