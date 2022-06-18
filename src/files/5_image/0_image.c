/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_image.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:09:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/17 20:57:28 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_color(t_mini *data, double u, double v);

void	print_image(t_mini *data)
{
	int		i;
	int		j;
	double	u;
	double	v;

	i = HEIGHT;
	while (--i >= 0)
	{
		j = -1;
		while (++j < WIDTH)
		{
			u = (double)j / WIDTH;
			v = (double)i / HEIGHT;
			rt_pixel_put_vector(data->img, j, i, get_color(data, u, v));
		}
	}
	mlx_put_image_to_window(data->mlx->mlx, \
							data->mlx->win, \
							data->img->ptr, 0, 0);
}

static t_vector	get_color(t_mini *data, double u, double v)
{
	t_ray ray;

	data->hit_record.min = 0.000001;
	data->hit_record.max = INFINITY;
	ray = ray_image(data, u, v);
	if (hit(data->element, &ray, &data->hit_record))
		return (vector_new(0, 0, 0));
	else
		return (vector_new(176, 224, 230));
}