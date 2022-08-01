/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_0_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:11:25 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/01 01:01:18 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_camera(t_mini *data, char **string)
{
	if (ft_strcmp(string[0], "C") == 0)
	{
		if (data->index.camera == 0)
		{
			data->index.camera++;
			return (1);
		}
		else
		{
			data->error.multiple_camera = true;
			return (0);
		}
	}
	else
	{
		return (0);
	}
}

t_cam_d	*init_camera(char **string, t_mini *data)
{
	t_cam_d	*camera;

	camera = (t_cam_d *)malloc(sizeof(t_cam_d));
	camera->view_point = str_to_coo_vector(string[1], \
	&data->error.camera_view_point);
	camera->orientation = str_to_coo_vector(string[2], \
	&data->error.camera_orientation);
	if (out_range_coo(&camera->orientation, -1, 1) || there_file_error(data))
	{
		data->error.camera_orientation = true;
		return (camera);
	}
	camera->fov = str_to_double(string[3]);
	if (camera->fov < 0 || camera->fov > 180 || there_file_error(data))
	{
		data->error.camera_fov = true;
		return (camera);
	}
	return (camera);
}
