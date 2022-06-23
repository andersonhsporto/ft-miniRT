/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_vector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 22:21:54 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/23 02:10:47 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

double	vector_abs(double *a, double *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2]* b[2]);
}

double	*make_point(double x, double y, double z)
{
	double	*res;

	res = (double *)malloc(sizeof(double));
	res[0] = x;
	res[1] = y;
	res[2] = z;
	return (res);
}

double	*vector_zero(void)
{
	return (make_point(0, 0, 0));
}
