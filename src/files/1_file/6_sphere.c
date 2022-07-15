/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:43:46 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/15 20:26:49 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_sphere(char **string)
{
	if (ft_strcmp(string[0], "sp") == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

t_sphere_d	*init_sphere(char **string)
{
	t_sphere_d	*sphere;
	sphere = (t_sphere_d *)malloc(sizeof(t_sphere_d));
	sphere->center = str_to_double_vector(string[1], ERR_SPHERE);
	sphere->diameter = str_to_double(string[2]);
	sphere->color = str_to_double_vector(string[3], ERR_SPHERE);
	if (out_range_int(sphere->color, 0, 255))
	{
		print_error("miniRT: Invalid Sphere Color");
		exit(1);
	}
	return (sphere);
}

void	lst_new_sphere(t_mini *data, char **string)
{
	t_sphere_d	*ptr;
	ptr = init_sphere(string);
	if (data->element == NULL)
	{
		data->element = element_new(sphere, (void *)ptr);
	}
	else
	{
		t_element	*new_node = element_new(sphere, (void *)ptr);
		element_add_back(&data->element, new_node);
	}
}
