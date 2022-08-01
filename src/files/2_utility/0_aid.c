/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_aid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:59:46 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:55:38 by anhigo-s         ###   ########.fr       */
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
	vector->y < min || vector->y > max || vector->z < min || vector->z > max)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
