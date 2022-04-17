#include "../include/minirt.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	int		color;
	t_data	img;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 200, 100);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, 200, 100, "Hello world!");
	color = (255);
	for (size_t i = 99; i != 0; i--)
	{
		for (size_t j = 0; j < 199; j++)
		{
			my_mlx_pixel_put(&img, j, i, color);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
