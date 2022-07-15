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
		t_data img;

		init_data(&data);
		check_file(&data, argv[1]);
		img.img = mlx_new_image(data.mlx->mlx, NX, NY);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									 &img.endian);
		render(&img);
		mlx_put_image_to_window(data.mlx->mlx, data.mlx->win, img.img, 5, 5);
		// print_image(&data);
		mlx_hook(data.mlx->win, KEY_RELEASE, BUTTON_RELEASE, exit_esc, &data);
		mlx_hook(data.mlx->win, EXPOSE, EXPOSURE_MASK, put_image, &data);
		mlx_hook(data.mlx->win, DESTROY_NOTIFY, NO_EVENT, red_cross, &data);
		mlx_loop(data.mlx->mlx);
	}
	return (0);
}
