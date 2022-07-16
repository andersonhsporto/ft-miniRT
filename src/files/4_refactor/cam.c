/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:40:12 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/16 03:08:17 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**calculate_orientation(t_coo *left, t_coo *true_up, t_coo *forward, t_coo *from)
{
	double	**matrix;
	double	**translate;
	double	**orientation;

	matrix = create_matrix(4, 4);
	matrix[0][0] = left->x;
	matrix[0][1] = left->y;
	matrix[0][2] = left->z;
	matrix[1][0] = true_up->x;
	matrix[1][1] = true_up->y;
	matrix[1][2] = true_up->z;
	matrix[2][0] = -1.0 * forward->x;
	matrix[2][1] = -1.0 * forward->y;
	matrix[2][2] = -1.0 * forward->z;
	matrix[3][3] = 1.0;
	translate =  translation(-1.0 * from->x, -1.0 * from->y, -1.0 * from->z);
	orientation = matrix_multiply(matrix, translate);
	return (orientation);
}

double	**view_transform(t_coo *from, t_coo *to, t_coo *up)
{
	const t_coo		*forward = vector_normalize(vector_subtration(to, from));
	const t_coo		*up_normal = vector_normalize(up);
	const t_coo		*left = vector_cross(forward, up_normal);
	const t_coo		*true_up = vector_cross(left, forward);

	// free((t_coo *)forward);
	// free((t_coo *)up_normal);
	// free((t_coo *)left);
	// // free((t_coo *)true_up);
	return (calculate_orientation(left, true_up, forward, from));
}

void	camera_pixel_size(int width, int height, t_cam *cam)
{
	const double	rad = (cam->fov * M_PI) / 180;
	const double	half_view = tan(rad / 2);
	const double	aspect = (double)width / (double)height;

	if (aspect >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / width;
}
