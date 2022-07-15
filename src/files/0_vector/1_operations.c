/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:58:47 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/04 21:48:35 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vector_normalize(t_vector v)
{
	t_vector	v_norm;
	double		mod;

	mod = vector_mod(v);
	v_norm.x = v.x / mod;
	v_norm.y = v.y / mod;
	v_norm.z = v.z / mod;
	return (v_norm);
}

t_vector	vector_scale(t_vector v, double k)
{
	t_vector	v_scaled;

	v_scaled.x = v.x * k;
	v_scaled.y = v.y * k;
	v_scaled.z = v.z * k;
	return (v_scaled);
}

t_vector	vector_cross(t_vector v, t_vector w)
{
	t_vector	v_cross;

	v_cross.x = v.y * w.z - v.z * w.y;
	v_cross.y = v.z * w.x - v.x * w.z;
	v_cross.z = v.x * w.y - v.y * w.x;
	return (v_cross);
}
