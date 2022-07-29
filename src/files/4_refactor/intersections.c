/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:03:55 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/26 22:35:18 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	all_intersec(t_caster *cast, t_ray *ray, void *list, t_intersec* (f)(t_ray*, void*))
{
	// t_intersec *tmp = f(ray, list);
		cast = put_intersection_in_cast(cast, f(ray, list));
	// if (tmp != NULL)
	// 	free(tmp);
}

t_intersec	*hiter_point(t_caster *head)
{
	t_intersec	*hit;
	t_intersec	*tmp_intersec;
	t_intersec	*current;
	int			i;

	if (head->cont == 0)
		return (NULL);
	hit = NULL;
	current = head->intersec;
	i = 0;
	while (i < head->cont)
	{
		tmp_intersec = current;
		if (hit == NULL && tmp_intersec->t >= 0)
			hit = tmp_intersec;
		else if (tmp_intersec->t >= 0 && tmp_intersec->t < hit->t)
			hit = tmp_intersec;
		current = current->next;
		i++;
	}
	return (hit);
}
