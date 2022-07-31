/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:33:43 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 19:58:22 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	line_scene_helper(t_mini *data, char **split);

int	there_file_error(t_mini *data)
{
	if (data->error.line_error != 0 || data->error.multiple_ambient != 0)
	{
		return (1);
	}
	if (data->error.rgb != 0 || data->error.ambient_color != 0)
	{
		return (1);
	}
	if (data->error.ambient_ratio != 0 || data->error.multiple_camera != 0)
	{
		return (1);
	}
	if (data->error.camera_view_point != 0 || data->error.camera_orientation != 0)
	{
		return (1);
	}
	if (data->error.camera_fov != 0)
	{
		return (1);
	}
	return (0);
}

void	get_line_scene(t_mini *data, char *line)
{
	char	**split;

	split = ft_split(line, '+');
	if (matrix_len(split) == 1 || there_file_error(data))
	{
		matrix_free(split);
		return ;
	}
	if (matrix_len(split) < 3)
	{
		data->error.line_error = true;
		matrix_free(split);
		return ;
	}
	line_scene_helper(data, split);
	matrix_free(split);
}

static void	line_scene_helper(t_mini *data, char **split)
{
	if (find_ambient(data, split))
		data->light_a = init_ambient(split, data);
	else if (find_camera(data, split))
		data->cam = init_camera(split, data);
	else if (find_light(data, split))
		data->light = init_light(split);
	else if (find_sphere(split))
		lst_new_sphere(data, split);
	else if (find_plane(split))
		lst_new_plane(data, split);
	else if (find_cylinder(split))
		lst_new_cylinder(data, split);
}
