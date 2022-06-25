/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:03:55 by algabrie          #+#    #+#             */
/*   Updated: 2022/06/25 16:46:46 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_coo	*background_3d_color(t_ray *ray)
{
	t_coo	*var;
	t_coo	*aux;
	t_coo	*color;
	double	t;

	var = vector_normalize(ray->direction);
	t = 0.5 * (var->y + 1.0);
	free(var);
	var = creat_vector(1.0, 1.0, 1.0);
	aux = vector_multipli_scalar(1.0 - t, var);
	free(var);
	color = creat_vector(0.5, 0.7, 1.0);
	var = vector_multipli_scalar(t, color);
	free(color);
	color = vector_addition(var, aux);
	free(aux);
	free(var);
	return(color);
}

t_coo	*point_at_parameter(double t, t_ray *ray)
{
	t_coo	*var;
	t_coo	*res;

	var = vector_multipli_scalar(t, ray->direction);
	res = vector_addition(ray->origin, var);
	free(var);
	return (res);
}

int	cylinder_intersection(t_ray *ray, t_scene *sphere, double t_max, double t_min)
{
	t_coo *oc = vector_subtration(ray->origin, sphere->center);
	double	a = ray->direction->x * ray->direction->x + ray->direction->z * ray->direction->z;
	double	b = 2.0 * oc->x * ray->direction->x + 2.0 * oc->z * ray->direction->x;
	double	c = oc->x * oc->x + oc->z * oc->z - sphere->radius;
	double	discriminant = (b*b)-(4*a*c);
	if (discriminant < 0)
		return (0);

	double temp = (-b - sqrt(discriminant))/a;
	if (!(temp < t_max && temp > t_min))
	{
		temp = (-b + sqrt(discriminant))/a;
		if (!(temp < t_max && temp > t_min))
			return	(0);
	}
	double	y0 = oc->y + temp * ray->direction->y;
	double max =  (sphere->radius * sphere->radius) / 2.0;
	double min = -1.0 * max;
	if (!(min < y0 && y0 < max))
		return (0);
	free(oc);
	sphere->t = y0;
	sphere->p = point_at_parameter(sphere->t, ray);
	oc = vector_subtration(sphere->p, sphere->center);
	sphere->normal = vector_multipli_scalar(1.0/sphere->radius, oc);
	free(oc);
	return (1);
}


int	hit_sphere(t_ray *ray, t_scene *sphere, double t_max, double t_min)
{
	t_coo *oc = vector_subtration(ray->origin, sphere->center);
	double	a = vector_abs(ray->direction, ray->direction);
	double	b = vector_abs(oc, ray->direction);
	double	c = vector_abs(oc, oc) - (sphere->radius*sphere->radius);
	double	discriminant = (b*b)-(a*c);
	if (!(discriminant > 0))
		return (0);
	double temp = (-b - sqrt(discriminant))/a;
	if (!(temp < t_max && temp > t_min))
	{
		temp = (-b + sqrt(discriminant))/a;
		if (!(temp < t_max && temp > t_min))
			return	(0);
	}
	free(oc);
	sphere->t = temp;
	sphere->p = point_at_parameter(sphere->t, ray);
	oc = vector_subtration(sphere->p, sphere->center);
	sphere->normal = vector_multipli_scalar(1.0/sphere->radius, oc);
	free(oc);
	return (1);
}

t_scene	*hiter_point(t_ray *ray, t_scene **hiter, t_scene *rec)
{
	double	t_max = __FLT_MAX__;
	double	t_min = 0.001;
	int		i;

	i = 0;
	rec = NULL;
	while (hiter[i])
	{
		if (hiter[i]->type == 'S')
		{
			if (hit_sphere(ray, hiter[i], t_max, t_min))
			{
				t_max = hiter[i]->t;
				rec = hiter[i];
			}
		}
		if (hiter[i]->type == 'C')
		{
			if (cylinder_intersection(ray, hiter[i], t_max, t_min))
			{
				t_max = hiter[i]->t;
				rec = hiter[i];
			}
		}
		i++;
	}
	return (rec);
}
