/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_if_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:36:35 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:08:06 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	check_ambient_error(t_mini *data);
static	void	check_camera_error(t_mini *data);

static void	check_sp_cy_pl_error(t_mini *data)
{
	if (data->error.sp_coord != false)
	{
		exit_and_free(data, ERR_SPHERE, 1);
	}
	if (data->error.pl_coord != false || data->error.pl_normalized != false)
	{
		exit_and_free(data, ERR_PLANE, 1);
	}
	if (data->error.cy_coord != false)
	{
		exit_and_free(data, ERR_CYLINDER, 1);
	}
	return ;
}

void	check_if_error(t_mini *data)
{
	if (data->error.line_error != false)
		exit_and_free(data, "miniRT: Invalid Line", 1);
	check_ambient_error(data);
	check_camera_error(data);
	if (data->error.light_point != false)
		exit_and_free(data, "miniRT: Invalid Light Point", 1);
	if (data->error.light_bright != false)
		exit_and_free(data, "miniRT: Invalid Light Intensity", 1);
	check_sp_cy_pl_error(data);
}

static	void	check_ambient_error(t_mini *data)
{
	if (data->error.multiple_ambient != false)
		exit_and_free(data, "miniRT: Ambient already defined", 1);
	if (data->error.rgb != false)
		exit_and_free(data, ERR_RGB, 1);
	if (data->error.ambient_color != false)
		exit_and_free(data, "miniRT: Invalid Ambient Color", 1);
	if (data->error.ambient_ratio != false)
		exit_and_free(data, "miniRT: Invalid Ambient Ratio", 1);
	return ;
}

static	void	check_camera_error(t_mini *data)
{
	if (data->error.multiple_camera != false)
		exit_and_free(data, "miniRT: Multiple Camera", 1);
	if (data->error.camera_view_point != false)
		exit_and_free(data, "miniRT: Invalid Camera View Point", 1);
	if (data->error.camera_orientation != false)
		exit_and_free(data, "miniRT: Invalid Camera Orientation", 1);
	if (data->error.camera_fov != false)
		exit_and_free(data, "miniRT: Invalid Camera FOV", 1);
	return ;
}
