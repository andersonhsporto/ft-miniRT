/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:35:41 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/21 23:01:03 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*cylinder_intersection(t_ray *ray, t_obj_d *obj)
{
	t_intersec	*intersection_points;

	double *oc = vector_subtraction(ray->origin, obj->position);
	double	a = ray->direction[0] * ray->direction[0] + ray->direction[2] * ray->direction[2];
	double	b = 2.0 * oc[0] * ray->direction[0] + 2.0 * oc[2] * ray->direction[2];
	double	c = oc[0] * oc[0] + oc[2] * oc[2] - obj->radius;
	double	discriminant = (b * b) - (4 * a * c);

	if (discriminant < 0)
		return (NULL);
	intersection_points = (t_intersec *)malloc(sizeof(t_intersec));
	intersection_points->cont = 0;
	double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t0 > t1)
	{
		double temp = t0;
		t0 = t1;
		t1 = temp;
	}
	double	y0 = oc[1] + t0 * ray->direction[1];
	double max =  (obj->radius * obj->radius) / 2.0;
	double min = -1.0 * max;
	if (min < y0 && y0 < max)
	{
		intersection_points->cont = 2;
		intersection_points->t1 = t0;
	}
	double	y1 = oc[1] + t1 * ray->direction[1];
	if (min < y1 && y1 < max)
	{
		intersection_points->cont++;
		intersection_points->t2 = t1;
	}
	return intersection_points;
}
