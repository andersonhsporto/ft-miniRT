/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 20:11:25 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/03 19:41:38 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_camera(t_mini *data, char	**string)
{
	if (ft_strcmp(string[0], "C") == 0)
	{
		if (data->index.camera != 0)
		{
			print_error("miniRT: Camera already defined");
			exit(1);
		}
		else
		{
			return (1);
		}
	}
	else
	{
		return (0);
	}
}

t_cam	*init_camera(char **string)
{
	t_cam	*camera;

	camera = (t_cam *)malloc(sizeof(t_cam));
	camera->view_point = str_to_double_vector(string[1], ERR_VIEWPOINT);
	camera->orientation = str_to_double_vector(string[2], ERR_NORMALIZED);
	if (out_range_double(camera->orientation, -1, 1))
	{
		print_error("miniRT: Invalid Camera Normalized Vector");
		exit(1);
	}
	camera->fov = ft_atoi(string[3]);
	if (camera->fov < 0 || camera->fov > 180)
	{
		print_error("miniRT: Invalid Camera FOV");
		exit(1);
	}
	print_vector("Camera View Point: ", camera->view_point);
	start_camera(camera);
	return (camera);
}
