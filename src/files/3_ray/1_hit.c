/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_hit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 23:47:33 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/19 23:48:44 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	*hit_scene_object(t_ray *ray, t_scene *scene)
{
	t_intersec	*intersection;
	t_hit		*hit;
	int			i;

	i = 0;
	hit = NULL;
	while (i < scene->cont)
	{
		if (scene->object[i]->type == 'C')
		{
			intersection = cylinder_intersection(ray, scene->object[i]);
			hit = hit_point(intersection);
			if (hit)
				return(hit);
		}
		if (scene->object[i]->type == 'S')
		{
			intersection = sphere_intersection(ray, scene->object[i]);
			hit = hit_point(intersection);
			if (hit)
				return(hit);
		}
		if (scene->object[i]->type == 'P')
		{
			intersection = plane_intersection(ray);
			hit = hit_point(intersection);
			if (hit)
				return(hit);
		}
		i++;
	}
	return (hit);
}
