/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_matrix_operations_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:47:25 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/30 20:49:04 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	*vector_addition(t_coo *a, t_coo *b)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	res->w = a->w + b->w;
	return (res);
}

t_coo	*vector_multipli(t_coo *a, t_coo *b)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x * b->x;
	res->y = a->y * b->y;
	res->z = a->z * b->z;
	res->w = a->w * b->w;
	return (res);
}

t_coo	*vector_subtraction(t_coo *a, t_coo *b)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	res->w = a->w - b->w;
	return (res);
}

t_coo	*vector_multipli_scalar(double scalar, t_coo *a)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x * scalar;
	res->y = a->y * scalar;
	res->z = a->z * scalar;
	res->w = a->w * scalar;
	return (res);
}

double	vector_lenght(t_coo *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w));
}
