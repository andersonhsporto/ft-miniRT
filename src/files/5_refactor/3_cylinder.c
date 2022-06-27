/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:35:41 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/27 01:44:38 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	cylinder_discriminant(t_ray *ray, t_cy *cy, t_cylinder *ptr)
{
	double	discriminant;

	cy->oc = vector_subtraction(ray->origin, ptr->coordinates);
	cy->a = pow(ray->direction[0], 2) + pow(ray->direction[2], 2);
	cy->b = 2.0 * cy->oc[0] * ray->direction[0] + 2.0 * cy->oc[2] \
	* ray->direction[2];
	cy->c = pow(cy->oc[0], 2) + pow(cy->oc[2], 2) - (ptr->diameter / 2);
	discriminant = (pow(cy->b, 2)) - (4 * cy->a * cy->c);
	cy->t0 = (-cy->b - sqrt(discriminant)) / (2.0 * cy->a);
	cy->t1 = (-cy->b + sqrt(discriminant)) / (2.0 * cy->a);
	cy->max = (pow((ptr->diameter / 2), 2)) / 2.0;
	cy->min = -1.0 * cy->max;
	return (discriminant);
}

static t_intersec	*get_intersection(t_cy *cy, double discriminant, t_ray *ray)
{
	t_intersec	*intersection_points;
	double		y0;
	double		y1;

	intersection_points = (t_intersec *)malloc(sizeof(t_intersec));
	intersection_points->cont = 0;
	if (cy->t0 > cy->t1)
		swap_double(&cy->t0, &cy->t1);
	y0 = cy->oc[1] + cy->t0 * ray->direction[1];
	if (cy->min < y0 && y0 < cy->max)
	{
		intersection_points->cont = 2;
		intersection_points->t1 = cy->t0;
	}
	y1 = cy->oc[1] + cy->t1 * ray->direction[1];
	if (cy->min < y1 && y1 < cy->max)
	{
		intersection_points->cont++;
		intersection_points->t2 = cy->t1;
	}
	return (intersection_points);
}

t_intersec	*cylinder_intersection(t_ray *ray, t_cylinder *ptr)
{
	t_intersec		*intersection_points;
	t_cy			cy;
	const double	discriminant = cylinder_discriminant(ray, &cy, ptr);

	if (discriminant < 0)
		return (NULL);
	intersection_points = get_intersection(&cy, discriminant, ray);
	intersection_points->color = ptr->color;
	return (intersection_points);
}
