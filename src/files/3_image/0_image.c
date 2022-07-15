/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_image.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:09:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/11 00:02:26 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_image(t_mini *data)
{
	int x;
	int y;
	x = HEIGHT;
	while (--x >= 0)
	{
		y = -1;
		while (++y < WIDTH)
		{
			rt_pixel_put_vector(data->img, x, y, get_colors(x, y, data));
			// if (y = 4)
			// 	exit(22);
		}
	}
	mlx_put_image_to_window(data->mlx->mlx,
							data->mlx->win,
							data->img->ptr,
							5, 5);
}
