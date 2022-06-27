/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:03 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/26 22:51:40 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sphere_discriminant(t_ray *ray, double *oc, t_sphere *lst)
{
	const double	a = vector_abs(ray->direction, ray->direction);
	const double	b = 2.0 * vector_abs(oc, ray->direction);
	const double	c = vector_abs(oc, oc) - (pow(2, (lst->diameter / 2)));

	return ((pow(b, 2)) - (4.0 * a * c));
}

static t_intersec	*get_intersection(t_ray *ray, double *oc, double discriminant)
{
	const double	a = vector_abs(ray->direction, ray->direction);
	const double	b = 2.0 * vector_abs(oc, ray->direction);
	t_intersec		*intersection_points;

	intersection_points = (t_intersec *)malloc(sizeof(t_intersec));
	intersection_points->t1 = (-b - sqrt(discriminant)) / (2.0 * a);
	intersection_points->t2 = (-b + sqrt(discriminant)) / (2.0 * a);
	intersection_points->cont = 3;
	return (intersection_points);
}

t_intersec	*sphere_intersection(t_ray *rayy, t_sphere *lst)
{
	const t_ray		*ray = ray_to_object_space(rayy, matrix_identify(1,1,1,1));
	const double	*oc = vector_subtraction(ray->origin, lst->center);
	const double	discriminant = sphere_discriminant(ray, oc, lst);
	t_intersec		*intersection_points;

	if (discriminant < 0)
	{
		free((double *)oc);
		return (NULL);
	}
	intersection_points = get_intersection(ray, oc, discriminant);
	free((double *)oc);
	return (intersection_points);
}
