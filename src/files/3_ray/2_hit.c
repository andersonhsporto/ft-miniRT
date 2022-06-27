/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_hit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:47:33 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/27 01:43:56 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	hit_alternative(t_mini	*data);
t_hit	*hit_sphere(t_mini *data, t_sphere *ptr);
void	hit_list(t_mini *data, t_element *lst);

void	hit(t_mini *data, int x, int y)
{
	data->ray = ray_direction(data, x, y);
	// data->hit = hit_scene_object(data);
	hit_alternative(data);
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

t_hit	*hit_element(t_mini *data, void	*ptr, \
	t_hit *(*f)(t_mini *, void *))
{
	const t_intersec	*intersec = f(data->ray, ptr);
	const t_hit			*hit = hit_point(intersec);

	free((t_intersec *)intersec);
	return (hit);
}

void	hit_list(t_mini *data, t_element *lst)
{
	if (lst->type == sphere)
	{
		data->hit = hit_element(data, lst->ptr, sphere_intersection);
	}
	else if (lst->type == cylinder)
	{
		data->hit = hit_element(data, lst->ptr, cylinder_intersection);
	}
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
		if (data->scene->object[i]->type == 'P')
		{
			intersection = plane_intersection(data->ray);
			hit = hit_point(intersection);
			if (hit)
				return (hit);
		}
		i++;
	}
	return (hit);
}
