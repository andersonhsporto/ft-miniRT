/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:04:59 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/28 22:27:48 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void get_y0_y1(double *intersec, double *y0_y1, t_ray *ray)
{
	double temp;

	if (intersec[0] > intersec[1])
	{
		temp = intersec[0];
		intersec[0] = intersec[1];
		intersec[1] = temp;
	}
	y0_y1[0] = ray->origin.y + (intersec[0] * ray->direction.y);
	y0_y1[1] = ray->origin.y + (intersec[1] * ray->direction.y);
}

static int eof(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

static t_intersec *create_intersec(double *vals, t_ray *ray, t_cylinder_d *cyd)
{
	t_intersec	*res;
	double		intersec[2];
	double		y_y1[2];
	double		min;
	double		max;

	max = cyd->height / 2.0;
	min = -1.0 * max;
	res = NULL;
	intersec[0] = (((-1 * vals[1]) - sqrt(vals[2])) / (2 * vals[0]));
	intersec[1] = (((-1 * vals[1]) + sqrt(vals[2])) / (2 * vals[0]));
	if (vals[2] >= 0 && eof(vals[0], 0) == 0)
	{
		get_y0_y1(intersec, y_y1, ray);
		if (y_y1[0] > min && max > y_y1[0])
		{
			res = (t_intersec *)malloc(sizeof(t_intersec));
			res->t = intersec[0];
			res->obj_type = cylinder;
			res->next = NULL;
		}
		if (y_y1[1] > min && max > y_y1[1])
		{
			if (res == NULL)
			{
				res = (t_intersec *)malloc(sizeof(t_intersec));
				res->t = intersec[1];
				res->obj_type = cylinder;
				res->next = NULL;
			}
			else
			{
				res->next = (t_intersec *)malloc(sizeof(t_intersec));
				res->next->t = intersec[1];
				res->next->obj_type = cylinder;
				res->next->next = NULL;
			}
		}
	}
	return (res);
}

t_intersec	*cylinder_intersec(t_ray *base_ray, void *ptr)
{
	t_cylinder_d	*cyd = (t_cylinder_d *)ptr;
	t_ray			ray;
	double			a;
	double			b;
	double			c;
	double			disc;
	double			vals[3];

	ray = ray_to_object_space(base_ray, cyd->transform);
	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = (2 * ray.origin.x * ray.direction.x) +
		(2 * ray.origin.z * ray.direction.z);
	c = (pow(ray.origin.x, 2) + pow(ray.origin.z, 2)) - 1.0;
	disc = pow(b, 2) - (4 * a * c);
	vals[0] = a;
	vals[1] = b;
	vals[2] = disc;
	return (create_intersec(vals, &ray, cyd));
}

void	render_cylinder_transform(t_cylinder *cylinder)
{
	double **translate;
	double **rotate;
	double **scale;
	double **transform;
	double radius;

	radius = cylinder->diameter * 0.5;
	scale = identity(radius, cylinder->height * 0.5, radius);
	translate = translation(cylinder->pos->x,
							cylinder->pos->y, cylinder->pos->z);
	transform = matrix_multiply(translate, scale);
	rotate = normal_rotation_matrix(cylinder->norm);
	translate = matrix_multiply(rotate, transform);
	cylinder->transform = translate;
}
