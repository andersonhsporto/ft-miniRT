/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_1_shadow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:29:04 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/01 23:34:14 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coo	init_shadow_path(t_comps *comps, t_mini *data);

int	is_shadowed(t_comps *comps, t_mini *data)
{
	t_coo		path;
	double		distance;
	t_intersec	*hit;

	path = init_shadow_path(comps, data);
	distance = vector_abs(&path, &path);
	hit = get_shadow_hit(comps->over_point, &path, data);
	if (hit && (hit->t < distance))
	{
		free(hit);
		return (1);
	}
	else
	{
		free(hit);
		return (0);
	}
}

static t_coo	init_shadow_path(t_comps *comps, t_mini *data)
{
	t_coo	path;

	path = vector_subtraction_temp(&data->light->point, comps->over_point);
	return (path);
}
