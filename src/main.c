#include "../include/minirt.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	hit_sphere(t_coo *origin, t_coo *center, double radius, t_coo *direction)
{
	t_coo *oc = vector_subtration(origin, center);
	double	a = vector_abs(direction, direction);
	double	b = 2.0 * vector_abs(oc, direction);
	double	c = vector_abs(oc, oc) - (radius*radius);
	double	discriminant = (b*b)-(4*a*c);
	free(oc);
	if (discriminant < 0)
		return (-1.0);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

t_coo	*colory(t_coo *origin, t_coo *direction)
{
	t_coo	center;
	center.x = 0.0;center.y = 0.0;center.z = -1.0;
	double	t = hit_sphere(origin, &center, 0.5, direction);
	if (t > 0.0)
	{
		t_coo	*res = vector_multipli_scalar(t, direction);
		t_coo	*var = vector_addition(origin, res);
		free(res);
		res = vector_subtration(var, &center);
		free(var);
		var = vector_normalize(res);
		var->x++;var->y++;var->z++;
		res = vector_multipli_scalar(0.5, var);
		free(var);
		return (res);
	}
	t_coo	*unity_direction = vector_normalize(direction);
	t = 0.5 * (unity_direction->y + 1.0);
	t_coo	m;
	m.x = 1.0;m.y = 1.0;m.z = 1.0;
	t_coo	b;
	b.x = 0.5;b.y = 0.7;b.z = 1.0;
	t_coo	*multi = vector_multipli_scalar(1.0 - t, &m);
	t_coo	*sec = vector_multipli_scalar(t, &b);
	t_coo	*soma = vector_addition(multi, sec);
	free(multi);
	free(sec);
	return(soma);
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
	t_coo	lower;
	lower.x = -2.0;lower.y = -1.0;lower.z = -1.0;
	t_coo	h;
	h.x = 4.0;h.y = 0.0;h.z = 0.0;
	t_coo	vertical;
	vertical.x = 0.0;vertical.y = 2.0;vertical.z = 0.0;
	t_coo	origin;
	origin.x = 0.0;origin.y = 0.0;origin.z = 0.0;
	for (size_t i = 99; i != 0; i--)
	{
		for (size_t j = 0; j < 199; j++)
		{
			// r << 16 g << 8 b 255
			double	u = (double)j / (double)199;
			double	v = (double)i / (double)99;
			t_coo	*ray = vector_addition(&lower, vector_addition(vector_multipli_scalar(u, &h), vector_multipli_scalar(v, &vertical)));
			t_coo *cc = colory(&origin, ray);
			color = ((int)(255.99 * cc->x)<<16) + ((int)(255.99 * cc->y)<<8) + ((int)(255.99 * cc->z));
			free(cc);
			free(ray);
			my_mlx_pixel_put(&img, j, i, color);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
