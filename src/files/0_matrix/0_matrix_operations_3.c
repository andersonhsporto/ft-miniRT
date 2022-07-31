/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_matrix_operations_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:49:18 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/30 21:14:03 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double det_3x3(double **mat)
{
	double result;

	result = (mat[0][0] * mat[1][1] * mat[2][2] +
			  mat[0][1] * mat[1][2] * mat[2][0] +
			  mat[0][2] * mat[1][0] * mat[2][1]) -
			 (mat[2][0] * mat[1][1] * mat[0][2] +
			  mat[2][1] * mat[1][2] * mat[0][0] +
			  mat[2][2] * mat[1][0] * mat[0][1]);
	return (result);
}

double cofactor_4x4(double **a, int index[2])
{
	double **sub;
	double cofactor;

	sub = sub_matrix(a, index, 3, 3);
	if ((index[0] + index[1]) % 2 == 0)
	{
		cofactor = det_3x3(sub);
	}
	else
	{
		cofactor = -1 * det_3x3(sub);
	}
	free_matrix(sub, 3);
	return (cofactor);
}

double **scalar_4x4_matrix(double **mat, double abs)
{
	double **new;
	int i;
	int j;

	i = 0;
	new = create_matrix(4, 4);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new[i][j] = mat[i][j] * abs;
			j++;
		}
		i++;
	}
	return (new);
}

double	**identity(double x, double y, double z)
{
	double	**res;
	int		i;

	i = 0;
	res = (double **)malloc(sizeof(double *) * 4);
	while (i < 4)
	{
		res[i] = (double *)malloc(sizeof(double) * 4);
		i++;
	}
	res[0][0] = (double)x;
	res[0][1] = 0.0;
	res[0][2] = 0.0;
	res[0][3] = 0.0;
	res[1][0] = 0.0;
	res[1][1] = (double)y;
	res[1][2] = 0.0;
	res[1][3] = 0.0;
	res[2][0] = 0.0;
	res[2][1] = 0.0;
	res[2][2] = (double)z;
	res[2][3] = 0.0;
	res[3][0] = 0.0;
	res[3][1] = 0.0;
	res[3][2] = 0.0;
	res[3][3] = 1.0;
	return (res);
}

double **translation(double x, double y, double z)
{
	double **res;

	res = identity(1, 1, 1);
	res[0][3] = x;
	res[1][3] = y;
	res[2][3] = z;
	return (res);
}
