/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:51:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/29 00:55:52 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *error_message)
{
	printf("Error\n%s\n", error_message);
	return ;
}

void	free_matrix(double **matrix, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}
