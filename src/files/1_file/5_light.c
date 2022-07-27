/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:58:53 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/27 00:02:06 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_light(t_mini *data, char **string)
{
	if (ft_strcmp(string[0], "L") == 0)
	{
		if (data->index.camera != 0)
		{
			print_error("miniRT: Light already defined");
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

t_light_d	*init_light(char **string)
{
	t_light_d	*light;

	light = (t_light_d *)malloc(sizeof(t_light_d));
	light->point = str_to_coo_vector_temp(string[1], ERR_LIGHT);
	light->bright = str_to_double(string[2]);
	if (light->bright < 0 || light->bright > 1)
	{
		print_error("miniRT: Invalid Light Intensity");
		exit(1);
	}
	light->ambient = 0.1;
	light->diffuse = 0.9;
	light->specular = 0.4;
	light->shininess = 40.0;
	return (light);
}
