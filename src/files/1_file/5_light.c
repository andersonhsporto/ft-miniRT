/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:58:53 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 20:23:58 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	find_light(t_mini *data, char **string)
{
	if (ft_strcmp(string[0], "L") == 0)
	{
		if (data->index.light != 0)
		{
			print_error("miniRT: Light already defined");
			return (0);
		}
		else
		{
			data->index.light++;
			return (1);
		}
	}
	else
	{
		return (0);
	}
}

t_light_d	*init_light(char **string, t_mini *data)
{
	t_light_d	*light;

	light = (t_light_d *)malloc(sizeof(t_light_d));
	light->point = str_to_coo_vector_temp(string[1], &data->error.light_point);
	light->bright = str_to_double(string[2]);
	if (light->bright < 0 || light->bright > 1)
	{
		data->error.light_bright = true;
	}
	light->ambient = 0.1;
	light->diffuse = 0.9;
	light->specular = 0.4;
	light->shininess = 40.0;
	return (light);
}

t_coo	init_light_intensity(t_coo *rgb, double temp_data)
{
	t_coo	light_intensity;
	t_coo	temp0;
	t_coo	temp1;
	t_coo	temp2;

	temp0 = create_vector_temp(1, 1, 1, 0);
	temp1 = vector_normalize_temp(rgb);
	temp2 = vector_multipli_scalar_temp(temp_data, &temp1);
	light_intensity = vector_addition_temp(&temp0, &temp2);
	return (light_intensity);
}
