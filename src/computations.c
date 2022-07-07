/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:26:05 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/07 11:27:02 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_coo	*reflect(t_coo *v, t_coo *n)
{
	t_coo	*var;
	t_coo	*res;

	var = vector_multipli_scalar(2.0*vector_abs(v,n),n);
	res = vector_subtration(v, var);
	free(var);
	return(res);
}

t_coo	*normal_object_type(t_material *poly, t_coo *o_point, int obj_type)
{
	if (obj_type == SPHERE)
		return (vector_subtration(o_point, create_vector(0, 0, 0, 1)));
	else if (obj_type == PLANE)
		return (create_vector(0, 1, 0, 0));
}

t_coo	*normal_at(double **transform, t_coo *w_point, t_material *poly, int obj_type)
{
	t_coo	*o_point;
	t_coo	*o_normal;
	t_coo	*w_normal;
	double	**inv_trans;
	double	**transp_trans;

	inv_trans = matrix_inverter(transform);
	transp_trans = matrix_transpose(inv_trans);
	o_point = mult_matrix_vector(inv_trans, w_point);
	o_normal = normal_object_type(poly, o_point, obj_type);
	w_normal = mult_matrix_vector(transp_trans, o_normal);
	w_normal->w = 0;
	return (vector_normalize(w_normal));
}

static void	get_obj_props(t_comps *comps, int obj_type, int obj_pos)
{
	if (obj_type == SPHERE)
	{
		comps->normal_vec = normal_at(comps->poly->sphere[obj_pos]->transform,
				comps->position, comps->poly->sphere[obj_pos]->material, obj_type);
		comps->material = comps->poly->sphere[obj_pos]->material;
	}
	if (obj_type == PLANE)
	{
		comps->normal_vec = normal_at(comps->poly->plane[obj_pos]->transform,
				comps->position, comps->poly->plane[obj_pos]->material, obj_type);
		comps->material = comps->poly->plane[obj_pos]->material;
	}
}

void	prepare_computations(t_comps *comps, t_ray *rt, t_intersec *hit, t_light *light, t_poly	*poly)
{
	comps->light = light;
	comps->t = hit->t;
	comps->poly = poly;
	comps->position = ray_position(rt, comps->t);
	comps->eye_vec = vector_multipli_scalar(-1, rt->direction);
	get_obj_props(comps, hit->obj_type, hit->obj_pos);
	if (vector_abs(comps->normal_vec, comps->eye_vec) < 0)
	{
		comps->inside = 1;
		comps->normal_vec = vector_multipli_scalar(-1, comps->normal_vec);
	}
	else
		comps->inside = 0;
	comps->reflect_vec = reflect(rt->direction, comps->normal_vec);
	comps->over_point = vector_addition(vector_multipli_scalar(EPSILON, comps->normal_vec), comps->position);
}

t_coo	*ray_position(t_ray *ray, double t)
{
	return (vector_addition(ray->origin, vector_multipli_scalar(t, ray->direction)));
}

t_caster	*put_intersection_in_cast(t_caster *cast, t_intersec *intersec)
{
	int	i;
	t_intersec	*aux;

	i = 0;
	aux = cast->intersec;
	if (intersec)
	{
		while (i < cast->cont)
		{
			cast->intersec  = cast->intersec->next;
			i++;
		}
		cast->intersec = intersec;
		if (aux)
			cast->intersec = aux;
		cast->cont += 2;
	}
	return (cast);
}

t_caster	*init_intersec_list(t_caster *list)
{
	list->cont = 0;
	list->intersec = NULL;
	return (list);
}

