/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:26:05 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/02 01:16:11 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	*get_cylinder_normal(double height, t_coo *o_point)
{
	double		dist;
	double		min;
	double		max;

	max = height / 2.0;
	min = -1.0 * max;
	dist = pow(o_point->x, 2) + pow(o_point->z, 2);
	if (dist < 1 && (o_point->y >= max - EPSILON))
		return (create_vector(0, 1, 0, 0));
	else if (dist < 1 && (o_point->y <= min + EPSILON))
		return (create_vector(0, -1, 0, 0));
	else
		return (create_vector(o_point->x, 0, o_point->z, 0));
}

void	get_obj_props(t_comps *comps, int obj_type, int obj_pos, t_mini *data)
{
	double		obj_type_cylinder_height[2];
	t_element	*tmp;

	obj_type_cylinder_height[0] = obj_type;
	tmp = data->element;
	while (tmp != NULL)
	{
		if (tmp->type == obj_type && tmp->id == obj_pos)
		{
			get_normal_vec(tmp, obj_type_cylinder_height, comps, obj_pos);
			return ;
		}
		tmp = tmp->next;
	}
}

t_caster	*put_intersection_in_cast(t_caster *cast, t_intersec *intersec)
{
	t_intersec	*aux;
	int			cont;
	int			i;

	i = -1;
	aux = cast->intersec;
	if (intersec)
	{
		cont = cast->cont - 1;
		while (++i < cont)
			cast->intersec = cast->intersec->next;
		if (intersec->next)
			cast->cont++;
		cast->cont++;
		if (aux)
		{
			cast->intersec->next = intersec;
			cast->intersec = aux;
		}
		else
			cast->intersec = intersec;
	}
	return (cast);
}
