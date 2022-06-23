/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_direction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 00:18:51 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/23 01:55:46 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*tmp_direction(double wall_size, double wall_nbr, int nbr_x, int nbr_y)
{
	const double	x = (wall_size * 0.5) - (nbr_x * wall_size / RESOLUTION);
	const double	y = (wall_size * 0.5) - (nbr_y * wall_size / RESOLUTION);

	return (create_vector(x, y, wall_nbr));
}

double	*find_direction(double *wall, double w_size, double *cam, int x, int y)
{
	const double	*temp = tmp_direction(w_size, wall[2], x, y);
	const double	*wall_pixel = vector_subtraction(wall, (double *)temp);
	const double	*point = vector_subtraction((double *)wall_pixel, cam);
	double			*direction;

	direction = vector_normalize_double((double *)point);
	free((double *)temp);
	free((double *)wall_pixel);
	free((double *)point);
	return (direction);
}
