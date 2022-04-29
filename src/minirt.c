/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/04/28 22:40:10 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

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
	view.cam->horizontal = creat_vector(4.0, 0.0, 0.0);
	view.cam->vertical = creat_vector(0.0, 2.0, 0.0);
	view.cam->origin = creat_vector(0.0, 0.0, 0.0);
	view.cam->lower_left_corner = creat_vector(-2.0, -1.0, -1.0);
	//make sphere
	view.scenes = (t_scene **)malloc(sizeof(t_scene *) * 3);
	view.scenes[0] = (t_scene *)malloc(sizeof(t_scene));
	view.scenes[1] = (t_scene *)malloc(sizeof(t_scene));
	view.scenes[2] = NULL;
	view.scenes[0]->center = creat_vector(0.0, 0.0, -1.0);
	view.scenes[0]->material = creat_vector(0.8, 0.6, 0.2);
	view.scenes[0]->radius = 0.5;
	//make second sphere
	view.scenes[1]->center = creat_vector(0.0, 100.5, -1.0);
	view.scenes[1]->material = creat_vector(0.8, 0.8, 0.8);
	view.scenes[1]->radius = 100;
	make_image(&img, &view);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
