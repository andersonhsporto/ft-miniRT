/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:59:00 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/29 23:46:19 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void render_plane_transform(t_plane *plane)
{
	double	**translate;
	double	**rotate;
	double	**transform;

	translate = translation(plane->pos->x,
							plane->pos->y, plane->pos->z);
	rotate = normal_rotation_matrix(plane->norm);
	transform = matrix_multiply(translate, rotate);
	plane->transform = transform;
}

t_intersec	*plane_intersection(t_ray *base_ray, void *ptr)
{
	const t_plane_d	*obj2 = (t_plane_d *)ptr;
	const t_ray		ray = ray_to_object_space(base_ray, obj2->transform);
	t_intersec		*intersectionPoints;

	if (fabs(ray.direction.y) < EPSILON)
		return (NULL);
	intersectionPoints = (t_intersec *)malloc(sizeof(t_intersec));
	intersectionPoints->t = (-1 * ray.origin.y) / ray.direction.y;
	free_matrix(ray.inverse, 4);
	intersectionPoints->obj_type = plane;
	intersectionPoints->next = NULL;
	return (intersectionPoints);
}
