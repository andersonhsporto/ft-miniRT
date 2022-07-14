/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:04:59 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/13 22:37:07 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

static void			get_y0_y1(double *intersec, double *y0_y1, t_ray *ray)
{
	double	temp;

	if (intersec[0] > intersec[1])
	{
		temp = intersec[0];
		intersec[0] = intersec[1];
		intersec[1] = temp;
	}
	y0_y1[0] =ray->origin->y + (intersec[0] * ray->direction->y);
	y0_y1[1] =ray->origin->y + (intersec[1] * ray->direction->y);
}

static int	eof(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

static t_intersec	*create_intersec(double *vals, t_cylinder *cylinder, t_ray *ray, int pos)
{
	t_intersec		*res;
	double			intersec[2];
	double			y_y1[2];
	double			min;
	double			max;

	max = cylinder->height / 2.0;
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
			res->obj_pos = pos;
			res->obj_type = CYLINDER;
			res->next = NULL;
		}
		if (y_y1[1] > min && max > y_y1[1])
		{
			if (res == NULL)
			{
				res = (t_intersec *)malloc(sizeof(t_intersec));
				res->t = intersec[1];
				res->obj_pos = pos;
				res->obj_type = CYLINDER;
				res->next = NULL;
			}
			else
			{
				res->next = (t_intersec *)malloc(sizeof(t_intersec));
				res->next->t = intersec[1];
				res->next->obj_pos = pos;
				res->next->obj_type = CYLINDER;
				res->next->next = NULL;
			}
		}
	}
	return (res);
}


t_intersec	*cylinder_intersec(t_ray *base_ray, t_cylinder *cylinder, int pos)
{
	t_ray		*ray;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		vals[3];

	ray = ray_to_object_space(base_ray, cylinder->transform);
	a = pow(ray->direction->x, 2) + pow(ray->direction->z, 2);
	b = (2 * ray->origin->x * ray->direction->x) +
		(2 * ray->origin->z * ray->direction->z);
	c = (pow(ray->origin->x, 2) + pow(ray->origin->z, 2)) - 1.0;
	disc = pow(b, 2) - (4 * a * c);
	vals[0] = a;
	vals[1] = b;
	vals[2] = disc;
	return (create_intersec(vals, cylinder, ray, pos));
}

void	render_cylinder_transform(t_cylinder *cylinder)
{
	double	**translate;
	double	**rotate;
	double	**scale;
	double	**transform;
	double	radius;

	radius = cylinder->diameter * 0.5;
	scale = identity(radius, cylinder->height * 0.5, radius);
	translate = translation(cylinder->pos->x,
		cylinder->pos->y, cylinder->pos->z);
	transform = matrix_multiply(translate, scale);
	rotate = normal_rotation_matrix(cylinder->norm);
	translate = matrix_multiply(rotate, transform);
	cylinder->transform = translate;
}

t_cylinder	*init_cylinder(void)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->pos = create_vector(0, 0, 0, 0);
	cylinder->norm = create_vector(1, 0, 0, 0);
	cylinder->height = 3;
	cylinder->diameter = 4;
	cylinder->radius = cylinder->diameter / 2.0;
	cylinder->material = (t_material *)malloc(sizeof(t_material));
	cylinder->material->color = create_vector(1, 0.2, 0.3, 0);
	cylinder->material->ambient = 0.1;
	cylinder->material->diffuse = 0.9;
	cylinder->material->specular = 0.4;
	cylinder->material->shininess = 100.0;
	return (cylinder);
}