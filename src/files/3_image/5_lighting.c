/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_lighting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 00:07:08 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/11 21:43:59 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

struct s_light
{
	t_vector	orig;
	t_vector	light_color;
	double		bright_ratio;
}	t_test;

t_vector	get_light_vector(t_mini *data)
{
	t_vector	color;
	t_vector	light_dir;

	color = vector_new(0, 0, 0);
	light_dir = unit_vector(vector_sub(data->light->orig, data->cam->orig));
	return (vector);
}