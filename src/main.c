#include "../include/minirt.h"

t_sence *race;
t_coo	*scared;
t_coo	*altetion;
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	hit_sphere(t_coo *origin, t_sence *sphere, t_coo *direction, double t_max, double t_min)
{
	t_coo *oc = vector_subtration(origin, sphere->center);
	double	a = vector_abs(direction, direction);
	double	b = vector_abs(oc, direction);
	double	c = vector_abs(oc, oc) - (sphere->raio*sphere->raio);
	double	discriminant = (b*b)-(a*c);
	if (discriminant > 0)
	{
		double temp = (-b - sqrt(discriminant))/a;
		if (temp < t_max && temp > t_min)
		{
			sphere->t = temp;
			// A + B*t
			t_coo	*var = vector_multipli_scalar(sphere->t, direction);
			sphere->p = vector_addition(origin, var);
			free(var);
			var = vector_subtration(sphere->p, sphere->center);
			sphere->normal = vector_multipli_scalar(1.0/sphere->raio, var);
			free(var);
			return (1);
		}
		temp = (-b + sqrt(discriminant))/a;
		if (temp < t_max && temp > t_min)
		{
			sphere->t = temp;
			// A + B*t
			t_coo	*var = vector_multipli_scalar(sphere->t, direction);
			sphere->p = vector_addition(origin, var);
			free(var);
			var = vector_subtration(sphere->p, sphere->center);
			sphere->normal = vector_multipli_scalar(1.0/sphere->raio, var);
			free(var);
			return (1);
		}
	}
	return (0);
}

int	hiter_point(t_coo *origin, t_sence **hiter, t_coo *direction, t_sence *rec)
{
	double	t_max = __FLT_MAX__;
	double	t_min = 0.001;
	int		hitable = 0;
	for (size_t i = 0; i < 2; i++)
	{
		if (hit_sphere(origin, hiter[i], direction, t_max, t_min))
		{
			hitable = 1;
			t_max = hiter[i]->t;
			race = hiter[i];
		}
	}
	return (hitable);
}

t_coo	*random_unit_sphere(void)
{
	t_coo	*p;
	t_coo	*aux;
	t_coo	var;

	do
	{
		var.x = drand48();var.y = drand48();var.z = drand48();
		aux = vector_multipli_scalar(2.0, &var);
		var.x = 1.0;var.y = 1.0;var.z = 1.0;
		p = vector_subtration(aux, &var);
		free(aux);
	} while (vector_abs(p, p) >= 1.0);
	return (p);
}

t_coo	*reflect(t_coo *v, t_coo *n)
{
	t_coo	*var = vector_multipli_scalar(2.0*vector_abs(v,n),n);
	t_coo	*res = vector_subtration(v, var);
	free(var);
	return(res);
}

int	scatter(t_coo *ray, t_sence *rec)
{
	scared = reflect(vector_normalize(ray),rec->normal);
	altetion = rec->material;
	if (vector_abs(scared, rec->normal) > 0)
		return (1);
	return(0);
}

t_coo	*colory(t_coo *origin, t_coo *direction, t_sence **hiter, int deat)
{
	t_sence *rec;
	if (hiter_point(origin, hiter, direction, rec))
	{
		if (deat < 50 && scatter(direction, race))
		{
			t_coo	*res = vector_multipli(altetion, colory(race->p, scared, hiter, deat+1));
			return (res);
		}
		else
		{
			t_coo	*res = (t_coo *)malloc(sizeof(t_coo));
			res->x = 0.0;res->y = 0.0;res->z = 0.0;
			return(res);
		}
	}
	else
	{
		t_coo	*unity_direction = vector_normalize(direction);
		double t = 0.5 * (unity_direction->y + 1.0);
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
}

int	main(void)
{
	#define NX 200
	#define NY 100
	#define NS 100
	void	*mlx;
	void	*mlx_win;
	int		color;
	t_data	img;
	t_coo	*aux;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, NX, NY);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_win = mlx_new_window(mlx, NX, NY, "Hello world!");
	t_coo	lower;
	lower.x = -2.0;lower.y = -1.0;lower.z = -1.0;
	t_coo	h;
	h.x = 4.0;h.y = 0.0;h.z = 0.0;
	t_coo	vertical;
	vertical.x = 0.0;vertical.y = 2.0;vertical.z = 0.0;
	t_coo	origin;
	origin.x = 0.0;origin.y = 0.0;origin.z = 0.0;
	t_sence **hiter = (t_sence **)malloc(sizeof(t_sence *) * 2);
	hiter[0] = (t_sence *)malloc(sizeof(t_sence));
	hiter[1] = (t_sence *)malloc(sizeof(t_sence));
	hiter[0]->raio = 0.5;
	t_coo	metal;
	metal.x = 0.8;metal.y = 0.6;metal.z = 0.2;
	hiter[0]->material = &metal;
	t_coo	sphere;
	sphere.x = 0.0;sphere.y = 0.0;sphere.z = -1.0;
	hiter[0]->center = &sphere;
	t_coo	back;
	back.x = 0.0;back.y = 100.5;back.z = -1.0;
	hiter[1]->center = &back;
	hiter[1]->raio = 100;
	t_coo	mate;
	metal.x = 0.8;metal.y = 0.8;metal.z = 0.8;
	hiter[1]->material = &mate;
	t_coo *cc = (t_coo *)malloc(sizeof(t_coo));
	cc->x = 0.0;cc->y = 0.0;cc->z = 0.0;
	for (size_t i = NY - 1; i > 0; i--)
	{
		for (size_t j = 0; j < NX; j++)
		{
			t_coo *cc = (t_coo *)malloc(sizeof(t_coo));
			cc->x = 0.0;cc->y = 0.0;cc->z = 0.0;
			for (size_t s = 0; s < NS; s++)
			{
				double	u = (double)j/(double)NX;
				double	v = (double)i/(double)NY;
				t_coo	*var = vector_addition(&lower, vector_addition(vector_multipli_scalar(u, &h), vector_multipli_scalar(v, &vertical)));
				t_coo	*ray = vector_subtration(var, &origin);
				free(var);
				aux = colory(&origin, ray, hiter, 0);
				free(ray);
				ray = cc;
				cc = vector_addition(cc, aux);
				free(ray);
				free(aux);
			}
			t_coo	*trt = cc;
			cc = vector_multipli_scalar(1.0/(double)NS, trt);
			free(trt);
			cc->x = sqrt(cc->x);cc->y = sqrt(cc->y);cc->z = sqrt(cc->z);
			color = ((int)(255.99 * cc->x)<<16) + ((int)(255.99 * cc->y)<<8) + ((int)(255.99 * cc->z));
			free(cc);
			my_mlx_pixel_put(&img, j, i, color);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

	// 	if (deat < 50 && scatter(direction, race))
	// 	{
	// 		t_coo	*res = vector_multipli(altetion, colory(race->p, scared, hiter, deat+1));
	// 		return (res);
	// 	}
	// 	else
	// 	{
	// 		t_coo	*res = (t_coo *)malloc(sizeof(t_coo));
	// 		res->x = 0.0;res->y = 0.0;res->z = 0.0;
	// 		return(res);
	// 	}
	// }