/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_normal_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 23:58:04 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/01 22:56:31 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_angle(t_coo *normal);
static t_coo	*get_axis(t_coo *normal);
double			*get_vals(double angle);

double	**normal_rotation_matrix(t_coo *normal)
{
	double	**rotation;
	double	angle;
	t_coo	*axis;
	double	*vals;

	rotation = create_matrix(4, 4);
	angle = get_angle(normal);
	axis = get_axis(normal);
	vals = get_vals(angle);
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
	free(axis);
	free(vals);
	return (rotation);
}

static double	get_angle(t_coo *normal)
{
	double	angle;
	t_coo	*temp;

	temp = create_vector(0, 1, 0, 0);
	angle = acos(vector_abs(normal, temp));
	free(temp);
	return (angle);
}

static t_coo	*get_axis(t_coo *normal)
{
	t_coo	*axis;
	t_coo	*temp;

	temp = create_vector(0, 1, 0, 0);
	axis = vector_cross(normal, temp);
	free(temp);
	return (axis);
}

double	*get_vals(double angle)
{
	double	*vals;

	vals = (double *)malloc(sizeof(double *) * 3);
	vals[0] = cos(angle);
	vals[1] = sin(angle);
	vals[2] = 1.0 - vals[0];
	return (vals);
}
