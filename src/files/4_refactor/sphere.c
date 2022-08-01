/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:50:42 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/31 22:36:45 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_sphere *init_sphere_re(void)
{
	t_sphere *sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->center = create_vector(2, 1, 0, 0);
	sphere->diameter = 4;
	sphere->radius = sphere->diameter / 2;
	sphere->material = (t_material *)malloc(sizeof(t_material));
	sphere->material->color = create_vector(0.2, 0.2, 1, 0);
	sphere->material->ambient = 0.1;
	sphere->material->diffuse = 0.9;  // randomico
	sphere->material->specular = 0.9; // randomico
	sphere->material->shininess = 200.0;
	return (sphere);
}

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
		intersectionPoints->next = (t_intersec *)malloc(sizeof(t_intersec));
		intersectionPoints->next->t = (((-1 * vals[1]) + sqrt(vals[2])) / (2 * vals[0]));
		intersectionPoints->next->next = NULL;
	}
	return (intersectionPoints);
}
