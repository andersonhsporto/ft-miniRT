/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:33:43 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/28 23:13:05 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coo	init_light_intensity(t_coo *rgb, double temp_data)
{
	t_coo	light_intensity;
	t_coo	temp0;
	t_coo	temp1;
	t_coo	temp2;

	temp0 = create_vector_temp(1, 1, 1, 0);
	temp1 = vector_normalize_temp(rgb);
	temp2 = vector_multipli_scalar_temp(temp_data, &temp1);
	light_intensity = vector_addition_temp(&temp0, &temp2);
	return (light_intensity);
}

void	get_line_scene(t_mini *data, char *line)
{
	char	**split;

	split = ft_split(line, '+');
	if (matrix_len(split) == 1)
	{
		matrix_free(split);
		return ;
	}
	if (matrix_len(split) < 3)
	{
		printf("%s\n", split[0]);
		print_error("miniRT: Invalid Line");
		exit(0); // free memory
	}
	if (find_ambient(data, split))
		data->light_a = init_ambient(split);
	else if (find_camera(data, split))
		data->cam = init_camera(split);
	else if (find_light(data, split))
		data->light = init_light(split);
	else if (find_sphere(split))
		lst_new_sphere(data, split);
	else if (find_plane(split))
		lst_new_plane(data, split);
	else if (find_cylinder(split))
		lst_new_cylinder(data, split);
	matrix_free(split);
}
