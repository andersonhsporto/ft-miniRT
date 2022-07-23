/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/23 02:52:51 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// sort intersections
int	render(t_mini *data)
{
	t_comps		comp;
	t_coo		*rgb;
	t_intersec	*hit;
	int			y;
	int			x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			hit = get_hit(x, y, data);
			if (hit)
			{
				prepare_computations(&comp, data->ray, hit, data);
				rgb = lighting(comp, is_shadowed(&comp, data), data);
				free(hit);
			}
			else
				rgb = create_vector(0, 0, 0, 0);
			rt_mlx_pixel_put(&data->img, x, y, rgb);
		}
	}
	free_data(data);
}
