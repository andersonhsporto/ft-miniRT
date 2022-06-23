/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:11:13 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/23 00:14:16 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*position(t_ray *ray, double t)
{
	const double	*temp = vector_multipli_scalar(t, ray->direction);
	double			*position;

	position = vector_addition(ray->origin, temp);
	free(temp);
	return (position);
}

// double	*there_is_light(t_mini *data, t_hit hit)

// double	*hitposition = position(data->ray, hit->t);
// double	*lighting = slighting(hitposition, scene->light[0], data->ray->direction, scene->object[0]->material, vector_normalize_double(hitposition));