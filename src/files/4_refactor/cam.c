/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:40:12 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/16 01:22:14 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	**calculate_orientation(t_coo *left, t_coo *true_up, t_coo *forward, t_coo *from)
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
	t_coo		*forward;
	t_coo		*up_normal;
	t_coo		*left;
	t_coo		*true_up;

	forward = vector_normalize(vector_subtration(to, from));
	up_normal = vector_normalize(up);
	left = vector_cross(forward, up_normal);
	true_up = vector_cross(left, forward);
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

t_cam	*init_cam(void)
{
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	cam->fov = 85;
	cam->view = create_vector(0, 0.5, -8, 0);
	cam->pos = create_vector(0, 0, 1, 0);
	cam->transform = view_transform(cam->view, vector_addition(cam->view, cam->pos),
		vector_cross(vector_cross(cam->pos, create_vector(0, 1, 0, 0)), cam->pos));
	cam->transform = matrix_inverter(cam->transform);
	camera_pixel_size(WIDTH, HEIGHT, cam);
	cam->origin = mult_matrix_vector(cam->transform, create_vector(0, 0, 0, 1));
	return(cam);
}
