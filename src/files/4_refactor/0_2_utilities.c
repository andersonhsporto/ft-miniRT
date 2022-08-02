/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_2_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:10:16 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/02 01:14:16 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	*normal_object_type(t_coo *o_point, double *obj_type_height)
{
	t_coo	*posi;
	t_coo	*sphere_posi;

	if (obj_type_height[0] == sphere)
	{
		posi = create_vector(0, 0, 0, 1);
		sphere_posi = vector_subtraction(o_point, posi);
		free(posi);
		return (sphere_posi);
	}
	else if (obj_type_height[0] == plane)
		return (create_vector(0, 1, 0, 0));
	else if (obj_type_height[0] == cylinder)
		return (get_cylinder_normal(obj_type_height[1], o_point));
	return (create_vector(0, 0, 0, 0));
}

t_coo	*normal_at(double **transform, t_coo *w_point, double *obj_type_height)
{
	double	**inv_trans;
	t_coo	*o_point;
	t_coo	*o_normal;
	t_coo	w_normal;

	inv_trans = matrix_inverter(transform);
	o_point = mult_matrix_vector(inv_trans, w_point);
	o_normal = normal_object_type(o_point, obj_type_height);
	free(o_point);
	matrix_transpose(inv_trans);
	w_normal = mult_matrix_vector_temp(inv_trans, o_normal);
	w_normal.w = 0;
	free_matrix(inv_trans, 4);
	free(o_normal);
	return (vector_normalize(&w_normal));
}

void	get_normal_vec(t_element *node, double *ch, t_comps *comps, int obj_pos)
{
	t_cylinder_d	*cy_ptr;
	t_sphere_d		*sp_ptr;
	t_plane_d		*pl_ptr;

	if (node->type == cylinder && node->id == obj_pos)
	{
		cy_ptr = (t_cylinder_d *)node->ptr;
		ch[1] = cy_ptr->height;
		comps->normal_vec = normal_at(cy_ptr->transform, &comps->position, ch);
		comps->color = &cy_ptr->color;
	}
	else if (node->type == sphere && node->id == obj_pos)
	{
		sp_ptr = (t_sphere_d *)node->ptr;
		comps->normal_vec = normal_at(sp_ptr->transform, &comps->position, ch);
		comps->color = &sp_ptr->color;
	}
	else if (node->type == plane && node->id == obj_pos)
	{
		pl_ptr = (t_plane_d *)node->ptr;
		comps->normal_vec = normal_at(pl_ptr->transform, &comps->position, ch);
		comps->color = &pl_ptr->color;
	}
	return ;
}
