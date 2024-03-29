/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 21:43:46 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/01 22:36:31 by anhigo-s         ###   ########.fr       */
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

double	**get_sphere_transform(double radius, t_coo *center)
{
	double	**translate;
	double	**scale;
	double	**transform;

	translate = translation(center->x, center->y, center->z);
	scale = identity(radius, radius, radius);
	transform = matrix_multiply(scale, translate);
	free_matrix(translate, 4);
	free_matrix(scale, 4);
	return (transform);
}

t_sphere_d	*init_sphere(t_mini *data, char **string)
{
	t_sphere_d	*ptr;

	ptr = (t_sphere_d *)malloc(sizeof(t_sphere_d));
	ptr->center = str_to_coo_vector(string[1], &data->error.sp_coord);
	ptr->center.x = ptr->center.x - 2;
	ptr->radius = str_to_double(string[2]) / 2;
	ptr->color = str_to_coo_vector(string[3], &data->error.rgb);
	ptr->transform_id = false;
	if (there_file_error(data))
	{
		return (ptr);
	}
	if (out_range_coo(&ptr->color, 0, 255))
	{
		data->error.rgb = true;
		return (ptr);
	}
	divide_coo(&ptr->color, 255);
	ptr->transform = get_sphere_transform(ptr->radius, &ptr->center);
	ptr->transform_id = true;
	ptr->id = ++data->index.sphere;
	return (ptr);
}

void	lst_new_sphere(t_mini *data, char **string)
{
	t_sphere_d	*ptr;
	t_element	*new_node;

	ptr = init_sphere(data, string);
	if (data->element == NULL)
	{
		data->element = element_new(sphere, data->index.sphere, (void *)ptr);
	}
	else
	{
		new_node = element_new(sphere, data->index.sphere, (void *)ptr);
		element_add_back(&data->element, new_node);
	}
}
