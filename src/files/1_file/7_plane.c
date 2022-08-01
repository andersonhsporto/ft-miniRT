/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:41:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:48:20 by anhigo-s         ###   ########.fr       */
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

	translate = translation(pos->x, pos->y, pos->z);
	rotate = normal_rotation_matrix(norm);
	transform = matrix_multiply(translate, rotate);
	free_matrix(translate, 4);
	free_matrix(rotate, 4);
	return (transform);
}

t_plane_d	*init_plane(t_mini *data, char **string)
{
	t_plane_d	*ptr;

	ptr = (t_plane_d *)malloc(sizeof(t_plane_d));
	ptr->coordinates = str_to_coo_vector(string[1], &data->error.pl_coord);
	ptr->normalized = str_to_coo_vector(string[2], &data->error.pl_normalized);
	ptr->color = str_to_coo_vector(string[3], &data->error.rgb);
	ptr->transform_id = false;
	if (there_file_error(data))
		return (ptr);
	if (out_range_coo(&ptr->color, 0, 255))
	{
		data->error.rgb = true;
		return (ptr);
	}
	if (out_range_coo(&ptr->normalized, 0, 1.0))
	{
		data->error.pl_normalized = true;
		return (ptr);
	}
	divide_coo(&ptr->color, 255);
	ptr->transform_id = true;
	ptr->transform = get_plane_transform(&ptr->coordinates, &ptr->normalized);
	ptr->id = ++data->index.plane;
	return (ptr);
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
