/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:41:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/22 23:21:06 by anhigo-s         ###   ########.fr       */
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

double	**get_plane_transform(t_coo *pos, t_coo *norm)
{
	double	**translate;
	double	**rotate;
	double	**transform;

	translate = translation(pos->x,	pos->y, pos->z);
	rotate = normal_rotation_matrix(norm);
	transform = matrix_multiply(translate, rotate);
	return (transform);
}

t_plane_d	*init_plane(t_mini *data, char **string)
{
	t_plane_d	*plane;

	plane = (t_plane_d *)malloc(sizeof(t_plane_d));
	plane->coordinates = str_to_coo_vector(string[1], ERR_PLANE);
	plane->normalized = str_to_coo_vector(string[2], ERR_PLANE);
	plane->color = str_to_coo_vector(string[3], ERR_PLANE);
	if (out_range_coo(plane->color, 0, 255))
	{
		print_error("miniRT: Invalid Plane Color");
		exit(1);
	}
	divide_coo(plane->color, 255);
	plane->transform = get_plane_transform(plane->coordinates, plane->normalized);
	plane->id = ++data->index.plane;
	return (plane);
}

void	lst_new_plane(t_mini *data, char **string)
{
	t_plane_d	*ptr;
	ptr = init_plane(data, string);
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


