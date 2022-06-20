/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_matrix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:15:02 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/19 23:23:28 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	matrix_determinant(double **a)
{
	double	res;
	int		jboo;
	int		size = 3;
	int		signal;
	double	matrix[3][3];

	res = 0.0;
	for (int u = 0; u < 4; u++)
	{
		signal = 1.0;
		if (u % 2 == 1)
			signal = -1.0;
		for (int i = 0; i < 3; i++)
		{
			jboo = 0;
			for (int j = 0; j < size; j++)
			{
				if (j == u)
					jboo = 1;
				matrix[i][j] = a[i + 1][j + jboo];
			}
		}
		res += (signal * a[0][u]) * matrix_cofactor(matrix);
	}
	return (res);
}

double	**matrix_multiply(double **a, double **b, int line)
{
	double	**res;
	double	*var;

	res = (double **)malloc(sizeof(double *) * line);
	for (int i = 0; i < line; i++)
	{
		var = (double *)malloc(sizeof(double) * 4);
		for (size_t u = 0; u < 4; u++)
		{
			var[u] = 0;
			for (size_t j = 0; j < 4; j++)
			{
				var[u] += a[i][j] * b[j][u];
			}
		}
		res[i] = var;
	}
	return (res);
}

double	**matrix_identify(double x, double y, double z, double w)
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
	res[3][3] = (double)w;
	return (res);
}
