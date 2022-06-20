/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:58:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/12 01:24:31 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vector_dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double	vector_mod(t_vector v)
{
	return (sqrt(vector_dot(v, v)));
}

double	vector_sin(t_vector v)
{
	return (sqrt(1 - (vector_dot(v, v) / (vector_mod(v) * vector_mod(v)))));
}

double	vector_cos(t_vector v)
{
	return (vector_dot(v, v) / (vector_mod(v) * vector_mod(v)));
}


double	sum_square_vector(t_vector v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}