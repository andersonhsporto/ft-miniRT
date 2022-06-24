/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:11:13 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/23 23:06:14 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*light_position(t_ray *ray, double t)
{
	double	*temp = vector_multipli_scalar(t, ray->direction);
	double	*position;

	position = vector_addition(ray->origin, temp);
	free((double *)temp);
	return (position);
}

double	*there_is_light(t_mini *data)
{
	const double	*hitposition = light_position(data->ray, data->hit->t);
	double			*lighting = slighting(hitposition, data->scene->light[0], data->ray->direction, data->scene->object[0]->material);

	free((double *)hitposition);
	return (lighting);
}
