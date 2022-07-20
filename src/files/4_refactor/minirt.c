/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/20 00:44:28 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//temp3 = vector_multipli_scalar(poly->sphere[0]->material->ambient, temp2)




// sort intersections
int	render(t_mini *data)
{
	t_comps		comp;
	t_poly		*poly;
	int			color;
	int			y;
	int			x;

	// spher = init_sphere_re();
	poly = (t_poly *)ft_calloc(sizeof(t_poly), 1);
	// poly->cylinder = (t_cylinder **)malloc(sizeof(t_cylinder *) * 2);
	// poly->cylinder[0] = init_cylinder_re();
	// poly->cylinder[1] = NULL;
	poly->cylinder = NULL;
	// poly->plane = NULL;
	poly->sphere = NULL;
	poly->sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 3);
	poly->sphere[0] = init_sphere_re();
	poly->sphere[0]->center = create_vector(2, 1, 0, 0);
	// poly->sphere[1] = NULL;
	poly->plane = (t_plane **)malloc(sizeof(t_plane *) * 2);
	poly->plane[0] = init_plane_re();
	poly->plane[1] = NULL;
	render_plane_transform(poly->plane[0]);
	render_sphere_transform(poly->sphere[0]);
	render_sphere_transform(poly->sphere[0]);
	// render_cylinder_transform(poly->cylinder[0]);

	t_coo		*rgb;
	t_caster	*intersec;
	y = 0;
	while (y < NY)
	{
		x = 0;
		while (x < NX)
		{
			data->ray = ray_for_pixel(data->cam, x, y);
			intersec = (t_caster *)malloc(sizeof(t_caster));
			intersec = init_intersec_list(intersec);
			all_sphere_intersec(intersec, data->ray, poly);
			all_plane_intersec(intersec, data->ray, poly);
			all_cylinder_intersec(intersec, data->ray, poly);
			t_intersec *hit = hiter_point(intersec);
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
