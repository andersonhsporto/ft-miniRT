/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 20:48:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/29 12:26:58 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_cylinder(char	**string)
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

double	**cy_transform(double height, double radius, t_coo *pos, t_coo *norm)
{
	double	**translate;
	double	**rotate;
	double	**scale;
	double	**transform;

	scale = identity(radius, (height * 0.5), radius);
	translate = translation(pos->x,	pos->y, pos->z);
	transform = matrix_multiply(translate, scale);
	free_matrix(scale, 4);
	free_matrix(translate, 4);
	rotate = normal_rotation_matrix(norm);
	translate = matrix_multiply(rotate, transform);
	free_matrix(rotate, 4);
	free_matrix(transform, 4);
	return (translate);
}

t_cylinder_d	*init_cylinder(t_mini *data, char **string)
{
	t_cylinder_d *cylinder;

	cylinder = (t_cylinder_d *)malloc(sizeof(t_cylinder_d));
	cylinder->coordinates = str_to_coo_vector_temp(string[1], ERR_CYLINDER);
	cylinder->normalized = str_to_coo_vector_temp(string[2], ERR_CYLINDER);
	cylinder->radius = str_to_double(string[3]) / 2;
	cylinder->height = str_to_double(string[4]);
	cylinder->color = str_to_coo_vector_temp(string[5], ERR_CYLINDER);
	if (out_range_coo(&cylinder->color, 0, 255))
	{
		print_error("miniRT: Invalid Cylinder Color");
		exit(1);
	}
	divide_coo(&cylinder->color, 255);
	cylinder->transform = cy_transform(cylinder->height,
										   cylinder->radius,
										   &cylinder->coordinates,
										   &cylinder->normalized);
	cylinder->id = ++data->index.cylinder;
	return (cylinder);
}

void lst_new_cylinder(t_mini *data, char **string)
{
	t_cylinder_d *ptr;
	t_element *new_node;

	ptr = init_cylinder(data, string);
	if (data->element == NULL)
	{
		data->element = element_new(cylinder, data->index.cylinder, (void *)ptr);
	}
	else
	{
		new_node = element_new(cylinder, data->index.cylinder, (void *)ptr);
		element_add_back(&data->element, new_node);
	}
}
