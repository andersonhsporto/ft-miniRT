/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:59:00 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/26 11:49:24 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double **normal_rotation_matrix(t_coo *normal)
{
	double	angle;
	double	vals[3];
	double	**rotation;
	t_coo	*axis;

	rotation = create_matrix(4, 4);
	angle = acos(vector_abs(normal, create_vector(0, 1, 0, 0)));
	axis = vector_cross(normal, create_vector(0, 1, 0, 0));
	vals[0] = cos(angle);
	vals[1] = sin(angle);
	vals[2] = 1.0 - vals[0];
	rotation[0][0] = vals[0] + (pow(axis->x, 2) * vals[2]);
	rotation[0][1] = (axis->x * axis->y * vals[2]) - (axis->z * vals[1]);
	rotation[0][2] = (axis->x * axis->z * vals[2]) + (axis->y * vals[1]);
	rotation[1][0] = (axis->y * axis->z * vals[2]) + (axis->z * vals[1]);
	rotation[1][1] = vals[0] + (pow(axis->y, 2) * vals[2]);
	rotation[1][2] = (axis->y * axis->z * vals[2]) - (axis->x * vals[1]);
	rotation[2][0] = (axis->z * axis->x * vals[2]) - (axis->y * vals[1]);
	rotation[2][1] = (axis->z * axis->y * vals[2]) + (axis->x * vals[1]);
	rotation[2][2] = vals[0] + (pow(axis->z, 2) * vals[2]);
	rotation[3][3] = 1;
	return (rotation);
}

t_plane *init_plane_re(void)
{
	t_plane *plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->pos = create_vector(0, 0, -10, 0);
	plane->norm = create_vector(0, 1, 0, 0);
	plane->material = (t_material *)malloc(sizeof(t_material));
	plane->material->color = create_vector(1, 1, 1, 0);
	plane->material->ambient = 0.1;
	plane->material->diffuse = 0.2; // intensidade da luz
	plane->material->specular = 0.4;
	plane->material->shininess = 10.0;
	return (plane);
}

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
	intersectionPoints->obj_type = plane;
	intersectionPoints->next = NULL;
	return (intersectionPoints);
}
