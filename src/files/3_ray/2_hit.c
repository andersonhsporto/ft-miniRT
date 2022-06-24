/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_hit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:47:33 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/24 00:22:50 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			intersection = cylinder_intersection(data->ray, data->scene->object[i]);
			hit = hit_point(intersection);
			if (hit)
				return(hit);
		}
		if (data->scene->object[i]->type == 'S')
		{
			intersection = sphere_intersection(data->ray, data->scene->object[i]);
			hit = hit_point(intersection);
			if (hit)
				return(hit);
		}
		if (data->scene->object[i]->type == 'P')
		{
			intersection = plane_intersection(data->ray);
			hit = hit_point(intersection);
			if (hit)
				return(hit);
		}
		i++;
	}
	return (hit);
}

// int	hit_object(t_mini *data, t_element *element, t_ray *ray)
// {
// 	t_intersec	*intersection;
// 	t_hit		*hit;
// 	int			boolean;

// 	boolean = 0;
// 	if (element->type == sphere)
// 	{
// 		intersection = sphere_intersection(data->ray, data->scene->object[i]);
// 	}
// }