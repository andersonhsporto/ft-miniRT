/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:41:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/04 00:18:38 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_plane(char **string)
{
	if (ft_strcmp(string[0], "pl") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

t_plane	*init_plane(char **string)
{
	t_plane	*plane;
	plane = (t_plane *)malloc(sizeof(t_plane));
	plane->coordinates = str_to_double_vector(string[1], ERR_PLANE);
	plane->normalized = str_to_double_vector(string[2], ERR_PLANE);
	plane->color = str_to_double_vector(string[3], ERR_PLANE);
	if (out_range_int(plane->color, 0, 255))
	{
		print_error("miniRT: Invalid Plane Color");
		exit(1);
	}
	return (plane);
}

void	lst_new_plane(t_mini *data, char **string)
{
	t_plane	*ptr;
	ptr = init_plane(string);
	if (data->element == NULL)
	{
		data->element = element_new(plane, (void *)ptr);
	}
	else
	{
		t_element	*new_node = element_new(plane, (void *)ptr);
		element_add_back(&data->element, new_node);
	}
}


