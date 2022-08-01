/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_0_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 22:56:26 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 23:06:51 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	matrix_free(char **matrix)
{
	int	index;

	index = 0;
	while (matrix[index] != 0)
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
	return ;
}

void	check_and_free(t_mini *data)
{
	if (data->index.ambient != 0)
	{
		free(data->light_a);
	}
	if (data->index.camera != 0)
	{
		free(data->cam);
	}
	if (data->index.light != 0)
	{
		free(data->light);
	}
}
