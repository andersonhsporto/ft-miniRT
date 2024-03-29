/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:34:51 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/02 01:14:08 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**matrix_inverter(double **a)
{
	double	**res;
	double	**temp;
	double	abs;
	int		index[2];

	abs = matrix_determinant(a);
	if (abs == 0)
		return (NULL);
	index[0] = 0;
	temp = create_matrix(4, 4);
	while (index[0] < 4)
	{
		index[1] = 0;
		while (index[1] < 4)
		{
			temp[index[0]][index[1]] = cofactor_4x4(a, index);
			index[1]++;
		}
		index[0]++;
	}
	matrix_transpose(temp);
	res = scalar_4x4_matrix(temp, 1.0 / abs);
	free_matrix(temp, 4);
	return (res);
}
