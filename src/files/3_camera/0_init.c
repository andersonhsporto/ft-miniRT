/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:37:51 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/12 23:56:26 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_viewport_height(int fov)
{
	return (tan((fov * M_PI / 180.0) / 2) * 2);
}

t_vector	get_lower_left_corner(t_mini *data)
{
	t_vector	temp;
	t_vector	utils;
	t_vector	lower_left;

	utils = vector_new(data->cam->view_point.x, data->cam->view_point.y, \
	data->cam->view_point.z);
	temp = vector_sub(utils, vector_div(data->data_cam->hori_dir, 2));
	lower_left = vector_sub(vector_sub(temp, vector_div(data->data_cam->vert_dir, 2)), data->data_cam->w);
	return (lower_left);
}

void	orienting_camera(t_mini *data)
{
	data->data_cam = (t_datacam *)malloc(sizeof(t_datacam));
	data->data_cam->viewport_height = get_viewport_height(data->cam->fov);
	data->data_cam->ratio = (double)WIDTH / (double)HEIGHT;
	data->data_cam->viewport_width = data->data_cam->viewport_height * \
	data->data_cam->ratio;
	data->data_cam->view_up = vector_new(0, 1, 0);
	data->data_cam->w = unit_vector(vector_mult(data->cam->normalized_vector, \
		-1));
	data->data_cam->u = unit_vector(vector_cross(data->data_cam->view_up, \
		data->data_cam->w));
	data->data_cam->v = unit_vector(vector_cross(data->data_cam->w, \
		data->data_cam->u));
	data->data_cam->hori_dir = vector_mult(data->data_cam->u, \
		data->data_cam->viewport_width);
	data->data_cam->vert_dir = vector_mult(data->data_cam->v, \
		data->data_cam->viewport_height);
	data->data_cam->lower_left_corner = get_lower_left_corner(data);
	print_cam_data(data->data_cam);
}
