#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/struct.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

float	*mt_multipli(float a, float *mt)
{
	mt[0] = mt[0] * a;
	mt[1] = mt[1] * a;
	mt[2] = mt[2] * a;
	return (mt);
}

float	*mt_sum(float *a, float *b)
{
	float *res;

	res = (float *)malloc(sizeof(float) * 3);
	res[0] = a[0] + b[0];
	res[1] = a[1] + b[1];
	res[2] = a[2] + b[2];
	return(res);
}

float	mt_lenght(float *v)
{
	return ((float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

float	*unity_vector(float *v)
{
	float	lenght;
	int		i;

	i = 0;
	lenght = mt_lenght(v);
	while (i < 3)
	{
		v[i] = v[i] / lenght;
		i++;
	}
	return (v);
}

float	*colory(float *a, float *direction)
{
	direction = unity_vector(direction);
	float	t = 0.5*(direction[1] + 1.0);
	float	b[] = {1.0, 1.0, 1.0};
	float	colo[] = {0.5, 0.7, 1.0};
	return(mt_sum(mt_multipli(1.0-t, b), colo));
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		ny = 100;
	int		nx = 200;
	float	*test;
	float	vertical[] = {0.0,2.0,0.0};
	float	horizontal[] = {4.0,0.0,0.0};
	float	origin[] = {0.0,0.0,0.0};
	float	lower[] = {-2.0,-1.0,-1.0};

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, nx, ny);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, nx, ny, "Hello world!");
	for (int y = ny - 1; y != 0; y--)
	{
		for (int x = 0; x < nx; x++)
		{
			float v = (float)y / (float)ny;
			float u = (float)x / (float)nx;
			test = colory(origin, mt_sum(lower, mt_sum(mt_multipli(u, horizontal), mt_multipli(v, vertical))));
			//color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
			int color = 255.99*test[0] + 255.99*test[1] + 255.99*test[2];
			printf("color %d ", color);
			my_mlx_pixel_put(&img, x, y, color);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
