/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_check_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:25:56 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/29 13:42:40 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_line(char *line);
static void	exit_and_free(t_mini *data);
static void	check_legal_char(char *file, t_mini *data);

void	check_file(t_mini *data, char *file)
{
	int		fd;
	char	*temp;
	char	*map_line;

	check_legal_char(file, data);
	fd = open(file, O_RDONLY);
	while (fd)
	{
		map_line = get_next_line(fd);
		if (map_line == NULL)
			break ;
		temp = replace_string(map_line, '+');
		get_line_scene(data, temp);
		free(temp);
	}
	close(fd);
	data->light->intensity = init_light_intensity(&data->light_a->rgb, \
												data->light_a->ratio);
	debug(data);
}

static void	check_legal_char(char *file, t_mini *data)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_and_free(data);
	while (fd)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (check_line(line))
		{
			print_error("miniRT: Illegal Character");
			close(fd);
			free(line);
			exit_and_free(data);
		}
		free(line);
	}
	close(fd);
	return ;
}

static void	exit_and_free(t_mini *data)
{
	print_error("miniRT: Open Error");
	mlx_destroy_image(data->mlx->mlx, data->img.img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx);
	exit(1);
}

static int	check_line(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (!legal_char(line[index]) && index > 1)
		{
			return (1);
		}
		index++;
	}
	return (0);
}
