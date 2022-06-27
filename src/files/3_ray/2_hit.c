/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_hit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:47:33 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/27 01:08:46 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_alternative(t_mini	*data);
t_hit	*hit_sphere(t_mini *data, t_sphere *ptr);
void	hit_list(t_mini *data, t_element *lst);

void	hit(t_mini *data, int x, int y)
{
	data->ray = ray_direction(data, x, y);
	data->hit = hit_scene_object(data);
	// hit_alternative(data);
}

void	hit_alternative(t_mini *data)
{
	t_element	*lst;

	lst = data->element;
	data->hit = NULL;
	while (lst != NULL)
	{
		hit_list(data, lst);
		if (data->hit != NULL)
			break ;
		lst = lst->next;
	}
	return ;
}

void	hit_list(t_mini *data, t_element *lst)
{
	if (lst->type == sphere)
	{
		data->hit = hit_sphere(data, lst->ptr);
	}
}

t_hit	*hit_sphere(t_mini *data, t_sphere *ptr)
{
	t_intersec	*intersec;
	t_hit		*hit;

	intersec = sphere_intersection(data->ray, ptr);
	hit = hit_point(intersec, ptr->color);
	return (hit);
}

t_cylinder	*get_cy_in_list(t_element *lst)
{
	t_cylinder	*cy;
	t_element	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (temp->type == cylinder)
		{
			cy = temp->ptr;
			return (cy);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_hit	*hit_scene_object(t_mini *data)
{
	t_intersec	*intersection;
	t_hit		*hit;
	int			i;

	i = 0;
	hit = NULL;
	while (i < data->scene->cont)
	{
		if (data->scene->object[i]->type == 'C')
		{
			t_cylinder	*cy = get_cy_in_list(data->element);
			intersection = cylinder_intersection(data->ray, cy);
			hit = hit_point(intersection, create_vector(0, 0, 1));
			if (hit)
				return(hit);
		}
		if (data->scene->object[i]->type == 'P')
		{
			intersection = plane_intersection(data->ray);
			hit = hit_point(intersection, create_vector(0, 0, 1));
			if (hit)
				return(hit);
		}
		i++;
	}
	return (hit);
}