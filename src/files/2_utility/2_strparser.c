/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_strparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:32:01 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/16 02:53:32 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// t_vector	*str_to_double_vector(char	*string, char *error_message)
// {
// 	t_vector	*rgb;
// 	char		**split;

// 	split = ft_split(string, ',');
// 	if (matrix_len(split) != 3)
// 	{
// 		print_error(error_message);
// 		exit(1);
// 	}
// 	rgb = (t_vector *)malloc(sizeof(t_vector));
// 	rgb->x = ft_atoi(split[0]);
// 	rgb->y = ft_atoi(split[1]);
// 	rgb->z = ft_atoi(split[2]);
// 	matrix_free(split);
// 	return (rgb);
// }

t_vector	str_to_double_vector(char	*string, char *error_message)
{
	t_vector	view_point;
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
	matrix_free(split);
	return (view_point);
}


t_coo	*str_to_coo_vector(char	*string, char *error_message)
{
	t_coo		*view_point;
	char		**split;

	view_point = (t_coo *)malloc(sizeof(t_coo));
	split = ft_split(string, ',');
	if (matrix_len(split) != 3)
	{
		print_error(error_message);
		exit(1);
	}
	view_point->x = str_to_double(split[0]);
	view_point->y = str_to_double(split[1]);
	view_point->z = str_to_double(split[2]);
	view_point->w = 0;
	matrix_free(split);
	return (view_point);
}