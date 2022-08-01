/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_matrix_operations_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:32:28 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/31 22:21:42 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**matrix_multiply(double **a, double **b)
{
	double	**res;
	double	*var;
	int		cont[3];

	cont[0] = 0;
	res = (double **)malloc(sizeof(double *) * 4);
	while (cont[0] < 4)
	{
		var = (double *)malloc(sizeof(double) * 4);
		cont[1] = 0;
		while (cont[1] < 4)
		{
			var[cont[1]] = 0;
			cont[2] = 0;
			while (cont[2] < 4)
			{
				var[cont[1]] += a[cont[0]][cont[2]] * b[cont[2]][cont[1]];
				cont[2]++;
			}
			cont[1]++;
		}
		res[cont[0]] = var;
		cont[0]++;
	}
	return (res);
}

t_coo	mult_matrix_vector_temp(double **m1, t_coo *t1)
{
	t_coo	new_t;
	double	*new;
	size_t	i;
	size_t	j;
	double	current[4];

	i = 0;
	new = (double *)ft_calloc(4, sizeof(double));
	current[0] = t1->x;
	current[1] = t1->y;
	current[2] = t1->z;
	current[3] = t1->w;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new[i] += (m1[i][j] * current[j]);
			j++;
		}
		i++;
	}
	new_t = create_vector_temp(new[0], new[1], new[2], new[3]);
	free(new);
	return (new_t);
}

t_coo	*mult_matrix_vector(double **m1, t_coo *t1)
{
	t_coo	*new_t;
	double	*new;
	size_t	i;
	size_t	j;
	double	current[4];

	i = 0;
	new = (double *)ft_calloc(4, sizeof(double));
	current[0] = t1->x;
	current[1] = t1->y;
	current[2] = t1->z;
	current[3] = t1->w;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new[i] += (m1[i][j] * current[j]);
			j++;
		}
		i++;
	}
	new_t = create_vector(new[0], new[1], new[2], new[3]);
	free(new);
	return (new_t);
}

void	matrix_transpose(double **a)
{
	double	b[4][4];
	int		cont[2];

	cont[0] = 0;
	while (cont[0] < 4)
	{
		cont[1] = 0;
		while (cont[1] < 4)
		{
			b[cont[0]][cont[1]] = a[cont[0]][cont[1]];
			cont[1]++;
		}
		cont[0]++;
	}
	cont[0] = 0;
	while (cont[0] < 4)
	{
		cont[1] = 0;
		while (cont[1] < 4)
		{
			a[cont[0]][cont[1]] = b[cont[1]][cont[0]];
			cont[1]++;
		}
		cont[0]++;
	}
}

double	matrix_determinant(double **a)
{
	double	res;
	double	*sub;
	int		index[2];

	index[0] = 0;
	index[1] = 0;
	sub = (double *)malloc(sizeof(double) * 4);
	while (index[1] < 4)
	{
		sub[index[1]] = cofactor_4x4(a, index);
		index[1]++;
	}
	res = a[0][0] * sub[0] + a[0][1] * sub[1] + a[0][2]
		* sub[2] + a[0][3] * sub[3];
	free(sub);
	sub = NULL;
	return (res);
}
