/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_1_0_cy_intersec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 00:56:36 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/02 01:00:50 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	get_y0_y1(double *intersec, double *y0_y1, t_ray *ray)
{
	double	temp;

	if (intersec[0] > intersec[1])
	{
		temp = intersec[0];
		intersec[0] = intersec[1];
		intersec[1] = temp;
	}
	y0_y1[0] = ray->origin.y + (intersec[0] * ray->direction.y);
	y0_y1[1] = ray->origin.y + (intersec[1] * ray->direction.y);
}

static int	eof(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	else
		return (0);
}

static t_intersec	*intersec_helper(double intersec, int pos)
{
	t_intersec	*res;

	res = (t_intersec *)malloc(sizeof(t_intersec));
	res->t = intersec;
	res->obj_type = cylinder;
	res->obj_pos = pos;
	res->next = NULL;
	return (res);
}

void	intersec_while_helper(t_intersec *res, double intersec, int pos)
{
	if (res == NULL)
		res = intersec_helper(intersec, pos);
	else
		res->next = intersec_helper(intersec, pos);
}

t_intersec	*create_intersec(double *vals, t_ray *ray, t_cylinder_d *cyd)
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
			res = intersec_helper(intersec[0], cyd->id);
		if (y_y1[1] > min && max > y_y1[1])
		{
			intersec_while_helper(res, intersec[1], cyd->id);
		}
	}
	free_matrix(ray->inverse, 4);
	return (res);
}
