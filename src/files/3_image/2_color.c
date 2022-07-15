/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:22:47 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/10 23:58:00 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit(t_mini *data);

t_vector	get_ray_direction(double x, double y, t_mini *data)
{
	t_vector	direction;
	t_vector	temp;

	temp = vector_sum(data->cam->lower_left_corner, \
							vector_mult(data->cam->horizontal, x));
	// print_vector("1: ", temp);
	temp = vector_sum(temp, vector_mult(data->cam->vertical, y));
	// printf("x %f y %f\n", x, y);
	// print_vector("1.5: ", vector_mult(data->cam->vertical, y));
	// print_vector("2: ", temp);
	temp = vector_sub(temp, data->cam->view_point);
	direction = unit_vector(temp);
	return (direction);
}

t_vector	ray_in(t_ray ray, double t)
{
	t_vector	vector;

	vector = vector_sum(ray.origin, vector_mult(ray.direction, t));
	return (vector);
}

void	get_ray(int x, int y, t_mini *data)
{
    double j = (double) x / HEIGHT;
    double u = (double) y / WIDTH;
	data->ray.origin = data->cam->view_point;
	data->ray.direction = get_ray_direction(u, j, data);
	// printf("\n%f %f \n", u, j);
	// print_vector("ray.origin", data->ray.origin);
	// print_vector("ray.direction", data->ray.direction);
}

t_vector	get_colors(int x, int y, t_mini *data)
{
	get_ray(x, y, data);

	data->hit_record.min = 1e-6;
	data->hit_record.max = INFINITY;
	if (hit(data))
		return (vector_new(0, 0, 255));
	return (vector_new(255, 0, 0));
}