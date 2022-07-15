/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ambient.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:37:42 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/12 23:30:27 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_ambient(t_mini *data, char	**string)
{
	if (ft_strcmp(string[0], "A") == 0)
	{
		if (data->index.ambient != 0)
		{
			print_error("miniRT: Ambient already defined");
			exit(1);
		}
		else
		{
			return (1);
		}
	}
	else
	{
		return (0);
	}
}

t_ambient	*init_ambient(char **string)
{
	t_ambient	*ligth;

	ligth = (t_ambient *)malloc(sizeof(t_ambient));
	ligth->rgb = str_to_double_vector(string[2], "miniRT: Invalid RGB");
	if (ligth->rgb.x < 0 || ligth->rgb.x > 255 || ligth->rgb.y < 0 || \
	ligth->rgb.y > 255 || ligth->rgb.z < 0 || ligth->rgb.z > 255)
	{
		print_error("miniRT: Invalid Ambient Color"); //free !!!!
		exit(1);
	}
	ligth->ratio = str_to_double(string[1]);
	printf(">>>>%f\n", ligth->ratio);
	if (ligth->ratio < 0 || ligth->ratio > 1)
	{
		print_error("miniRT: Invalid Ambient Ratio");	//free !!!!!
		exit(1);
	}
	return (ligth);
}
