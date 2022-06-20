/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:00 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/19 23:56:06 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(t_scene *scene, t_image *img, int resolution)
{
	double	*camera = make_point(0, 0, -5);
	double	*wall = make_point(0, 0, 7.0);
	double	wallsize = 7.0;

	t_ray	*ray = (t_ray *)malloc(sizeof(t_ray));
	int	x = 0;
	while (x < resolution)
	{
		int	y = 0;
		while (y < resolution)
		{
			double	increment = wallsize / resolution;
			double	*current_wall_pixel = vector_subtraction(wall, create_vector((wallsize * 0.5) - (x * increment), (wallsize * 0.5) - (y * increment), wall[2]));
			double	*point = vector_subtraction(current_wall_pixel, camera);
			ray->direction = vector_normalize_double(point);
			// ray->direction = direction;
			ray->origin = camera;
			t_hit	*hit = hit_scene_object(ray, scene);
			if (hit != NULL)
			{
				double	*hitposition = position(ray, hit->t);
				double	*lighting = slighting(hitposition, scene->light[0], ray->direction, scene->object[0]->material, vector_normalize_double(hitposition));
				int color = ((int)(255.99 * lighting[0])<<16) + ((int)(255.99 * lighting[1])<<8) + ((int)(255.99 * lighting[2]));
				my_mlx_pixel_put(img, x, y, color);
				free(hitposition);
				free(lighting);
			}
			y++;
		}
		x++;
	}
	free(ray);
}

double	*slighting(double *position, t_light_d *light, double *eye, t_material_d *material, double *normal)
{
	double	*temp = material->color;
	double	*effectivecolor = vector_multipli(temp, light->intensity);
	double	*lightvec = vector_normalize_double(vector_subtraction(light->posi, position));
	double	*ambienteColor = vector_multipli_scalar(material->ambient, temp);
	double	*difusecolor;
	double	*specularcolor;

	double	lDOtn = vector_abs(lightvec, normal);
	if (lDOtn <= 0.0)
	{
		difusecolor = make_point(0.0, 0.0, 0.0);
		specularcolor = make_point(0.0, 0.0, 0.0);
	}
	else
	{
		difusecolor = vector_multipli_scalar(lDOtn, vector_multipli_scalar(material->diffuse, effectivecolor));
		double	*refle = reflect(vector_multipli_scalar(-1.0, lightvec), normal);
		double	rDote = vector_abs(refle, eye);
		if (rDote <= 0.0)
			specularcolor = make_point(0.0, 0.0, 0.0);
		else
		{
			//Shinniness ou Brilho e depois do rDote
			double	factor = pow(rDote, 200.0);
			specularcolor = vector_multipli_scalar(material->specular * factor, light->intensity);
		}
	}
	return vector_addition(vector_addition(ambienteColor, difusecolor), specularcolor);
}

t_scene	*init_scene(void)
{
	t_scene	*scene = (t_scene *)malloc(sizeof(t_scene));
	scene->cont = 1;
	scene->object = (t_obj_d **)malloc(sizeof(t_obj_d *) * 2);
	scene->object[0] = (t_obj_d*)malloc(sizeof(t_obj_d));
	scene->object[0]->radius = 2.0;
	scene->object[0]->type = 'C';
	scene->object[0]->position = make_point(0.0, 0.0, 0.0);
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
