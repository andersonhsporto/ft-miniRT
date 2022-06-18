/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_hit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 01:54:20 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/15 00:13:19 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit(t_element *list, t_ray *ray, t_record *rec)
{
	t_element	*temp;

	temp = list;
	while (temp != NULL)
	{
		if (hit_element(temp, ray, rec))
		{
			rec->max = rec->t;
			rec->albedo = vector_mult(temp->color, 1.0 / 255.0);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	hit_element(t_element *list, t_ray *ray, t_record *rec)
{
	int as_hit;

	as_hit = 0;
	if (list->type == sphere)
	{
		as_hit = hit_sphere(list, ray, rec);
	}
	return (as_hit);
}

double	get_discriminant(t_ray ray, t_sphere spr)
{
	double		a;
	double		b;
	double		c;
	double		discriminant;

	a =	sum_square_vector(ray.direction);
	b = vector_dot(vector_sub(ray.origin, spr.center), ray.direction);
	c = sum_square_vector(vector_sub(ray.origin, spr.center)) - pow(spr.diameter, 2.0);
	discriminant = pow(b, 2.0) - (a * c);
	return (discriminant);
}

double	get_root(t_ray ray, t_sphere spr, double discriminant, int flag)
{
	const t_vector	oc = vector_sub(ray.origin, spr.center);
	const double	a = vector_dot(ray.direction, ray.direction);
	const double	b = 2 * vector_dot(ray.direction, oc);
	double			root;

	if (flag == 1)
		root = (-b + sqrt(discriminant)) / a;
	else
		root = (-b - sqrt(discriminant)) / a;
	return (root);
}
