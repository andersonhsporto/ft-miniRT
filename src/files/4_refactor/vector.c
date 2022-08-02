/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 01:02:39 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/02 01:02:40 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	vector_normalize_temp(t_coo *a)
{
	t_coo	res;
	double	length;

	length = vector_lenght(a);
	res.x = a->x / length;
	res.y = a->y / length;
	res.z = a->z / length;
	return (res);
}

t_coo	vector_multipli_scalar_temp(double scalar, t_coo *a)
{
	t_coo	res;

	res.x = a->x * scalar;
	res.y = a->y * scalar;
	res.z = a->z * scalar;
	res.w = a->w * scalar;
	return (res);
}

t_coo	vector_addition_temp(t_coo *a, t_coo *b)
{
	t_coo	res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	res.w = a->w + b->w;
	return (res);
}

t_coo	vector_subtraction_temp(t_coo *a, t_coo *b)
{
	t_coo	res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	res.w = a->w - b->w;
	return (res);
}

t_coo	create_vector_temp(double x, double y, double z, double w)
{
	t_coo	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return (res);
}
