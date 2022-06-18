/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:03:35 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/14 12:13:40 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_new(t_vector origin, t_vector direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_vector	ray_at(t_ray ray, double t)
{
	t_vector	multiplication;
	t_vector	sum;

	multiplication = vector_mult(ray.origin, t);
	sum = vector_sum(ray.origin, multiplication);
	return (sum);
}

t_ray	ray_image(t_mini *data, double u, double v)
{
	t_ray	ray;

	ray.origin = vector_new(data->cam->view_point.x, data->cam->view_point.y,
						data->cam->view_point.z);
	ray.direction = vector_sum(data->data_cam->lower_left_corner, vector_mult(data->data_cam->hori_dir, u));
	ray.direction = vector_sum(ray.direction, vector_mult(data->data_cam->vert_dir, v));
	ray.direction = vector_sub(ray.direction, ray.origin);
	ray.direction = unit_vector(ray.direction);

	// if (u > 0.8 && u < 0.81)
	// {
	// 	print_vector("ray origin", ray.origin);
	// 	printf("u: %f  ", u);
	// 	print_vector("hori_dir", data->data_cam->hori_dir);
	// 	print_vector("vector_mult", vector_mult(data->data_cam->hori_dir, u));
	// 	print_vector("direction", ray.direction);
	// }
	return (ray);
}