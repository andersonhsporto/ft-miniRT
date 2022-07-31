/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ambient.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 23:37:42 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 14:52:05 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_ambient(t_mini *data, char	**string)
{
	if (ft_strcmp(string[0], "A") == 0)
	{
		if (data->index.ambient == 0)
		{
			data->index.ambient++;
			return (1);
		}
		else
		{
			data->error.multiple_ambient = true;
			return (0);
		}
	}
	else
	{
		return (0);
	}
}

t_ambient	*init_ambient(char **string, t_mini *data)
{
	t_ambient	*light;

	light = (t_ambient *)malloc(sizeof(t_ambient));
	light->rgb = str_to_coo_vector_temp(string[2], &data->error.rgb);
	if (light->rgb.x < 0 || light->rgb.x > 255 || light->rgb.y < 0 || \
	light->rgb.y > 255 || light->rgb.z < 0 || light->rgb.z > 255)
	{
		data->error.ambient_color = true;
		return (light);
	}
	divide_coo(&light->rgb, 255);
	light->ratio = str_to_double(string[1]);
	if (light->ratio < 0 || light->ratio > 1)
	{
		data->error.ambient_ratio = true;
	}
	return (light);
}
