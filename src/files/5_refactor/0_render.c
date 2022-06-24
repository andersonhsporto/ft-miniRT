/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:00 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/23 23:43:58 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_mini *data, t_scene *scene, t_image *img)
{
	int		x;
	int		y;
	double	*lighting;

	x = -1;
	while (++x < RESOLUTION)
	{
		y = -1;
		while (++y < RESOLUTION)
		{
			data->ray = ray_direction(data, x, y);
			data->hit = hit_scene_object(data);
			if (data->hit != NULL)
			{
				lighting = there_is_light(data);
				my_mlx_pixel_put(img, x, y, get_color(lighting));
				free(lighting);
				free(data->hit);
			}
		}
	}
	free(data->ray);
}

t_scene	*init_scene(void)
{
	t_scene	*scene = (t_scene *)malloc(sizeof(t_scene));
	scene->cont = 1;
	scene->object = (t_obj_d **)malloc(sizeof(t_obj_d *) * 2);
	scene->object[0] = (t_obj_d*)malloc(sizeof(t_obj_d));
	scene->object[0]->radius = 4.0;
	scene->object[0]->type = 'C';
	scene->object[0]->position = make_point(0.0, 0.0, 1.0);
	scene->object[0]->matrix = matrix_identify(1,1,1,1);
	scene->object[0]->material = (t_material_d *)malloc(sizeof(t_material_d));
	scene->object[0]->material->color = create_vector(1, 0.2, 1.0);
	scene->object[0]->material->ambient = 0.1;
	scene->object[0]->material->diffuse = 0.9;
	scene->object[0]->material->specular = 0.9;
	scene->object[1] = (t_obj_d*)malloc(sizeof(t_obj_d));
	scene->object[1]->type = 'P';
	scene->light = (t_light_d **)malloc(sizeof(t_light_d *));
	scene->light[0] = (t_light_d *)malloc(sizeof(t_light_d));
	scene->light[0]->posi = make_point(-10, 10, -10);
	scene->light[0]->intensity = create_vector(1.0, 1.0, 1.0);
	return (scene);
}
