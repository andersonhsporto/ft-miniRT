/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:50:42 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/01 22:21:28 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void render_sphere_transform(t_sphere *sphere)
{
	double **translate;
	double **scale;
	double **transform;

	translate = translation(sphere->center->x,
							sphere->center->y, sphere->center->z);
	scale = identity(sphere->radius, sphere->radius, sphere->radius);
	transform = matrix_multiply(scale, translate);
	sphere->transform = transform;
}

t_intersec *sphere_intersection(t_ray *base_ray, void *ptr)
{
	t_sphere_d	*obj = (t_sphere_d *)ptr;
	t_intersec	*intersectionPoints = NULL;
	t_ray		ray = ray_to_object_space(base_ray, obj->transform);
	t_coo		temp = create_vector_temp(0, 0, 0, 1);
	t_coo		sphere_to_ray = vector_subtraction_temp(&ray.origin, &temp);
	double		dot;
	double		vals[3];

	vals[0] = vector_abs(&ray.direction, &ray.direction);
	vals[1] = 2 * vector_abs(&ray.direction, &sphere_to_ray);
	dot = vector_abs(&sphere_to_ray, &sphere_to_ray) - 1;
	free_matrix(ray.inverse, 4);
	vals[2] = ((vals[1] * vals[1]) - (4 * vals[0] * dot));
	if (vals[2] >= 0)
	{
		intersectionPoints = (t_intersec *)malloc(sizeof(t_intersec));
		intersectionPoints->t = (((-1 * vals[1]) - sqrt(vals[2])) / (2 * vals[0]));
		intersectionPoints->obj_type = sphere;
		intersectionPoints->obj_pos = obj->id;
		intersectionPoints->next = (t_intersec *)malloc(sizeof(t_intersec));
		intersectionPoints->next->t = (((-1 * vals[1]) + sqrt(vals[2])) / (2 * vals[0]));
		intersectionPoints->next->next = NULL;
	}
	return (intersectionPoints);
}
