/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_object.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:02:27 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 01:24:19 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_re	*hiter_seine_object(t_ray_re *ray, t_scene_re *scene)
{
	t_intersec_re	*intersection;
	t_hit_re		*hiter;
	int				i;

	i = 0;
	hiter = NULL;
	while (i < scene->cont)
	{
		if (scene->object[i]->type == 'C')
		{
			intersection = cylinder_intersection(ray, scene->object[i]);
			hiter = hiter_point(intersection);
			if (hiter)
				return(hiter);
		}
		if(scene->object[i]->type == 'S')
		{
			intersection = sphere_intersection(ray, scene->object[i]);
			hiter = hiter_point(intersection);
			if (hiter)
				return(hiter);
		}
		if(scene->object[i]->type == 'P')
		{
			intersection = plane_intersection(ray);
			hiter = hiter_point(intersection);
			if (hiter)
				return(hiter);
		}
		i++;
	}
	return (hiter);
}

t_intersec_re	*cylinder_intersection(t_ray_re*ray, t_obj_re *obj)
{
	t_intersec_re	*intersectionPoints = NULL;

	double *oc = vector_subtraction(ray->origin, obj->position);
	double	a = ray->direction[0] * ray->direction[0] + ray->direction[2] * ray->direction[2];
	double	b = 2.0 * oc[0] * ray->direction[0] + 2.0 * oc[2] * ray->direction[2];

	double	c = oc[0] * oc[0] + oc[2] * oc[2] - obj->radius;
	double	discriminant = (b*b)-(4*a*c);
	if (discriminant < 0)
		return intersectionPoints;
	intersectionPoints = (t_intersec_re *)malloc(sizeof(t_intersec_re));
	intersectionPoints->cont = 0;
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
		intersectionPoints->cont = 2;
		intersectionPoints->t1 = t0;
	}
	double	y1 = oc[1] + t1 * ray->direction[1];
	if (min < y1 && y1 < max)
	{
		intersectionPoints->cont++;
		intersectionPoints->t2 = t1;
	}
	return intersectionPoints;
}


t_intersec_re	*sphere_intersection(t_ray_re *rayy, t_obj_re *obj)
{
	t_intersec_re	*intersectionPoints = NULL;
	t_ray_re *ray = ray_to_object_space(rayy, obj->matrix);
	//position
	double *oc = vector_subtraction(ray->origin, obj->position);
	double	a = vector_abs(ray->direction, ray->direction);
	double	b = 2.0 * vector_abs(oc, ray->direction);
	double	c = vector_abs(oc, oc) - (obj->radius * obj->radius);
	double	discriminant = (b*b)-(4*a*c);
	free(oc);
	if (discriminant < 0)
	{
		return intersectionPoints;
	}
	intersectionPoints = (t_intersec_re *)malloc(sizeof(t_intersec_re));
	double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	intersectionPoints->t1 = t1;
	intersectionPoints->t2 = t2;
	intersectionPoints->cont = 3;
	return intersectionPoints;
}

t_hit_re	*hiter_point(t_intersec_re *intersections)
{
	t_hit_re	*first = NULL;
	if(intersections == NULL)
		return (NULL);
	else
	{
		if ((intersections->cont == 2 || intersections->cont == 3) && !(intersections->t1 < 0.0))
		{
			first = (t_hit_re *)malloc(sizeof(t_hit_re));
			first->t = intersections->t1;
			return (first);
		}
		if ((intersections->cont == 1 || intersections->cont == 3) && !(intersections->t2 < 0.0))
		{
			first = (t_hit_re *)malloc(sizeof(t_hit_re));
			first->t = intersections->t2;
			return (first);
		}
	}
	return (first);
}

t_intersec_re	*plane_intersection(t_ray_re *ray)
{
	t_intersec_re	*intersectionPoints = NULL;
	if (ray->direction[1] < 0.001)
		return intersectionPoints;
	intersectionPoints = (t_intersec_re *)malloc(sizeof(t_intersec_re));
	intersectionPoints->t1 = -ray->origin[1] / ray->direction[1];
	intersectionPoints->cont = 2;
	return intersectionPoints;
}
