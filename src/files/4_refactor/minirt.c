/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/16 01:16:09 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static t_coo	*position(t_ray *ray, double t)
// {
// 	const t_coo	*aux = vector_multipli_scalar(t, ray->direction);
// 	t_coo 		*position;

// 	position = vector_addition(ray->origin, aux);
// 	free((t_coo *)aux);
// 	return (position);
// }

// sort intersections
int render(t_image *img)
{
	t_cam		*cam;
	t_ray		*ray;
	t_sphere	*spher;
	t_light		*light;
	t_poly		*poly;
	t_comps		comp;
	int			color;

	int y = 0;
	cam = init_cam();
	spher = init_sphere_re();
	poly = (t_poly *)ft_calloc(sizeof(t_poly), 1);
	// poly->cylinder = (t_cylinder **)malloc(sizeof(t_cylinder *) * 2);
	// poly->cylinder[0] = init_cylinder_re();
	// poly->cylinder[1] = NULL;
	poly->cylinder = NULL;
	// poly->plane = NULL;
	// poly->sphere = NULL;
	poly->sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 3);
	poly->sphere[0] = spher;
	// poly->sphere[0] = init_sphere_re();
	// poly->sphere[0]->center = create_vector(2, 1, 0, 0);
	poly->sphere[1] = NULL;
	poly->plane = (t_plane **)malloc(sizeof(t_plane *) * 2);
	poly->plane[0] = init_plane_re();
	poly->plane[1] = NULL;
	render_plane_transform(poly->plane[0]);
	render_sphere_transform(spher);
	// render_sphere_transform(poly->sphere[0]);
	// render_cylinder_transform(poly->cylinder[0]);
	light = (t_light *)malloc(sizeof(t_light));
	light->posi = create_vector(0, 8, -3, 0);
	light->intensity = create_vector(1, 1, 1, 0);
	t_coo *rgb;

	t_caster *intersec;
	while (y < NY)
	{
		int x = 0;
		while (x < NX)
		{
			ray = ray_for_pixel(cam, x, y);
			// printf("%f %f %f %f\n", ray->direction->x, ray->direction->y, ray->direction->z, ray->direction->w);
			intersec = (t_caster *)malloc(sizeof(t_caster));
			intersec = init_intersec_list(intersec);
			// printf("ray_origin : (%f, %f, %f)\t ray_direction : (%f, %f, %f)\n", ray->origin->x,ray->origin->y, ray->origin->z, ray->direction->x, ray->direction->y, ray->direction->z);

			// intersec = plane_intersection(ray, spher);
			all_sphere_intersec(intersec, ray, poly);
			all_plane_intersec(intersec, ray, poly);
			all_cylinder_intersec(intersec, ray, poly);
			t_intersec *hit = hiter_point(intersec);
			// tem que dar hit quando o y == 78 ou mior
			if (hit)
			{
				prepare_computations(&comp, ray, hit, light, poly);
				// t_coo	*hitposition = position(ray, hit->t);
				// rgb = slighting(hitposition, light, ray->direction, poly->sphere[0]->material, vector_normalize(hitposition), is_shadowed(&comp, light, poly));
				rgb = lighting(comp, light, is_shadowed(&comp, light, poly));
			}
			else
				rgb = create_vector(0, 0, 0, 0);
			color = ((int)(255.99 * rgb->x) << 16) + ((int)(255.99 * rgb->y) << 8) + ((int)(255.99 * rgb->z));
			my_mlx_pixel_put(img, x, y, color);
			// printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
			//  printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
			//  printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
			x++;
		}
		y++;
	}

	// int	i = 0;
	// 	while (i < 4)
	// 	{
	// 		int	y = 0;
	// 		while (y < 4)
	// 		{
	// 			printf("%f ", cam->transform[i][y]);
	// 			y++;
	// 		}
	// 		printf("\n");
	// 		i++;
	// printf("%f %f %f %f\n", ray->direction->x, ray->direction->y, ray->direction->z, ray->direction->w);
	// 	}
}
