/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:57:08 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/09 00:27:39 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_utils	get_discriminant(t_mini *data, t_sphere *ptr)
{
	t_utils utils;

	utils.a = sum_square_vector(data->ray.direction);
	// printf("a: %f\n", utils.a);
	utils.b = vector_dot(vector_sub(data->ray.origin, ptr->center), \
	data->ray.direction);
	utils.c = sum_square_vector(vector_sub( \
			data->ray.origin, ptr->center)) - pow(ptr->diameter, 2);
	utils.discriminant = pow(utils.b, 2) - (utils.a * utils.c);
	utils.root = (-utils.b - sqrt(utils.discriminant)) / utils.a;
	return (utils);
}

int	hit_sphere(t_mini *data, t_sphere *ptr)
{
	t_utils utils;

	utils = get_discriminant(data, ptr);
    if (utils.discriminant < 0)
    {
        return (0);
    }
	if (utils.root < data->hit_record.min || utils.root > data->hit_record.max)
		return (0);
	else
	{
		data->hit_record.t = utils.root;
		data->hit_record.p = ray_in(data->ray, data->hit_record.t);
		data->hit_record.normal = vector_normalize( \
			vector_sub(data->hit_record.p, ptr->center));
		return (1);
	}
}