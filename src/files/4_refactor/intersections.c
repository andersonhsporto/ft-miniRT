/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 01:03:55 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/21 00:03:03 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	sort_intersection(t_caster *cast)
{
	double	aux;

	if (cast->cont)
	{
		printf("primeiro %f\n", cast->intersec->t);
		printf("segundo %f\n", cast->intersec->next->t);
		if (cast->intersec->t > cast->intersec->next->t)
		{
			printf("hello\n");
			aux = cast->intersec->t;
			cast->intersec->t = cast->intersec->next->t;
			cast->intersec->next->t = aux;
		}
	}
}

void	all_sphere_intersec(t_caster *cast, t_ray *ray, t_poly *poly, t_sphere *list)
{
	int	i;

	i = 0;
	while (poly->sphere && poly->sphere[i])
	{
		cast = put_intersection_in_cast(cast, sphere_intersection(ray, poly->sphere[i], i));
		//sort_intersection(cast);
		i++;
	}
}

void	all_plane_intersec(t_caster *cast, t_ray *ray, t_poly *poly, t_sphere *list)
{
	int	i;

	i = 0;
	while (poly->plane && poly->plane[i])
	{
		cast = put_intersection_in_cast(cast, plane_intersection(ray, poly->plane[i], i));
		i++;
	}
}

void	all_cylinder_intersec(t_caster *cast, t_ray *ray, t_poly *poly, t_sphere *list)
{
	int	i;

	i = 0;
	while (poly->cylinder && poly->cylinder[i])
	{
		cast = put_intersection_in_cast(cast, cylinder_intersec(ray, poly->cylinder[i], i));
		i++;
	}
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

