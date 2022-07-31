/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_calculate_orientation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 00:09:55 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/30 21:07:58 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	**get_matrix(t_coo *left, t_coo *true_up, t_coo *forward);

double	**calculate_orientation(t_coo *left, t_coo *true_up, \
									t_coo *forward, t_coo *from)
{
	double	**matrix;
	double	**translate;
	double	**orientation;

	matrix = get_matrix(left, true_up, forward);
	translate = translation(-1.0 * from->x, -1.0 * from->y, -1.0 * from->z);
	orientation = matrix_multiply(matrix, translate);
	free_matrix(matrix, 4);
	free_matrix(translate, 4);
	return (orientation);
}

static double	**get_matrix(t_coo *left, t_coo *true_up, t_coo *forward)
{
	double	**matrix;

	matrix = create_matrix(4, 4);
	matrix[0][0] = left->x;
	matrix[0][1] = left->y;
	matrix[0][2] = left->z;
	matrix[1][0] = true_up->x;
	matrix[1][1] = true_up->y;
	matrix[1][2] = true_up->z;
	matrix[2][0] = -1.0 * forward->x;
	matrix[2][1] = -1.0 * forward->y;
	matrix[2][2] = -1.0 * forward->z;
	matrix[3][3] = 1.0;
	return (matrix);
}
