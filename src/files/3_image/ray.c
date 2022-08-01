/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 20:52:13 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 23:08:34 by algabrie         ###   ########.fr       */
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
	t_coo			direction;
	t_coo			temp;
	t_coo			matrix;
	const double	x_offset = (x + 0.5) * cam->pixel_size;
	const double	y_offset = (y + 0.5) * cam->pixel_size;

	temp = create_vector_temp(cam->half_width - x_offset,
			cam->half_height - y_offset, -1, 1);
	matrix = mult_matrix_vector_temp(cam->transform, &temp);
	temp = vector_subtraction_temp(&matrix, &cam->origin);
	direction = vector_normalize_temp(&temp);
	return (create_ray(&cam->origin, &direction));
}

t_coo	mult_matrix_vector_temp(double **m1, t_coo *t1);

t_ray	ray_to_object_space(t_ray *ray, double **matrix)
{
	t_ray	res;

	res.inverse = matrix_inverter(matrix);
	res.origin = mult_matrix_vector_temp(res.inverse, &ray->origin);
	res.direction = mult_matrix_vector_temp(res.inverse, &ray->direction);
	return (res);
}
