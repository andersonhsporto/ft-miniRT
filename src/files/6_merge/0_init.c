/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 21:59:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 01:19:43 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene_re	*init_seine(void)
{
	t_scene_re	*scene = (t_scene_re *)malloc(sizeof(t_scene_re));
	scene->cont = 1;
	scene->object = (t_obj_re **)malloc(sizeof(t_obj_re *) * 2);
	scene->object[0] = (t_obj_re*)malloc(sizeof(t_obj_re));
	scene->object[0]->radius = 2.0;
	scene->object[0]->type = 'C';
	scene->object[0]->position = make_point(0.0, 0.0, 0.0);
	scene->object[0]->matrix = matrix_identify(1,1,1,1);
	scene->object[0]->material = (t_material_re *)malloc(sizeof(t_material_re));
	scene->object[0]->material->color = creat_vector(1, 0.2, 1.0);
	scene->object[0]->material->ambient = 0.1;
	scene->object[0]->material->diffuse = 0.9;
	scene->object[0]->material->specular = 0.9;
	scene->object[1] = (t_obj_re*)malloc(sizeof(t_obj_re));
	scene->object[1]->type = 'P';
	scene->light = (t_light_re **)malloc(sizeof(t_light_re *));
	scene->light[0] = (t_light_re *)malloc(sizeof(t_light_re));
	scene->light[0]->posi = make_point(-10, 10, -10);
	scene->light[0]->intensity = creat_vector(1.0, 1.0, 1.0);
	return (scene);
}

void	render(t_scene_re *scene, t_img_data *img, int resolution)
{
	t_ray_re	*ray = (t_ray_re *)malloc(sizeof(t_ray_re));
	double		*camera = make_point(0, 0, -5);
	double		*wall = make_point(0,0,7.0);
	double		wallsize = 7.0;
	int	x = 0;
	while (x < resolution)
	{
		int	y = 0;
		while (y < resolution)
		{
			double	increment = wallsize / resolution;
			double	*current_wall_pixel = vector_subtraction(wall, create_vector((wallsize * 0.5) - (x * increment), (wallsize * 0.5) - (y * increment), wall[2]));
			double	*point = vector_subtraction(current_wall_pixel, camera);
			double	*direction = vector_normalize(point);
			ray->direction = direction;
			ray->origin = camera;
			t_hit_re	*hit = hiter_seine_object(ray, scene);
			if(hit != NULL)
			{
				double	*hitposition = position(ray, hit->t);
				double	*lighting = slighting(hitposition, scene->light[0], ray->direction, scene->object[0]->material, vector_normalize(hitposition));
				int color = ((int)(255.99 * lighting[0])<<16) + ((int)(255.99 * lighting[1])<<8) + ((int)(255.99 * lighting[2]));
				my_mlx_pixel_put(img, x, y, color);
			}
			y++;
		}
		x++;
	}
}
