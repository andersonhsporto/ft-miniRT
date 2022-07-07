/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:03:55 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/06 19:51:31 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	all_sphere_intersec(t_caster *cast, t_ray *ray, t_sence *sence)
{
	int	i;

	i = 0;
	while (sence->obj[i])
	{
		cast = put_intersection_in_cast(cast, sphere_intersection(ray, sence->obj[i]));
		i++;
	}
}

void	all_plane_intersec(t_caster *cast, t_ray *ray, t_sence *sence)
{
	int	i;

	i = 0;
	while (sence->plane[i])
	{
		cast = put_intersection_in_cast(cast, plane_intersection(ray, sence->plane[i]));
		i++;
	}
}

t_intersec	*hiter_point(t_caster	*head)
{
	t_intersec	*hit;
	t_intersec	*tmp_intersec;
	t_intersec	*current;

	if (head->intersec == NULL)
		return (NULL);
	current = head->intersec;
	hit = NULL;
	while (current != NULL)
	{
		tmp_intersec = current;
		if (!hit && tmp_intersec->t >= 0)
			hit = tmp_intersec;
		else if (tmp_intersec->t >= 0 && tmp_intersec->t < hit->t)
			hit = tmp_intersec;
		current = current->next;
	}
	if (hit && hit == 0)
		hit = NULL;
	return (hit);
}

