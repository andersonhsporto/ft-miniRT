/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:04:07 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/23 00:04:29 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*vector_to_double(t_vector vector)
{
	double	*double_vector;

	double_vector = (double *)malloc(sizeof(double) * 3);
	double_vector[0] = vector.x;
	double_vector[1] = vector.y;
	double_vector[2] = vector.z;
	return (double_vector);
}
