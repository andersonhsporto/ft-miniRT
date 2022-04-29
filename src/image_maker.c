/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:16 by algabrie          #+#    #+#             */
/*   Updated: 2022/04/28 22:38:17 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_ray	*gerate_ray(t_cam	*cam, double u, double v)
{
	t_ray	*ray;
	t_coo	*aux;
	t_coo	*var;

	ray = (t_ray *)malloc(sizeof(t_ray));
	ray->origin = cam->origin;
	aux = vector_multipli_scalar(v, cam->horizontal);
	var = vector_multipli_scalar(u, cam->vertical);
	ray->direction = vector_addition(aux, var);
	free(var);
	free(aux);
	var = vector_addition(cam->lower_left_corner, ray->direction);
	free(ray->direction);
	ray->direction = vector_subtration(var, cam->origin);
	return(ray);
}

t_coo	*colory(t_ray *ray, t_scene **hiter, int deat)
{
	t_scene	*rec;

	rec = hiter_point(ray, hiter, rec);
	if (rec)
	{
		t_ray	*scattered;
		t_coo	*attenuation;

		scattered = scatter(ray, rec, scattered);
		if (deat < 50 && scattered)
		{
			attenuation = rec->material;
			t_coo	*res = vector_multipli(attenuation, colory(scattered, hiter, deat+1));
			return (res);
		}
		else
			return(creat_vector(0.0, 0.0, 0.0));
	}
	else
		return (background_3d_color(ray));
}

t_coo	*pixel_gerator(double y, double x, t_view *data)
{
	t_ray	*ray;
	t_coo	*rgb;
	t_coo	*aux;
	int		s;

	s = -1;
	rgb = creat_vector(0.0, 0.0, 0.0);
	while (s++ < (NS - 1))
	{
		ray = gerate_ray(data->cam, y/(double)NY, x/(double)NX);
		aux = colory(ray, data->scenes, 0);
		free(ray);
		//free no ultimo rgb t_coo a = rgb depois free(a);
		rgb = vector_addition(rgb, aux);
		free(aux);
	}
	return (rgb);
}

void	make_image(t_data *img, t_view *view)
{
	t_coo	*col;
	t_coo	*var;
	int		color;

	for (int y = NY - 1; y > 0; y--)
	{
		for (int x = 0; x < NX; x++)
		{
			var = pixel_gerator((double)y, (double)x, view);
			col = vector_multipli_scalar(1.0/(double)NS, var);
			free(var);
			col->x = sqrt(col->x);
			col->y = sqrt(col->y);
			col->z = sqrt(col->z);
			color = ((int)(255.99 * col->x)<<16) + ((int)(255.99 * col->y)<<8) + ((int)(255.99 * col->z));
			free(col);
			my_mlx_pixel_put(img, x, y, color);
		}
	}
}
