/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:00 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/27 01:00:33 by anhigo-s         ###   ########.fr       */
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
			hit(data, x, y);
			if (data->hit != NULL)
			{
				lighting = there_is_light(data);
				my_mlx_pixel_put(img, x, y, get_color(lighting));
				free(lighting);
				free(data->hit);
			}
		}
	}
	printf("FIM DO RENDER\n");
	free(data->ray);
}

t_scene	*init_scene(void)
{
	t_scene	*scene = (t_scene *)malloc(sizeof(t_scene));
	scene->cont = 2;
	scene->object = (t_obj_d **)malloc(sizeof(t_obj_d *) * 2);
	scene->object[0] = (t_obj_d*)malloc(sizeof(t_obj_d));
	scene->object[0]->radius = 2.0;
	scene->object[0]->type = 'C';
	scene->object[0]->position = create_vector(0.0, 0.0, 1.0);
	// scene->object[0]->matrix = matrix_identify(1,1,1,1);
	scene->object[1] = (t_obj_d*)malloc(sizeof(t_obj_d));
	scene->object[1]->type = 'P';
	scene->object[1]->position = create_vector(0.0, 0.0, 1.0);
	scene->light = (t_light_d **)malloc(sizeof(t_light_d *));
	scene->light[0] = (t_light_d *)malloc(sizeof(t_light_d));
	scene->light[0]->posi = create_vector(-10, 10, -10);
	scene->light[0]->intensity = create_vector(1.0, 1.0, 1.0);
	return (scene);
}
