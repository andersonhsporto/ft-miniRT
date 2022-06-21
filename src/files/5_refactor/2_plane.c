/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:36:37 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/21 02:13:11 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*plane_intersection(t_ray *ray)
{
	t_intersec	*intersection_points;

	if (ray->direction[1] < 0.001)
		return (NULL);
	intersection_points = (t_intersec *)malloc(sizeof(t_intersec));
	intersection_points->t1 = -ray->origin[1] / ray->direction[1];
	intersection_points->cont = 2;
	return (intersection_points);
}
