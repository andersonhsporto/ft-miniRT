/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:51:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 21:54:18 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_and_free(t_mini *data);

void	print_error(char *error_message)
{
	if (ft_strcmp(error_message, "") != 0)
	{
		printf("Error\n%s\n", error_message);
	}
	return ;
}

void	free_content_node(t_element *node)
{
	t_sphere_d		*sp_ptr;
	t_plane_d		*pl_ptr;
	t_cylinder_d	*cy_ptr;

	if (node->id == sphere)
	{
		sp_ptr = (t_sphere_d *)node->ptr;
		if (sp_ptr->transform_id == true)
			free_matrix(sp_ptr->transform, 4);
	}
	else if (node->id == plane)
	{
		pl_ptr = (t_plane_d *)node->ptr;
		if (pl_ptr->transform_id == true)
			free_matrix(pl_ptr->transform, 4);
	}
	else if (node->id == cylinder)
	{
		cy_ptr = (t_cylinder_d *)node->ptr;
		free_matrix(cy_ptr->transform, 4);
	}
	return ;
}

void	free_element_list(t_mini *data)
{
	t_element	*temp;
	t_element	*head;

	temp = data->element;
	while (temp != NULL)
	{
		head = temp->next;
		free_content_node(temp);
		free(temp->ptr);
		free(temp);
		temp = head;
	}
}


void	exit_and_free(t_mini *data, char *string, int code)
{
	if (code != 0)
	{
		check_and_free(data);
	}
	free_element_list(data);
	print_error(string);
	mlx_destroy_image(data->mlx->mlx, data->img.img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx);
	exit(code);
}

void	free_matrix(double **matrix, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}



void	check_and_free(t_mini *data)
{
	if (data->index.ambient != 0)
	{
		free(data->light_a);
	}
	if (data->index.camera != 0)
	{
		free(data->cam);
	}
	if (data->index.light != 0)
	{
		free(data->light);
	}
}

int	there_file_error(t_mini *data)
{
	if (data->error.line_error != 0 || data->error.multiple_ambient != 0)
	{
		return (1);
	}
	if (data->error.rgb != 0 || data->error.ambient_color != 0)
	{
		return (1);
	}
	if (data->error.ambient_ratio != 0 || data->error.multiple_camera != 0)
	{
		return (1);
	}
	if (data->error.camera_view_point != 0 || data->error.camera_orientation != 0)
	{
		return (1);
	}
	if (data->error.camera_fov != 0 || data->error.light_bright != 0)
	{
		return (1);
	}
	if (data->error.light_point != 0)
	{
		return (1);
	}
	if (data->error.sp_coord != 0 || data->error.pl_coord != 0  || data->error.pl_normalized != 0)
	{
		return (1);
	}
	return (0);
}
