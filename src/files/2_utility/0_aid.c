/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_aid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:59:46 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/03 19:15:34 by anhigo-s         ###   ########.fr       */
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
	free(string);
	string = NULL;
	return (new_string);
}

int	out_range_double(t_vector vector, double min, double max)
{
	if (vector.x < min || vector.x > max || \
	vector.y < min || vector.y > max)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int	out_range_int(t_vector vector, int min, int max)
{
	if (vector.x < min || vector.x > max || \
	vector.y < min || vector.y > max)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
