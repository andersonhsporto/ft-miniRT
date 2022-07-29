/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_check_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:28:43 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:13:24 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_line(char *line);

void	check_file(t_mini *data, char *file)
{
	int		fd;
	char	*temp;
	char	*map_line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error("miniRT: Open Error");
		exit (1);
	}
	while (fd)
	{
		map_line = get_next_line(fd);
		if (map_line == NULL || check_line(map_line))
			break ;
		temp = replace_string(map_line, '+');
		get_line_scene(data, temp);
		free(temp);
	}
	close(fd);
	debug(data);
	data->light->intensity = init_light_intensity(&data->light_a->rgb, data->light_a->ratio);
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
			print_error("miniRT: Illegal Character");
			exit(1); //free memory
			return (1);
		}
		index++;
	}
	return (0);
}

