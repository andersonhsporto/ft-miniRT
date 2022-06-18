/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:21:54 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 01:23:04 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*make_point(double x, double y, double z)
{
	double	*res;

	res = (double *)malloc(sizeof(double));
	res[0] = x;
	res[1] = y;
	res[2] = z;
	return (res);
}

double	*vector_subtraction(double *a, double *b)
{
	double *res;

	res = (double *)malloc(sizeof(double));
	res[0] = a[0] - b[0];
	res[1] = a[1] - b[1];
	res[2] = a[2] - b[2];
	return (res);
}

double	*create_vector(double x, double y, double z)
{
	double	*res;

	res = (double *)malloc(sizeof(double));
	res[0] = x;
	res[1] = y;
	res[2] = z;
	return (res);
}

double	*vector_normalize(double *a)
{
	double	*res;
	double	length;

	length = vector_length(a);
	res = (double *)malloc(sizeof(double));
	res[0] = a[0] / length;
	res[1] = a[1] / length;
	res[2] = a[2] / length;
	return (res);
}

double	vector_abs(double *a, double *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2]* b[2]);
}
