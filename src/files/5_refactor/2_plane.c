/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:36:37 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/19 23:36:55 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*plane_intersection(t_ray *ray)
{
	t_intersec	*intersectionPoints = NULL;
	if (ray->direction[1] < 0.001)
		return intersectionPoints;
	intersectionPoints = (t_intersec *)malloc(sizeof(t_intersec));
	intersectionPoints->t1 = -ray->origin[1] / ray->direction[1];
	intersectionPoints->cont = 2;
	return intersectionPoints;
}
