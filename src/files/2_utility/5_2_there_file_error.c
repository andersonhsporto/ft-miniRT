/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_2_there_file_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:01:08 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 23:07:57 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ambient_error(t_mini *data);
static int	camera_error(t_mini *data);
static int	element_error(t_mini *data);

int	there_file_error(t_mini *data)
{
	if (data->error.line_error != 0 || data->error.rgb != 0)
	{
		return (1);
	}
	if (data->error.light_bright != 0 || data->error.light_point != 0)
	{
		return (1);
	}
	if (ambient_error(data) == 1 || camera_error(data) == 1 || \
	element_error(data) == 1)
	{
		return (1);
	}
	return (0);
}

static int	ambient_error(t_mini *data)
{
	if (data->error.multiple_ambient != 0 || data->error.ambient_color != 0 || \
	data->error.ambient_ratio != 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int	camera_error(t_mini *data)
{
	if (data->error.camera_view_point != 0 || data->error.camera_fov != 0 || \
	data->error.camera_orientation != 0 || data->error.multiple_camera != 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int	element_error(t_mini *data)
{
	if (data->error.sp_coord != 0 || data->error.pl_coord != 0 || \
	data->error.pl_normalized != 0 || data->error.cy_coord != 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
