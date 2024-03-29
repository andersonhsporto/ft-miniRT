/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_strparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:32:01 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/01 22:53:19 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	zero_vector(void)
{
	t_coo	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	vector.w = 0;
	return (vector);
}

t_coo	str_to_coo_vector(char *string, int *error)
{
	t_coo	view_point;
	char	**split;

	split = ft_split(string, ',');
	if (matrix_len(split) != 3)
	{
		*error = 1;
		matrix_free(split);
		return (zero_vector());
	}
	view_point.x = str_to_double(split[0]);
	view_point.y = str_to_double(split[1]);
	view_point.z = str_to_double(split[2]);
	view_point.w = 0;
	matrix_free(split);
	return (view_point);
}
