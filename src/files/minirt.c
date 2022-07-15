/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:29:25 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/05/18 21:32:16 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int render(t_data *img);

int	main(int argc, char **argv)
{
	t_mini	data;

	if (check_args(argc, argv))
	{
		void *mlx;
		void *mlx_win;
		t_data img;

		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, NX, NY, "Ray_Sphere");
		img.img = mlx_new_image(mlx, NX, NY);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									 &img.endian);
		render(&img);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
		// init_data(&data);
		// check_file(&data, argv[1]);
		// print_image(&data);
		// mlx_hook(data.mlx->win, KEY_RELEASE, BUTTON_RELEASE, exit_esc, &data);
		// mlx_hook(data.mlx->win, EXPOSE, EXPOSURE_MASK, put_image, &data);
		// mlx_hook(data.mlx->win, DESTROY_NOTIFY, NO_EVENT, red_cross, &data);
		// mlx_loop(data.mlx->mlx);
	}
	return (0);
}
