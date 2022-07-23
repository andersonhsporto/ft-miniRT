/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/23 02:26:14 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// sort intersections
int	render(t_mini *data)
{
	t_comps		comp;
	t_coo		*rgb;
	t_intersec	*hit;
	int			color;
	int			y;
	int			x;

	y = -1;
	while (++y < NY)
	{
		x = -1;
		while (++x < NX)
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
			color = ((int)(255.99 * rgb->x) << 16) + ((int)(255.99 * rgb->y) << 8) + ((int)(255.99 * rgb->z));
			my_mlx_pixel_put(&data->img, x, y, color);
		}
	}
	free_data(data);
}
