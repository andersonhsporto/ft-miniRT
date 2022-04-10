#include <mlx.h>

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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
	t_data	img;
	int		color;
	int		h = 100;
	int		w = 200;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, w, h, "Hello world!");
	for (int y = h - 1; y != 0; y--)
	{
		for (int x = 0; x < w; x++)
		{
			color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
			my_mlx_pixel_put(&img, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
