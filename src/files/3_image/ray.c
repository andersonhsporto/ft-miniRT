/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:52:13 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/16 03:07:55 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*create_ray(t_coo *origin, t_coo *direction)
{
	t_ray	*new;

	new = (t_ray *)malloc(sizeof(t_ray));
	new->origin = origin;
	new->direction = direction;
	return (new);
}

t_ray	*ray_for_pixel(t_cam_d *temp, int x, int y)
{
	const double	x_offset = (x + 0.5) * temp->pixel_size;
	const double	y_offset = (y + 0.5) * temp->pixel_size;
	t_coo			*direction;
	t_coo			*test;

	test = create_vector(temp->half_width - x_offset, \
						temp->half_height - y_offset, -1, 1);
	direction = vector_normalize(\
				vector_subtration(\
				mult_matrix_vector(temp->transform, test), temp->origin));
	return (create_ray(temp->origin, direction));
}

t_ray	*ray_to_object_space(t_ray *ray, double **matrix)
{
	t_ray	*res;
	double	**inverse;

	res = (t_ray *)malloc(sizeof(t_ray));
	inverse = matrix_inverter(matrix);
	res->origin = mult_matrix_vector(inverse, ray->origin);
	res->direction = mult_matrix_vector(inverse, ray->direction);
	return (res);
}

