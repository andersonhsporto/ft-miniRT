/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:41:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:02:30 by anhigo-s         ###   ########.fr       */
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
	free_matrix(translate, 4);
	free_matrix(rotate, 4);
	return (transform);
}

t_plane_d	*init_plane(t_mini *data, char **string)
{
	t_plane_d	*plane;

	plane = (t_plane_d *)malloc(sizeof(t_plane_d));
	plane->coordinates = str_to_coo_vector_temp(string[1], &data->error.pl_coord);
	plane->normalized = str_to_coo_vector_temp(string[2], &data->error.pl_normalized);
	plane->color = str_to_coo_vector_temp(string[3], &data->error.rgb);
	plane->transform_id = false;
	if (there_file_error(data))
	{
		return (plane);
	}
	if (out_range_coo(&plane->color, 0, 255))
	{
		data->error.rgb = true;
		return (plane);
	}
	if (out_range_coo(&plane->normalized, 0, 1.0))
	{
		data->error.pl_normalized = true;
		return (plane);
	}
	divide_coo(&plane->color, 255);
	plane->transform = get_plane_transform(&plane->coordinates, &plane->normalized);
	plane->transform_id = true;
	plane->id = ++data->index.plane;
	return (plane);
}

void	lst_new_plane(t_mini *data, char **string)
{
	t_plane_d	*ptr;
	t_element	*new_node;

	ptr = init_plane(data, string);
	if (data->element == NULL)
	{
		data->element = element_new(plane, data->index.plane, (void *)ptr);
	}
	else
	{
		new_node = element_new(plane, data->index.plane, (void *)ptr);
		element_add_back(&data->element, new_node);
	}
}


