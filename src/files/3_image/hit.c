/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:03:51 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/01 23:19:27 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_intersec_list(t_caster *intersect)
{
	int count;
	t_intersec *aux;

	count = 0;
	while (count < intersect->cont)
	{
		aux = intersect->intersec;
		intersect->intersec = intersect->intersec->next;
		free(aux);
		count++;
	}
	free(intersect);
}

void get_hit(int x, int y, t_mini *data)
{
	t_caster *intersec;
	t_element *tmp;

	data->ray = ray_for_pixel(data->cam, x, y);
	intersec = init_intersec_list();
	tmp = data->element;
	while (tmp != NULL)
	{
		if (tmp->type == sphere)
			all_intersec(intersec, &data->ray, tmp->ptr, sphere_intersection);
		else if (tmp->type == cylinder)
			all_intersec(intersec, &data->ray, tmp->ptr, cylinder_intersec);
		else if (tmp->type == plane)
			all_intersec(intersec, &data->ray, tmp->ptr, plane_intersection);
		tmp = tmp->next;
	}
	data->hit = hitter_point(intersec);
	free_intersec_list(intersec);
}

t_intersec *get_shadow_hit(t_coo *over_point, t_coo *path, t_mini *data)
{
	t_caster *intersec;
	t_intersec *hit;
	t_element *tmp;
	t_ray ray;
	t_coo tmp_normalize;

	tmp_normalize = vector_normalize_temp(path);
	ray = create_ray(over_point, &tmp_normalize);
	intersec = init_intersec_list();
	tmp = data->element;
	while (tmp != NULL)
	{
		if (tmp->type == sphere)
			all_intersec(intersec, &ray, tmp->ptr, sphere_intersection);
		else if (tmp->type == cylinder)
			all_intersec(intersec, &ray, tmp->ptr, cylinder_intersec);
		else if (tmp->type == plane)
			all_intersec(intersec, &ray, tmp->ptr, plane_intersection);
		tmp = tmp->next;
	}
	hit = hitter_point(intersec);
	free_intersec_list(intersec);
	return (hit);
}
