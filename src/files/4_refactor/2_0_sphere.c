/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_0_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:50:42 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/02 00:29:44 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_sp_intersec	init_sphere_intersection(t_ray *base_ray, \
t_sphere_d *obj);
static t_intersec		*get_intersection_ptr(double vals[3], \
t_sphere_d *obj);

t_intersec	*sphere_intersection(t_ray *base_ray, void *ptr)
{
	const t_sphere_d		*obj = (t_sphere_d *)ptr;
	t_sp_intersec			sp_data;
	t_intersec				*intersection;

	sp_data = init_sphere_intersection(base_ray, (t_sphere_d *)obj);
	intersection = NULL;
	if (sp_data.vals[2] >= 0)
	{
		intersection = get_intersection_ptr(sp_data.vals, (t_sphere_d *)obj);
	}
	return (intersection);
}

static t_intersec	*get_intersection_ptr(double vals[3], t_sphere_d *obj)
{
	t_intersec	*intersection_points;

	intersection_points = (t_intersec *)malloc(sizeof(t_intersec));
	intersection_points->t = (((-1 * vals[1]) - sqrt(vals[2])) / (2 * vals[0]));
	intersection_points->obj_type = sphere;
	intersection_points->obj_pos = obj->id;
	intersection_points->next = (t_intersec *)malloc(sizeof(t_intersec));
	intersection_points->next->t = (((-1 * vals[1]) + sqrt(vals[2])) \
	/ (2 * vals[0]));
	intersection_points->next->next = NULL;
	return (intersection_points);
}

static t_sp_intersec	init_sphere_intersection(t_ray *base_ray, \
t_sphere_d *obj)
{
	t_sp_intersec	sp_data;

	sp_data.ray = ray_to_object_space(base_ray, obj->transform);
	sp_data.temp = create_vector_temp(0, 0, 0, 1);
	sp_data.sphere_to_ray = vector_subtraction_temp(&sp_data.ray.origin, \
	&sp_data.temp);
	sp_data.vals[0] = vector_abs(&sp_data.ray.direction, \
	&sp_data.ray.direction);
	sp_data.vals[1] = 2 * vector_abs(&sp_data.ray.direction, \
	&sp_data.sphere_to_ray);
	sp_data.dot = vector_abs(&sp_data.sphere_to_ray, \
	&sp_data.sphere_to_ray) - 1;
	free_matrix(sp_data.ray.inverse, 4);
	sp_data.vals[2] = ((sp_data.vals[1] * sp_data.vals[1]) - \
	(4 * sp_data.vals[0] * sp_data.dot));
	return (sp_data);
}
