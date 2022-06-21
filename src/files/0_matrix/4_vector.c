/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:47:14 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 02:36:17 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*vector_multipli_scalar(double scalar, double *a)
{
	double *res;

	res = (double *)malloc(sizeof(double));
	res[0] = a[0] * scalar;
	res[1] = a[1] * scalar;
	res[2] = a[2] * scalar;
	return (res);
}

double	*vector_normalize_double(double *a)
{
	double	*res;
	double	length;

	length = vector_length_double(a);
	res = (double *)malloc(sizeof(double));
	res[0] = a[0] / length;
	res[1] = a[1] / length;
	res[2] = a[2] / length;
	return (res);
}

double	*vector_addition(double *a, double *b)
{
	double *res;

	res = (double *)malloc(sizeof(double));
	res[0] = a[0] + b[0];
	res[1] = a[1] + b[1];
	res[2] = a[2] + b[2];
	return (res);
}

double	vector_length_double(double *a)
{
	return (sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]));
}

double	*vector_multipli(double *a, double *b)
{
	double *res;

	res = (double *)malloc(sizeof(double));
	res[0] = a[0] * b[0];
	res[1] = a[1] * b[1];
	res[2] = a[2] * b[2];
	return (res);
}
