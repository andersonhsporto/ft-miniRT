/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_1_free_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:01:12 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 23:07:16 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_sphere_transform(t_element *node);
static void	free_plane_transform(t_element *node);
static void	free_cylinder_transform(t_element *node);

void	free_content_node(t_element *node)
{
	t_plane_d		*pl_ptr;
	t_cylinder_d	*cy_ptr;

	if (node->type == sphere)
	{
		free_sphere_transform(node);
	}
	if (node->type == plane)
	{
		free_plane_transform(node);
	}
	if (node->type == cylinder)
	{
		free_cylinder_transform(node);
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

static void	free_sphere_transform(t_element *node)
{
	t_sphere_d	*sp_ptr;

	sp_ptr = (t_sphere_d *)node->ptr;
	if (sp_ptr->transform_id == true)
		free_matrix(sp_ptr->transform, 4);
	return ;
}

static void	free_plane_transform(t_element *node)
{
	t_plane_d	*pl_ptr;

	pl_ptr = (t_plane_d *)node->ptr;
	if (pl_ptr->transform_id == true)
		free_matrix(pl_ptr->transform, 4);
	return ;
}

static void	free_cylinder_transform(t_element *node)
{
	t_cylinder_d	*cy_ptr;

	cy_ptr = (t_cylinder_d *)node->ptr;
	if (cy_ptr->transform_id == true)
		free_matrix(cy_ptr->transform, 4);
	return ;
}
