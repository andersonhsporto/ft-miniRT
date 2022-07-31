/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_sub_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:51:02 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/30 20:57:27 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**sub_matrix(double	**a, int index[2], int col, int row)
{
	int		i;
	int		j;
	int		idx[2];
	double	**res;

	i = 0;
	idx[0] = 0;
	res = create_matrix(row, col);
	while (idx[0] < row)
	{
		if (i == index[0])
			i++;
		j = 0;
		idx[1] = 0;
		while (idx[1] < col)
		{
			if (j == index[1])
				j++;
			res[idx[0]][idx[1]] = a[i][j];
			j++;
			idx[1]++;
		}
		idx[0]++;
		i++;
	}
	return (res);
}
