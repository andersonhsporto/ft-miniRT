/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:48:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/27 01:31:10 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_cylinder(char **string)
{
	if (ft_strcmp(string[0], "cy") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

t_cylinder	*init_cylinder(char **string)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
	cylinder->coordinates = str_to_double_pointer(string[1], ERR_CYLINDER);
	cylinder->normalized = str_to_double_pointer(string[2], ERR_CYLINDER);
	cylinder->diameter = str_to_double(string[3]);
	cylinder->height = str_to_double(string[4]);
	cylinder->color = str_to_double_pointer(string[5], ERR_CYLINDER);
	if (out_of_range(cylinder->color, 0, 255))
	{
		print_error("miniRT: Invalid Cylinder Color");
		exit(1);
	}
	return (cylinder);
}

void	lst_new_cylinder(t_mini *data, char **string)
{
	t_cylinder	*ptr;

	ptr = init_cylinder(string);
	if (data->element == NULL)
	{
		data->element = element_new(cylinder, (void *)ptr);
	}
	else
	{
		t_element	*new_node = element_new(cylinder, (void *)ptr);
		element_add_back(&data->element, new_node);
	}
}
