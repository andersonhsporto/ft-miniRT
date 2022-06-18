/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_unit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 00:00:37 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/04 00:25:21 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_magnitude(t_vector	vector)
{
	double	magnitude;
	double	temp;

	temp = (pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	magnitude = sqrt(temp);
	return (magnitude);
}

t_vector	unit_vector(t_vector vector)
{
	t_vector	unit_vector;
	double		magnitude;

	magnitude = get_magnitude(vector);
	unit_vector.x = vector.x / magnitude;
	unit_vector.y = vector.y / magnitude;
	unit_vector.z = vector.z / magnitude;
	return (unit_vector);
}

