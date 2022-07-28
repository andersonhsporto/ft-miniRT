/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:26:05 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/28 03:28:07 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	*reflect(t_coo *v, t_coo *n)
{
	t_coo	*var;
	t_coo	*res;

	var = vector_multipli_scalar(2.0 * vector_abs(v, n), n);
	res = vector_subtration(v, var);
	free(var);
	return(res);
}

static t_coo	*get_cylinder_normal(double height, t_coo *o_point)
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

t_coo	*normal_object_type(t_coo *o_point, double *obj_type_height)
{
	if (obj_type_height[0] == sphere)
	{
		return (vector_subtration(o_point, create_vector(0, 0, 0, 1)));
	}
	else if (obj_type_height[0] == plane)
		return (create_vector(0, 1, 0, 0));
	else if (obj_type_height[0] == cylinder)
		return (get_cylinder_normal(obj_type_height[1], o_point));
}

t_coo	*normal_at(double **transform, t_coo *w_point, double *obj_type_height)
{
	t_coo	*o_point;
	t_coo	*o_normal;
	t_coo	*w_normal;
	double	**inv_trans;
	double	**transp_trans;

	inv_trans = matrix_inverter(transform);
	o_point = mult_matrix_vector(inv_trans, w_point);
	o_normal = normal_object_type(o_point, obj_type_height);
	transp_trans = matrix_transpose(inv_trans);
	free_matrix(inv_trans, 4);
	w_normal = mult_matrix_vector(transp_trans, o_normal);
	w_normal->w = 0;
	return (vector_normalize(w_normal));
}

void	get_normal_vec(t_element *node, double *ch, t_comps *comps, int obj_pos)
{
	t_cylinder_d	*cy_ptr;
	t_sphere_d		*sp_ptr;
	t_plane_d		*pl_ptr;

	if (node->type == cylinder)
	{
		cy_ptr = (t_cylinder_d *)node->ptr;
		ch[1] = cy_ptr->height;
		comps->normal_vec = normal_at(cy_ptr->transform, &comps->position, ch);
		comps->color = &cy_ptr->color;
	}
	else if (node->type == sphere)
	{
		sp_ptr = (t_sphere_d *)node->ptr;
		comps->normal_vec = normal_at(sp_ptr->transform, &comps->position, ch);
		comps->color = &sp_ptr->color;
	}
	else if (node->type == plane)
	{
		pl_ptr = (t_plane_d *)node->ptr;
		comps->normal_vec = normal_at(pl_ptr->transform, &comps->position, ch);
		comps->color = &pl_ptr->color;
	}
}

static void	get_obj_props(t_comps *comps, int obj_type, int obj_pos, t_mini *data)
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

t_coo	ray_position(t_ray *ray, double t)
{
	const t_coo	temp = vector_multipli_scalar_temp(t, &ray->direction);

	return (vector_addition_temp(&ray->origin, &temp));
}

void	prepare_computations(t_comps *comps, t_ray *rt, t_mini *data)
{
	comps->t = data->hit->t;
	comps->position = ray_position(rt, comps->t);
	comps->eye_vec = vector_multipli_scalar(-1, &rt->direction);
	get_obj_props(comps, data->hit->obj_type, data->hit->obj_pos, data);
	if (vector_abs(comps->normal_vec, comps->eye_vec) < 0)
	{
		comps->inside = 1;
		comps->normal_vec = vector_multipli_scalar(-1, comps->normal_vec);
	}
	else
		comps->inside = 0;
	comps->reflect_vec = reflect(&rt->direction, comps->normal_vec);
	comps->over_point = vector_addition(&comps->position, vector_multipli_scalar(EPSILON, comps->normal_vec));
}

t_caster	*put_intersection_in_cast(t_caster *cast, t_intersec *intersec)
{
	t_intersec	*aux;
	int			cont;
	int			i;

	i = 0;
	aux = cast->intersec;
	if (intersec)
	{
		cont = cast->cont - 1;
		while (i < cont)
		{
			cast->intersec  = cast->intersec->next;
			i++;
		}
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

t_caster	*init_intersec_list(void)
{
	t_caster *list;

	list = (t_caster *)malloc(sizeof(t_caster) * 1);
	list->cont = 0;
	list->intersec = NULL;
	return (list);
}

