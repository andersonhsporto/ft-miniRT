/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_element.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:18:49 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 20:08:06 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_face_normal(t_ray *ray, t_record *rec, double root, t_sphere *sp)
{
	int front_face;

	rec->t = root;
	rec->p = ray_at(*ray, root);
	rec->normal = unit_vector(vector_sub(rec->p, sp->center));
	front_face = vector_dot(ray->direction, rec->normal);
	if (front_face > 0)
		rec->normal = vector_mult(rec->normal, -1);
	return (1);
}

int	hit_sphere(t_element *list, t_ray *ray, t_record *rec)
{
	const t_sphere	*spr = (t_sphere *)list->ptr;
	const double	discriminant = get_discriminant(*ray, *spr);
	double			root;

	if (discriminant > 0)
	{
		root = get_root(*ray, *spr, discriminant, 1);
		if (root > 0 && root < INFINITY)
		{
			return (set_face_normal(ray, rec, root, spr));
		}
	}
	return (0);
}
