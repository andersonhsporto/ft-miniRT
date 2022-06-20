/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:03 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/19 19:55:23 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*sphere_intersection(t_ray *rayy, t_obj_d *obj)
{
	t_intersec	*intersectionPoints = NULL;
	t_ray		*ray = ray_to_object_space(rayy, obj->matrix);
	//position
	double *oc = vector_subtraction(ray->origin, obj->position);
	double	a = vector_abs(ray->direction, ray->direction);
	double	b = 2.0 * vector_abs(oc, ray->direction);
	double	c = vector_abs(oc, oc) - (obj->radius * obj->radius);
	double	discriminant = (b * b)-(4 * a * c);
	free(oc);
	if (discriminant < 0)
	{
		return (intersectionPoints);
	}
	intersectionPoints = (t_intersec *)malloc(sizeof(t_intersec));
	double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	intersectionPoints->t1 = t1;
	intersectionPoints->t2 = t2;
	intersectionPoints->cont = 3;
	return intersectionPoints;
}
