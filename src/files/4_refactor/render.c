/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/27 00:30:50 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rt_mlx_pixel_put_teste(t_image *data, int x, int y, t_coo rgb)
{
	const int	color = ((int)(255.99 * rgb.x) << 16) + \
						((int)(255.99 * rgb.y) << 8) + \
						((int)(255.99 * rgb.z));
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	render(t_mini *data)
{
	t_comps		comp;
	t_coo		rgb;
	int			y;
	int			x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			get_hit(x, y, data);
			if (data->hit)
			{
				prepare_computations(&comp, &data->ray, data);
				rgb = lighting(comp, is_shadowed(&comp, data), data);
			}
			else
				rgb = create_vector_temp(0, 0, 0, 0);
			rt_mlx_pixel_put_teste(&data->img, x, y, rgb);
		}
	}
	free_mini(data);
}
