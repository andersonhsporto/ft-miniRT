/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:58:52 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/16 03:46:13 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int exit_esc(int keycode, t_mini *data)
{
	if (keycode == ESC)
	{
		free(data->mlx);
		exit(0);
	}
	return (0);
}

int red_cross(t_mini *data)
{
	free(data->mlx);
	exit(0);
	return (0);
}

void print_image(t_mini *data)
{
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
							data->img.img, 5, 5);
	return;
}
