/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/21 00:12:03 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// sort intersections
int	render(t_mini *data)
{
	t_comps		comp;
	t_poly		*poly;
	t_coo		*rgb;
	int			color;
	int			y;
	int			x;

	// spher = init_sphere_re();
	poly = (t_poly *)ft_calloc(sizeof(t_poly), 1);
	// poly->cylinder = (t_cylinder **)malloc(sizeof(t_cylinder *) * 2);
	// poly->cylinder[0] = init_cylinder_re();
	// poly->cylinder[1] = NULL;
	// poly->plane = NULL;
	poly->cylinder = NULL;
	poly->sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 3);
	poly->sphere[0] = init_sphere_re();
	// poly->sphere[1] = NULL;
	poly->plane = (t_plane **)malloc(sizeof(t_plane *) * 2);
	poly->plane[0] = init_plane_re();
	render_plane_transform(poly->plane[0]);
	render_sphere_transform(poly->sphere[0]);
	render_sphere_transform(poly->sphere[0]);
	// render_cylinder_transform(poly->cylinder[0]);

	y = 0;
	while (y < NY)
	{
		x = 0;
		while (x < NX)
		{
			t_intersec *hit = get_hit(x, y, data, poly);
			if (hit)
			{
				prepare_computations(&comp, data->ray, hit, poly);
				rgb = lighting(comp, is_shadowed(&comp, poly, data), data);
				if (rgb->x > 1)
					rgb->x = 1;
				if (rgb->y > 1)
					rgb->y = 1;
				if (rgb->z > 1)
					rgb->z = 1;
				free(hit);
			}
			else
				rgb = create_vector(0, 0, 0, 0);
			color = ((int)(255.99 * rgb->x) << 16) + ((int)(255.99 * rgb->y) << 8) + ((int)(255.99 * rgb->z));
			my_mlx_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
	free_data(data);
}
