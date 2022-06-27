/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/06/27 08:58:30 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"


double	**identity(double x, double y, double z)
{
	double	**res;
	int		i;

	i = 0;
	res = (double **)malloc(sizeof(double *) * 4);
	while (i < 4)
	{
		res[i] = (double *)malloc(sizeof(double) * 4);
		i++;
	}
	res[0][0] = (double)x;res[0][1] = 0.0;res[0][2] = 0.0;res[0][3] = 0.0;
	res[1][0] = 0.0;res[1][1] = (double)y;res[1][2] = 0.0;res[1][3] = 0.0;
	res[2][0] = 0.0;res[2][1] = 0.0;res[2][2] = (double)z;res[2][3] = 0.0;
	res[3][0] = 0.0;res[3][1] = 0.0;res[3][2] = 0.0;res[3][3] = 1.0;
	return (res);
}

double	**translation(double x, double y, double z)
{
	double	**res;

	res = identity(1, 1, 1);
	res[0][3] = x;
	res[1][3] = y;
	res[2][3] = z;
	return (res);
}

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
	double	half_view;
	double	aspect;
	double	rad;

	rad = (cam->fov * M_PI)/180;
	half_view = tan(rad / 2);
	aspect = (double)width / (double)height;
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
	cam->fov = 70;
	cam->view = create_vector(-50, 0, 20, 0);
	cam->pos = create_vector(0, 0, 1, 0);
	cam->transform = view_transform(cam->view, vector_addition(cam->view, cam->pos),
		vector_cross(vector_cross(cam->pos, create_vector(0, 1, 0, 0)), cam->pos));
	cam->transform = matrix_inverter(cam->transform, matrix_determinant(cam->transform));
	cam->origin = mult_matrix_vector(cam->transform, create_vector(0, 0, 0, 1));
	camera_pixel_size(NX, NY, cam);
	return(cam);
}

t_ray	*create_ray(t_coo *origin, t_coo *direction)
{
	t_ray	*new;

	new = (t_ray *)malloc(sizeof(t_ray));
	new->origin = origin;
	new->direction = direction;
	return (new);
}

t_ray	*ray_for_pixel(t_cam *cam, int x, int y)
{
	double	x_offset;
	double	y_offset;
	t_coo	*direction;

	x_offset = (x + 0.5) * cam->pixel_size;
	y_offset = (y + 0.5) * cam->pixel_size;
	direction = vector_normalize(vector_subtration(mult_matrix_vector(cam->transform,
		create_vector(cam->half_width - x_offset,
		cam->half_height - y_offset, -1, 1)), cam->origin));
	return (create_ray(cam->origin, direction));
}

void	render_sphere_transform(t_sphere *sphere)
{
	t_matrix	translate;
	t_matrix	scale;
	t_matrix	transform;

	translate = translation(sphere->center.x,
		sphere->center.y, sphere->center.z);
	scale = scaling(sphere->radius, sphere->radius, sphere->radius);
	transform = mult_matrix(scale, translate);
	sphere->transform = transform;
	free_matrix(translate);
	free_matrix(scale);
}

int	main()
{
	t_cam	*cam;
	t_ray	*ray;

	cam = init_cam();
	int	y = 0;
	while (y < NY)
	{
		int	x = 0;
		while (x < NX)
		{
			ray = ray_for_pixel(cam, x, y);

			x++;
		}
		y++;
	}

// int	i = 0;
// 	while (i < 4)
// 	{
// 		int	y = 0;
// 		while (y < 4)
// 		{
// 			printf("%f ", cam->transform[i][y]);
// 			y++;
// 		}
// 		printf("\n");
// 		i++;
// printf("%f %f %f %f\n", ray->direction->x, ray->direction->y, ray->direction->z, ray->direction->w);
// 	}
}