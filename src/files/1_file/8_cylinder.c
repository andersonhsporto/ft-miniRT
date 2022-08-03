/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:48:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/03 13:02:27 by anhigo-s         ###   ########.fr       */
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

double	**get_cylinder_transform(double height, double radius,
								t_coo *pos, t_coo *norm)
{
	double	**translate;
	double	**rotate;
	double	**scale;
	double	**transform;
	double	**temp;

	scale = identity(radius, height * 0.5, radius);
	temp = translation(pos->x, pos->y, pos->z);
	transform = matrix_multiply(temp, scale);
	free_matrix(scale, 4);
	free_matrix(temp, 4);
	rotate = normal_rotation_matrix(norm);
	translate = matrix_multiply(rotate, transform);
	free_matrix(rotate, 4);
	free_matrix(transform, 4);
	return (translate);
}

t_cylinder_d	*init_cylinder(t_mini *data, char **string)
{
	t_cylinder_d	*ptr;

	ptr = (t_cylinder_d *)malloc(sizeof(t_cylinder_d));
	ptr->coordinates = str_to_coo_vector(string[1], &data->error.cy_coord);
	ptr->normalized = str_to_coo_vector(string[2], &data->error.cy_coord);
	ptr->radius = str_to_double(string[3]) / 2;
	ptr->height = str_to_double(string[4]);
	ptr->color = str_to_coo_vector(string[5], &data->error.cy_coord);
	ptr->transform_id = false;
	if (out_range_coo(&ptr->normalized, -1, 1))
		data->error.cy_coord = true;
	if (out_range_coo(&ptr->color, 0, 255))
		data->error.rgb = true;
	if (there_file_error(data))
		return (ptr);
	divide_coo(&ptr->color, 255);
	ptr->transform = get_cylinder_transform(ptr->height, \
											ptr->radius, \
											&ptr->coordinates, \
											&ptr->normalized);
	ptr->transform_id = true;
	ptr->id = ++data->index.cylinder;
	return (ptr);
}

void	lst_new_cylinder(t_mini *data, char **string)
{
	t_cylinder_d	*ptr;
	t_element		*new_node;

	ptr = init_cylinder(data, string);
	if (data->element == NULL)
	{
		data->element = element_new(2, data->index.cylinder, (void *)ptr);
	}
	else
	{
		new_node = element_new(cylinder, data->index.cylinder, (void *)ptr);
		element_add_back(&data->element, new_node);
	}
}
