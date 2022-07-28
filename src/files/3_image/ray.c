/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:52:13 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/28 03:48:24 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	create_ray(t_coo *origin, t_coo *direction)
{
	t_ray	new;

	new.origin.x = origin->x;
	new.origin.y = origin->y;
	new.origin.z = origin->z;
	new.origin.w = origin->w;
	new.direction.x = direction->x;
	new.direction.y = direction->y;
	new.direction.z = direction->z;
	new.direction.w = direction->w;
	return (new);
}

t_ray	ray_for_pixel(t_cam_d *cam, int x, int y)
{
	const double	x_offset = (x + 0.5) * cam->pixel_size;
	const double	y_offset = (y + 0.5) * cam->pixel_size;
	t_coo			direction;
	t_coo			test;
	t_coo			temp;
	t_coo			matrix;


	test = create_vector_temp(cam->half_width - x_offset, \
						cam->half_height - y_offset, -1, 1);
	matrix = mult_matrix_vector_temp(cam->transform, &test);
	temp = vector_subtration_temp(&matrix, &cam->origin);
	direction = vector_normalize_temp(&temp);
	return (create_ray(&cam->origin, &direction));
}

t_coo	mult_matrix_vector_temp(double **m1, t_coo *t1); // add to header
t_ray	ray_to_object_space(t_ray *ray, double **matrix)
{
	t_ray	res;
	double	**inverse;

	inverse = matrix_inverter(matrix);
	res.origin = mult_matrix_vector_temp(inverse, &ray->origin);
	res.direction = mult_matrix_vector_temp(inverse, &ray->direction);
	free_matrix(inverse, 4);
	return (res);
}
