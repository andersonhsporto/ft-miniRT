/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:38:35 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 14:51:48 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_args(int argc, char **argv)
{
	if (argc == 2 && check_extension(argv[1]))
	{
		if (check_extension(argv[1]) == 0)
		{
			print_error("miniRT: File Error");
			return (0);
		}
		return (1);
	}
	else
	{
		print_error("miniRT: Invalid Arguments");
		return (0);
	}
}

int	check_extension(char *file)
{
	char	*string;

	string = ft_strrchr(file, '.');
	if (string)
	{
		if (ft_strcmp(string, ".rt") == 0)
		{
			return (1);
		}
	}
	return (0);
}

t_error	init_error_struct(void)
{
	t_error	error;

	error.line_error = 0;
	error.multiple_ambient = 0;
	error.rgb = 0;
	error.ambient_color = 0;
	error.ambient_ratio = 0;
	return (error);
}

void	init_data(t_mini *data)
{
	data->index.ambient = 0;
	data->index.camera = 0;
	data->index.light = 0;
	data->index.sphere = -1;
	data->index.plane = -1;
	data->index.cylinder = -1;
	data->cam = NULL;
	data->light = NULL;
	data->element = NULL;
	data->hit = NULL;
	data->error = init_error_struct();
	data->mlx = (t_mlx *)malloc(sizeof(t_mlx));
	data->mlx->mlx = mlx_init();
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIDTH + 10, HEIGHT + 10, "miniRT");
	data->img.img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
								&data->img.bits_per_pixel,\
								&data->img.line_length,
								&data->img.endian);
}
