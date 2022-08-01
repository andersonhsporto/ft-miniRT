/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:58:52 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:58:33 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_mini(t_mini *data)
{
	free(data->light_a);
	free_matrix(data->cam->transform, 4);
	free(data->cam);
	free(data->light);
}

int	exit_esc(int keycode, t_mini *data)
{
	if (keycode == ESC)
	{
		free(data->mlx);
		exit(0);
	}
	return (0);
}

int	red_cross(t_mini *data)
{
	free(data->mlx);
	exit(0);
	return (0);
}

int	print_image(t_mini *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->img.img, 5, 5);
	return (1);
}
