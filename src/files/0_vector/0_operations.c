/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:58:53 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/04 00:21:02 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vector_new(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vector_sum(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	t_vector	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vector	vector_mult(t_vector v1, double k)
{
	t_vector	v;

	v.x = v1.x * k;
	v.y = v1.y * k;
	v.z = v1.z * k;
	return (v);
}

t_vector	vector_div(t_vector v1, double k)
{
	t_vector	v;

	v.x = v1.x / k;
	v.y = v1.y / k;
	v.z = v1.z / k;
	return (v);
}
