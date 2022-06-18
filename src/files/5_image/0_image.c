/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_image.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:09:50 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 01:19:43 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_image(t_img_data *img, t_scene_re *scene)
{
	double	*camera = make_point(0, 0, -5);
	double	*wall = make_point(0,0,7.0);
	double	wallsize = 7.0;
	t_ray_re	*ray = (t_ray_re *)malloc(sizeof(t_ray_re));
	int	x = 0;
	while (x < WIDTH)
	{
		int	y = 0;
		while (y < WIDTH)
		{
			double	increment = wallsize / WIDTH;
			double	*current_wall_pixel = vector_subtraction(wall, creat_vector((wallsize * 0.5) - (x * increment), (wallsize * 0.5) - (y * increment), wall[2]));
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

