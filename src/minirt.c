/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/11 09:39:52 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


t_ray	*create_ray(t_coo *origin, t_coo *direction)
{
	t_ray	*new;

	new = (t_ray *)malloc(sizeof(t_ray));
	new->origin = origin;
	new->direction = direction;
	return (new);
}

t_ray	*ray_for_pixel(t_cam *cam, int x, int y)
{
	double	x_offset;
	double	y_offset;
	t_coo	*direction;
	t_coo	*test;

	x_offset = (x + 0.5) * cam->pixel_size;
	y_offset = (y + 0.5) * cam->pixel_size;
	test = create_vector(cam->half_width - x_offset, cam->half_height - y_offset, -1, 1);
	direction = vector_normalize(vector_subtration(mult_matrix_vector(cam->transform, test), cam->origin));
	return (create_ray(cam->origin, direction));
}

t_ray	*ray_to_object_space(t_ray *ray, double **matrix)
{
	t_ray	*res;
	double	**inverse;

	res = (t_ray *)malloc(sizeof(t_ray));
	inverse = matrix_inverter(matrix);
	res->direction = mult_matrix_vector(inverse, ray->direction);
	res->origin = mult_matrix_vector(inverse, ray->origin);
	return (res);
}

static t_coo	*position(t_ray *ray, double t)
{
	t_coo	*aux = vector_multipli_scalar(t, ray->direction);
	t_coo	*position = vector_addition(ray->origin, aux);
	return (position);
}

int	render(t_data *img)
{
	t_cam	*cam;
	t_ray	*ray;
	t_sphere	*spher;
	t_light		*light;
	t_poly		*poly;
	int color;
	t_comps	comp;

	int	y = 0;
	cam = init_cam();
	spher = init_sphere();
	poly = (t_poly *)malloc(sizeof(t_poly));
	// poly->cylinder = (t_cylinder **)malloc(sizeof(t_cylinder *) * 2);
	// poly->cylinder[0] = init_cylinder();
	// poly->cylinder[1] = NULL;
	poly->cylinder = NULL;
	poly->plane = NULL;
	poly->sphere = (t_sphere **)malloc(sizeof(t_sphere *) * 3);
	//poly->sphere[0] = spher;
	poly->sphere[0] = init_sphere();
	poly->sphere[0]->center = create_vector(2, 1, 0, 0);
	poly->sphere[1] = NULL;
	// poly->plane = (t_plane **)malloc(sizeof(t_plane *) * 2);
	// poly->plane[0] = init_plane();
	// poly->plane[1] = NULL;
	// render_plane_transform(poly->plane[0]);
	//render_sphere_transform(spher);
	render_sphere_transform(poly->sphere[0]);
	//render_cylinder_transform(poly->cylinder[0]);
	light = (t_light *)malloc(sizeof(t_light));
	light->posi = create_vector(0, 8, -3, 0);
	light->intensity = create_vector(1, 1 ,1 , 0);
	t_coo	*rgb;

	t_caster	*intersec;
	while (y < NY)
	{
		int	x = 0;
		while (x < NX)
		{
			ray = ray_for_pixel(cam, x, y);
			//printf("%f %f %f %f\n", ray->direction->x, ray->direction->y, ray->direction->z, ray->direction->w);
			intersec = (t_caster *)malloc(sizeof(t_caster));
			intersec = init_intersec_list(intersec);
			//printf("ray_origin : (%f, %f, %f)\t ray_direction : (%f, %f, %f)\n", ray->origin->x,ray->origin->y, ray->origin->z, ray->direction->x, ray->direction->y, ray->direction->z);

			//intersec = plane_intersection(ray, spher);
			all_sphere_intersec(intersec, ray, poly);
			all_plane_intersec(intersec, ray, poly);
			all_cylinder_intersec(intersec, ray, poly);
			t_intersec	*hit = hiter_point(intersec);
			if (hit)
			{
				prepare_computations(&comp, ray, hit, light, poly);
				//t_coo	*hitposition = position(ray, hit->t);
				//rgb = slighting(hitposition, light, ray->direction, poly->sphere[0]->material, vector_normalize(hitposition), is_shadowed(&comp, light, poly));
				rgb = lighting(comp, light, is_shadowed(&comp, light, poly));
			}
			else
				rgb = create_vector(0, 0, 0, 0);
			color = ((int)(255.99 * rgb->x)<<16) + ((int)(255.99 * rgb->y)<<8) + ((int)(255.99 * rgb->z));
			my_mlx_pixel_put(img, x, y, color);
	//printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
	// printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
	// printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
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

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, NX, NY, "Ray_Sphere");
	img.img = mlx_new_image(mlx, NX, NY);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	render(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}