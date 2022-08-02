/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_2_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:59:00 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/02 01:04:12 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render_plane_transform(t_plane *plane)
{
	double	**translate;
	double	**rotate;
	double	**transform;

	translate = translation(plane->pos->x, plane->pos->y, plane->pos->z);
	rotate = normal_rotation_matrix(plane->norm);
	transform = matrix_multiply(translate, rotate);
	plane->transform = transform;
}

t_intersec	*plane_intersection(t_ray *base_ray, void *ptr)
{
	t_intersec			*intersection_points;
	const t_plane_d		*obj2 = (t_plane_d *)ptr;
	const t_ray			ray = ray_to_object_space(base_ray, obj2->transform);

	if (fabs(ray.direction.y) < EPSILON)
	{
		return (NULL);
	}
	intersection_points = (t_intersec *)malloc(sizeof(t_intersec));
	intersection_points->t = (-1 * ray.origin.y) / ray.direction.y;
	free_matrix(ray.inverse, 4);
	intersection_points->obj_type = plane;
	intersection_points->obj_pos = obj2->id;
	intersection_points->next = NULL;
	return (intersection_points);
}
