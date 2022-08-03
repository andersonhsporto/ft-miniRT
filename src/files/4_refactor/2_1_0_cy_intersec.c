/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_1_0_cy_intersec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:20:19 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/03 01:40:02 by anhigo-s         ###   ########.fr       */
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

double	*get_max_min(t_cylinder_d *cyd)
{
	double	*max_min;

	max_min = (double *)malloc(sizeof(double) * 2);
	max_min[0] = cyd->height / 2.0;
	max_min[1] = -1.0 * max_min[0];
	return (max_min);
}

t_intersec	*create_intersec(double *vals, t_ray *ray, t_cylinder_d *cyd)
{
	t_intersec	*res;
	double		intersec[2];
	double		y_y1[2];
	double		*max_min;

	res = NULL;
	max_min = get_max_min(cyd);
	intersec[0] = (((-1 * vals[1]) - sqrt(vals[2])) / (2 * vals[0]));
	intersec[1] = (((-1 * vals[1]) + sqrt(vals[2])) / (2 * vals[0]));
	if (vals[2] >= 0 && eof(vals[0], 0) == 0)
	{
		get_y0_y1(intersec, y_y1, ray);
		if (y_y1[0] > max_min[1] && max_min[0] > y_y1[0])
			res = intersec_helper(intersec[0], cyd->id);
		if (y_y1[1] > max_min[1] && max_min[0] > y_y1[1])
		{
			if (res == NULL)
				res = intersec_helper(intersec[1], cyd->id);
			else
				res->next = intersec_helper(intersec[1], cyd->id);
		}
	}
	helper_cy(ray->inverse, max_min);
	return (res);
}
