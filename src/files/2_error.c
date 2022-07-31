/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:51:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 20:36:42 by anhigo-s         ###   ########.fr       */
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



void	check_and_free(t_mini *data)
{
	if (data->index.ambient != 0)
	{
		free(data->light_a);
	}
	if (data->index.camera != 0)
	{
		free(data->cam);
	}
	if (data->index.light != 0)
	{
		free(data->light);
	}
}

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
	if (data->error.camera_fov != 0 || data->error.light_bright != 0)
	{
		return (1);
	}
	if (data->error.light_point != 0)
	{
		return (1);
	}
	return (0);
}
