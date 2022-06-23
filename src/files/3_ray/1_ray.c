/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 23:22:42 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/22 23:49:58 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*ray_direction(double *wall, double w_size, double *cam, int x, int y)
{
	t_ray	*ray = (t_ray *)malloc(sizeof(t_ray));

	ray->direction = find_direction(wall, w_size, cam, x, y);
	ray->origin = cam;
	return (ray);
}