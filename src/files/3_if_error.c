/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_if_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:36:35 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 20:42:07 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static	void	check_ambient_error(t_mini *data);
static	void	check_camera_error(t_mini *data);

void	check_if_error(t_mini *data)
{
	if (data->error.line_error != false)
		exit_and_free(data, "miniRT: Invalid Line");
	check_ambient_error(data);
	check_camera_error(data);
	if (data->error.light_point != false)
		exit_and_free(data, "miniRT: Invalid Light Point");
	if (data->error.light_bright != false)
		exit_and_free(data, "miniRT: Invalid Light Intensity");
}

static	void	check_ambient_error(t_mini *data)
{
	if (data->error.multiple_ambient != false)
		exit_and_free(data, "miniRT: Ambient already defined");
	if (data->error.rgb != false)
		exit_and_free(data, ERR_RGB);
	if (data->error.ambient_color != false)
		exit_and_free(data, "miniRT: Invalid Ambient Color");
	if (data->error.ambient_ratio != false)
		exit_and_free(data, "miniRT: Invalid Ambient Ratio");
	return ;
}

static	void	check_camera_error(t_mini *data)
{
	if (data->error.multiple_camera != false)
		exit_and_free(data, "miniRT: Multiple Camera");
	if (data->error.camera_view_point != false)
		exit_and_free(data, "miniRT: Invalid Camera View Point");
	if (data->error.camera_orientation != false)
		exit_and_free(data, "miniRT: Invalid Camera Orientation");
	if (data->error.camera_fov != false)
		exit_and_free(data, "miniRT: Invalid Camera FOV");
	return ;
}
