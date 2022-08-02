/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:03:55 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/01 23:25:14 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_intersec	*hitter_point_helper(t_intersec *hit);

void	all_intersec(t_caster *cast, t_ray *ray, void *list, \
t_intersec *(f)(t_ray *, void *))
{
	cast = put_intersection_in_cast(cast, f(ray, list));
}

t_intersec	*hitter_point(t_caster *head)
{
	t_intersec	*hit;
	t_intersec	*tmp_intersec;
	t_intersec	*current;
	int			index;

	if (head->cont == 0)
		return (NULL);
	hit = NULL;
	current = head->intersec;
	index = -1;
	while (++index < head->cont)
	{
		tmp_intersec = current;
		if (hit == NULL && tmp_intersec->t >= 0)
			hit = tmp_intersec;
		else if (tmp_intersec->t >= 0 && tmp_intersec->t < hit->t)
			hit = tmp_intersec;
		current = current->next;
	}
	if (hit)
		hit = hitter_point_helper(hit);
	return (hit);
}

static t_intersec	*hitter_point_helper(t_intersec *hit)
{
	t_intersec	*tmp_intersec;

	tmp_intersec = (t_intersec *)malloc(sizeof(t_intersec));
	tmp_intersec->t = hit->t;
	tmp_intersec->obj_pos = hit->obj_pos;
	tmp_intersec->obj_type = hit->obj_type;
	tmp_intersec->next = NULL;
	return (tmp_intersec);
}
