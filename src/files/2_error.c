/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:51:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/01 01:14:12 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_error(char *error_message)
{
	if (ft_strcmp(error_message, "") != 0)
		printf("Error\n%s\n", error_message);
	return ;
}

void	exit_and_free(t_mini *data, char *string, int code)
{
	if (code != 0)
	{
		check_and_free(data);
	}
	free_element_list(data);
	print_error(string);
	mlx_destroy_image(data->mlx->mlx, data->img.img);
	mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	mlx_destroy_display(data->mlx->mlx);
	free(data->mlx->mlx);
	free(data->mlx);
	exit(code);
}
void	free_matrix(double **matrix, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
