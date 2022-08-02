/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_0_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/02 01:04:42 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			rt_mlx_pixel_put(&data->img, x, y, rgb);
		}
	}
	free_mini(data);
}
