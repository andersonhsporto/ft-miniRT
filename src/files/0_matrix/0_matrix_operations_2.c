/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_matrix_operations_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 21:01:11 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:22:34 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vector_abs(t_coo *a, t_coo *b)
{
	if (!a && !b)
		return (0);
	return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

double	**vector_to_matrix(t_coo *a)
{
	double	**res;

	res = (double **)malloc(sizeof(double *));
	res[0] = (double *)malloc(sizeof(double) * 4);
	res[0][0] = a->x;
	res[0][1] = a->y;
	res[0][2] = a->z;
	res[0][3] = a->w;
	return (res);
}

t_coo	*vector_cross(t_coo *a, t_coo *b)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = (a->y * b->z) - (a->z * b->y);
	res->y = (a->z * b->x) - (a->x * b->z);
	res->z = (a->x * b->y) - (a->y * b->x);
	res->w = 0;
	return (res);
}

t_coo	*vector_normalize(t_coo *a)
{
	t_coo	*res;
	double	length;

	length = vector_lenght(a);
	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x / length;
	res->y = a->y / length;
	res->z = a->z / length;
	return (res);
}

t_coo	*create_vector(double x, double y, double z, double w)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = x;
	res->y = y;
	res->z = z;
	res->w = w;
	return (res);
}
