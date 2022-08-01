/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_strparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:32:01 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/01 01:06:15 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	str_to_coo_vector(char	*string, char *error_message)
{
	t_coo		view_point;
	char		**split;

	split = ft_split(string, ',');
	if (matrix_len(split) != 3)
	{
		print_error(error_message);
		exit(1);
	}
	view_point.x = str_to_double(split[0]);
	view_point.y = str_to_double(split[1]);
	view_point.z = str_to_double(split[2]);
	view_point.w = 0;
	matrix_free(split);
	return (view_point);
}
