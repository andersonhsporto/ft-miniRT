/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_matrix.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:09:11 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/21 02:18:41 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**create_matrix(int col, int line)
{
	double	**res;
	int		i;

	i = 0;
	res = (double **)malloc(sizeof(double *) * line);
	while (i < line)
	{
		res[i] = (double *)malloc(sizeof(double) * col);
		i++;
	}
	return (res);
}

double	matrix_x_multiply(double a[2][2])
{
	return (a[0][0] * a[1][1] - (a[0][1] * a[1][0]));
}

double	**matrix_inverter(double **a, double abs)
{
	double	**res;
	int		jboo;
	int		iboo;
	int		signal = 1.0;
	double	matrix[3][3];

	res = create_matrix(4, 4);
	for (size_t t = 0; t < 4; t++)
	{
		if (t % 2 == 1)
			signal = -1.0;
		for (size_t u = 0; u < 4; u++)
		{
			if ((t % 2 == 0 && u % 2 == 1) || (t % 2 == 1 && u % 2 == 0))
				signal = -1.0;
			iboo = 0;
			for (size_t i = 0; i < 3; i++)
			{
				if (i == t)
					iboo = 1;
				jboo = 0;
				for (size_t j = 0; j < 3; j++)
				{
					if (j == u)
						jboo = 1;
					matrix[i][j] = a[i + iboo][j + jboo];
				}
			}
			res[t][u] = (signal * matrix_cofactor(matrix)) / abs;
			signal = 1.0;
		}
	}
	return (res);
}
