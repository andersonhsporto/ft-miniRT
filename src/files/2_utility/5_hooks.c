/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:58:52 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 20:15:04 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	exit_esc(int keycode, t_mini *data)
{
	(void)data;
	if (keycode == ESC)
	{
		exit(0);
	}
	return (0);
}

int	red_cross(t_mini *data)
{
	(void)data;
	exit(0);
	return (0);
}

int	put_image(t_mini *data)
{
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, \
	data->img.img, 0, 0);
	return (0);
}
