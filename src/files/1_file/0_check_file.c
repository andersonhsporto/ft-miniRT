/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_check_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:25:56 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 21:35:48 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_line(char *line);
static void	check_legal_char(char *file, t_mini *data);
static void	start_camera_and_light(t_mini *data);

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
		free(map_line);
		map_line = NULL;
		get_line_scene(data, temp);
		free(temp);
	}
	close(fd);
	check_if_error(data);
	start_camera_and_light(data);
	debug(data);
}

static void	check_legal_char(char *file, t_mini *data)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_and_free(data, "miniRT: Open Error", 1);
	while (fd)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else if (check_line(line))
		{
			close(fd);
			free(line);
			exit_and_free(data, "miniRT: Illegal Character", 1);
		}
		free(line);
	}
	close(fd);
	return ;
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

static void	start_camera_and_light(t_mini *data)
{
	if (data->index.ambient == 1 && data->index.light == 1)
	{
		start_camera(data->cam);
		data->light->intensity = init_light_intensity(&data->light_a->rgb, \
		data->light_a->ratio);
	}
	return ;
}
