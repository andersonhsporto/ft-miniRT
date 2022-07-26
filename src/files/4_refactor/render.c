/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/25 22:22:30 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render(t_mini *data)
{
	t_comps		comp;
	t_coo		*rgb;
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
				prepare_computations(&comp, data->ray, data);
				rgb = lighting(comp, is_shadowed(&comp, data), data);
				free(data->hit);
			}
			else
				rgb = create_vector(0, 0, 0, 0);
			rt_mlx_pixel_put(&data->img, x, y, rgb);
		}
	}
	free_data(data);
}
