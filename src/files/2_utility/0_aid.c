/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_aid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:59:46 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:58:45 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_len(char **matrix)
{
	int	index;

	index = 0;
	while (matrix[index])
	{
		index++;
	}
	return (index);
}

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

char	*replace_string(char *string, char character)
{
	int		index;
	char	*new_string;

	index = 0;
	new_string = ft_strdup(string);
	while (new_string[index] != '\0')
	{
		if (new_string[index] == '\t' || new_string[index] == ' ')
		{
			new_string[index] = character;
		}
		index++;
	}
	return (new_string);
}

int	out_range_coo(t_coo *vector, double min, double max)
{
	if (vector->x < min || vector->x > max || \
	vector->y < min || vector->y > max)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
