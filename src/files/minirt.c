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

int	main(int argc, char **argv)
{
	t_mini	data;

	if (check_args(argc, argv))
	{
		init_data(&data);
		check_file(&data, argv[1]);
		render(&data);

		print_image(&data);
		mlx_hook(data.mlx->win, KEY_RELEASE, BUTTON_RELEASE, exit_esc, &data);
		mlx_hook(data.mlx->win, EXPOSE, EXPOSURE_MASK, print_image, &data);
		mlx_hook(data.mlx->win, DESTROY_NOTIFY, NO_EVENT, red_cross, &data);
		mlx_loop(data.mlx->mlx);
	}
	return (0);
}
