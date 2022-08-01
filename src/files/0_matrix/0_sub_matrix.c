/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_sub_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 20:51:02 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:07:38 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**sub_matrix(double	**a, int index[2], int col, int row)
{
	int		cont[2];
	int		idx[2];
	double	**res;

	cont[0] = 0;
	idx[0] = 0;
	res = create_matrix(row, col);
	while (idx[0] < row)
	{
		if (cont[0] == index[0])
			cont[0]++;
		cont[1] = 0;
		idx[1] = 0;
		while (idx[1] < col)
		{
			if (cont[1] == index[1])
				cont[1]++;
			res[idx[0]][idx[1]] = a[cont[0]][cont[1]];
			cont[1]++;
			idx[1]++;
		}
		idx[0]++;
		cont[0]++;
	}
	return (res);
}

double	**create_matrix(int col, int line)
{
	double	**res;
	int		i;

	i = 0;
	res = (double **)malloc(sizeof(double *) * line);
	while (i < line)
	{
		res[i] = (double *)ft_calloc(sizeof(double), col);
		i++;
	}
	return (res);
}
