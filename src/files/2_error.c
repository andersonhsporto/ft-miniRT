/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:51:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 20:04:43 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_and_free(t_mini *data);

void	print_error(char *error_message)
{
	printf("Error\n%s\n", error_message);
	return ;
}

void	exit_and_free(t_mini *data, char *string)
{
	check_and_free(data);
	print_error(string);
	mlx_destroy_image(data->mlx->mlx, data->img.img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx);
	exit(1);
}

void	free_matrix(double **matrix, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	check_if_error(t_mini *data)
{
	if (data->error.line_error != false)
		exit_and_free(data, "miniRT: Invalid Line");
	if (data->error.multiple_ambient != false)
		exit_and_free(data, "miniRT: Ambient already defined");
	if (data->error.rgb != false)
		exit_and_free(data, ERR_RGB);
	if (data->error.ambient_color != false)
		exit_and_free(data, "miniRT: Invalid Ambient Color");
	if (data->error.ambient_ratio != false)
		exit_and_free(data, "miniRT: Invalid Ambient Ratio");
	if (data->error.multiple_camera != false)
		exit_and_free(data, "miniRT: Multiple Camera");
	if (data->error.camera_view_point != false)
		exit_and_free(data, "miniRT: Invalid Camera View Point");
	if (data->error.camera_orientation != false)
		exit_and_free(data, "miniRT: Invalid Camera Orientation");
	if (data->error.camera_fov != false)
		exit_and_free(data, "miniRT: Invalid Camera FOV");
}


void	check_and_free(t_mini *data)
{
	if (data->index.ambient != 0)
	{
		free(data->light_a);
	}
	if (data->index.camera != 0)
	{
	printf(">>>>>>>>>>>>>>>>>>>>>>>%d\n", data->index.camera);
		free(data->cam);
	}
	if (data->index.light != 0)
	{
		free(data->light);
	}
}
