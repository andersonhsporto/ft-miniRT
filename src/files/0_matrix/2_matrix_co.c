/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_matrix_co.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 02:18:51 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/21 02:18:51 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	matrix_cofactor(double a[3][3])
{
	double	res;
	double	signal;
	double	matrix[2][2];
	int		jboo;
	int		size = 2;

	res = 0.0;
	for (int u = 0; u < 3; u++)
	{
		signal = 1.0;
		if (u % 2 == 1)
			signal = -1.0;
		for (int i = 0; i < 2; i++)
		{
			jboo = 0;
			for (int j = 0; j < size; j++)
			{
				if (j == u)
					jboo = 1;
				matrix[i][j] = a[i + 1][j + jboo];
			}
		}
		res += (signal * a[0][u]) * matrix_x_multiply(matrix);
	}
	return (res);
}
