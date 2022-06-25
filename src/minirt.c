/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/06/25 16:41:12 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// //cam cordenate
// 	t_coo	*lookfrom = creat_vector(-2.0,2.0,1.0);
// 	t_coo	*lookkat = creat_vector(0.0,0.0,-1.0);
// 	t_coo	*vup = creat_vector(0.0,1.0,0.0);
// 	double	vfov = 90;
// 	double	aspect = (double)NX/(double)NY;
// 	//body
// 	double	theta = vfov*(M_PI/180.0);
// 	double	half_height = tan(theta/2);
// 	double	half_width = aspect * half_height;
// 	t_coo	*w = vector_normalize(vector_subtration(lookfrom, lookkat));
// 	t_coo	*u = vector_normalize(vector_cross(vup, w));t_coo	*v = vector_cross(w, u);
// 	view.cam->origin = lookfrom;
// 	view.cam->lower_left_corner = creat_vector(-half_width, -half_height, -1.0);
// 	view.cam->lower_left_corner = vector_subtration(view.cam->origin, vector_subtration(vector_subtration(vector_multipli_scalar(half_width, u), vector_multipli_scalar(half_height, v)), w));
// 	view.cam->horizontal = vector_multipli_scalar(2*half_width, u);
// 	view.cam->vertical = vector_multipli_scalar(2*half_height, v);
// 	//end cam cordenate

int	main(void)
{
	t_data	img;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, NX, NY);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, NX, NY, "MiniRt");
	t_view	view;
	view.cam = (t_cam *)malloc(sizeof(t_cam));
	double	vfov = 90.0;
	double	aspect = (double)NX/(double)NY;
	double	theta = vfov*M_PI/180;
	double	half_height = tan(theta/2.0);
	double	half_width = aspect * half_height;
	view.cam->horizontal = creat_vector(2*half_width, 0.0, 0.0);
	view.cam->vertical = creat_vector(0.0, 2*half_height, 0.0);
	view.cam->origin = creat_vector(0.0, 0.0, 0.0);
	view.cam->lower_left_corner = creat_vector(-half_width, -half_height, -1.0);
	//make sphere
	view.scenes = (t_scene **)malloc(sizeof(t_scene *) * 3);
	view.scenes[0] = (t_scene *)malloc(sizeof(t_scene));
	view.scenes[1] = (t_scene *)malloc(sizeof(t_scene));
	view.scenes[2] = NULL;
	view.scenes[0]->center = creat_vector(-cos(M_PI/4), 0.0, -1.0);
	view.scenes[0]->material = creat_vector(0.8, 0.6, 0.2);
	view.scenes[0]->radius = 0.5;
	view.scenes[0]->type = 'C';
	//make second sphere
	view.scenes[1]->center = creat_vector(cos(M_PI/4), 100.5, -1.0);
	view.scenes[1]->material = creat_vector(0.8, 0.8, 0.8);
	view.scenes[1]->radius = 100;
	view.scenes[1]->type = 'S';
	make_image(&img, &view);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
