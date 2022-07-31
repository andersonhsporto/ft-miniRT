/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_check_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:25:56 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 02:25:24 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_line(char *line);
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
		free(map_line);
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
		exit_and_free(data, "miniRT: Open Error");
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
			exit_and_free(data, "miniRT: Open Error");
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
