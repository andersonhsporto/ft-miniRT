/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:13:10 by algabrie          #+#    #+#             */
/*   Updated: 2022/07/04 11:02:29 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


double	**identity(double x, double y, double z)
{
	double	**res;
	int		i;

	i = 0;
	res = (double **)malloc(sizeof(double *) * 4);
	while (i < 4)
	{
		res[i] = (double *)malloc(sizeof(double) * 4);
		i++;
	}
	res[0][0] = (double)x;res[0][1] = 0.0;res[0][2] = 0.0;res[0][3] = 0.0;
	res[1][0] = 0.0;res[1][1] = (double)y;res[1][2] = 0.0;res[1][3] = 0.0;
	res[2][0] = 0.0;res[2][1] = 0.0;res[2][2] = (double)z;res[2][3] = 0.0;
	res[3][0] = 0.0;res[3][1] = 0.0;res[3][2] = 0.0;res[3][3] = 1.0;
	return (res);
}

double	**translation(double x, double y, double z)
{
	double	**res;

	res = identity(1, 1, 1);
	res[0][3] = x;
	res[1][3] = y;
	res[2][3] = z;
	return (res);
}

static double	**calculate_orientation(t_coo *left, t_coo *true_up, t_coo *forward, t_coo *from)
{
	double	**matrix;
	double	**translate;
	double	**orientation;

	matrix = create_matrix(4, 4);
	matrix[0][0] = left->x;
	matrix[0][1] = left->y;
	matrix[0][2] = left->z;
	matrix[1][0] = true_up->x;
	matrix[1][1] = true_up->y;
	matrix[1][2] = true_up->z;
	matrix[2][0] = -1.0 * forward->x;
	matrix[2][1] = -1.0 * forward->y;
	matrix[2][2] = -1.0 * forward->z;
	matrix[3][3] = 1.0;
	translate =  translation(-1.0 * from->x, -1.0 * from->y, -1.0 * from->z);
	orientation = matrix_multiply(matrix, translate);
	return (orientation);
}

double	**view_transform(t_coo *from, t_coo *to, t_coo *up)
{
	t_coo		*forward;
	t_coo		*up_normal;
	t_coo		*left;
	t_coo		*true_up;

	forward = vector_normalize(vector_subtration(to, from));
	up_normal = vector_normalize(up);
	left = vector_cross(forward, up_normal);
	true_up = vector_cross(left, forward);
	return (calculate_orientation(left, true_up, forward, from));
}

void	camera_pixel_size(int width, int height, t_cam *cam)
{
	double	half_view;
	double	aspect;
	double	rad;

	rad = (cam->fov * M_PI)/180;
	half_view = tan(rad / 2);
	aspect = (double)width / (double)height;
	if (aspect >= 1)
	{
		cam->half_width = half_view;
		cam->half_height = half_view / aspect;
	}
	else
	{
		cam->half_width = half_view * aspect;
		cam->half_height = half_view;
	}
	cam->pixel_size = (cam->half_width * 2) / width;
}

t_cam	*init_cam(void)
{
	t_cam	*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	cam->fov = 85;
	cam->view = create_vector(0, 0.5, -8, 0);
	cam->pos = create_vector(0, 0, 1, 0);
	cam->transform = view_transform(cam->view, vector_addition(cam->view, cam->pos),
		vector_cross(vector_cross(cam->pos, create_vector(0, 1, 0, 0)), cam->pos));
	cam->transform = matrix_inverter(cam->transform);
	camera_pixel_size(NX, NY, cam);
	//printf("half_height : %f, half_width : %f, pixel_size : %f\n", cam->half_height, cam->half_width, cam->pixel_size);
	cam->origin = mult_matrix_vector(cam->transform, create_vector(0, 0, 0, 1));
	return(cam);
}

t_ray	*create_ray(t_coo *origin, t_coo *direction)
{
	t_ray	*new;

	new = (t_ray *)malloc(sizeof(t_ray));
	new->origin = origin;
	new->direction = direction;
	return (new);
}

t_ray	*ray_for_pixel(t_cam *cam, int x, int y)
{
	double	x_offset;
	double	y_offset;
	t_coo	*direction;
	t_coo	*test;

	x_offset = (x + 0.5) * cam->pixel_size;
	y_offset = (y + 0.5) * cam->pixel_size;
	//printf("x_offset : %f, y_offset : %f\n", x_offset, y_offset);
	test = create_vector(cam->half_width - x_offset, cam->half_height - y_offset, -1, 1);
	direction = vector_normalize(vector_subtration(mult_matrix_vector(cam->transform, test), cam->origin));
	//printf("vector : (%f, %f, %f)\n",test->x, test->y, test->z);
	//printf("ray_direction : (%f, %f, %f)\n",direction->x, direction->y, direction->z);
	return (create_ray(cam->origin, direction));
}

void	render_sphere_transform(t_sphere *sphere)
{
	double	**translate;
	double	**scale;
	double	**transform;

	translate = translation(sphere->center->x,
		sphere->center->y, sphere->center->z);
	scale = identity(sphere->radius, sphere->radius, sphere->radius);
	transform = matrix_multiply(scale, translate);
	sphere->transform = transform;
}

t_ray	*ray_to_object_space(t_ray *ray, double **matrix)
{
	t_ray	*res;
	double	**inverse;

	res = (t_ray *)malloc(sizeof(t_ray));

	inverse = matrix_inverter(matrix);
	res->direction = mult_matrix_vector(inverse, ray->direction);
	res->origin = mult_matrix_vector(inverse, ray->origin);
	return (res);
}

t_intersec	*sphere_intersection(t_ray *base_ray, t_sphere *obj)
{
	t_intersec	*intersectionPoints = NULL;
	t_ray *ray = ray_to_object_space(base_ray, obj->transform);
	double		dot;
	double		vals[3];

	t_coo	*sphere_to_ray = vector_subtration(ray->origin, create_vector(0, 0, 0, 1));
	vals[0] = vector_abs(ray->direction, ray->direction);
	vals[1] = 2 * vector_abs(ray->direction, sphere_to_ray);
	dot = vector_abs(sphere_to_ray, sphere_to_ray) - 1;
	vals[2] = ((vals[1] * vals[1]) - (4 * vals[0] * dot));
	if (vals[2] >= 0)
	{
		intersectionPoints = (t_intersec *)malloc(sizeof(t_intersec));
		intersectionPoints->t1 = (((-1 * vals[1]) - sqrt(vals[2])) / (2 * vals[0]));
		intersectionPoints->t2 = (((-1 * vals[1]) + sqrt(vals[2])) / (2 * vals[0]));
	}
	return (intersectionPoints);
}

t_intersec	*plane_intersection(t_ray *base_ray, t_sphere *obj)
{
	t_intersec	*intersectionPoints = NULL;
	t_ray *ray = ray_to_object_space(base_ray, obj->transform);
	if (fabs(ray->direction->y) < EPSILON)
		return NULL;
	intersectionPoints = (t_intersec *)malloc(sizeof(t_intersec));
	intersectionPoints->t1 = (-1 *ray->origin->y) / ray->direction->y;
	intersectionPoints->t2 = intersectionPoints->t1;
	return intersectionPoints;
}

t_sphere	*init_sphere(void)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	sphere->center = create_vector(0, 0, 0, 0);
	sphere->diameter = 4;
	sphere->radius = sphere->diameter / 2;
	sphere->material = (t_material *)malloc(sizeof(t_material));
	sphere->material->color = create_vector(1, 0.2, 0.3, 0);
	sphere->material->ambient = 0.1;
	sphere->material->diffuse = 0.9;
	sphere->material->specular = 0.9;
	sphere->material->shininess = 100.0;
	return (sphere);
}

t_coo	*reflect(t_coo *v, t_coo *n)
{
	t_coo	*var;
	t_coo	*res;

	var = vector_multipli_scalar(2.0*vector_abs(v,n),n);
	res = vector_subtration(v, var);
	free(var);
	return(res);
}

t_coo	*normal_object_type(t_material *poly, t_coo *o_point)
{
	return (vector_subtration(o_point, create_vector(0, 0, 0, 1)));
}

t_coo	*normal_at(double **transform, t_coo *w_point, t_material *poly)
{
	t_coo	*o_point;
	t_coo	*o_normal;
	t_coo	*w_normal;
	double	**inv_trans;
	double	**transp_trans;

	inv_trans = matrix_inverter(transform);
	transp_trans = matrix_transpose(inv_trans);
	o_point = mult_matrix_vector(inv_trans, w_point);
	o_normal = normal_object_type(poly, o_point);
	w_normal = mult_matrix_vector(transp_trans, o_normal);
	w_normal->w = 0;
	return (vector_normalize(w_normal));
}

static void		get_obj_props(t_sphere *sphere, t_comps *comps)
{
	comps->normal_vec = normal_at(sphere->transform,
			comps->position, sphere->material);
}

t_coo	*ray_position(t_ray *ray, double t)
{
	return (vector_addition(ray->origin, vector_multipli_scalar(t, ray->direction)));
}

t_hit	*hiter_point(t_intersec *intersections, t_sphere *sphere)
{
	t_hit	*first = NULL;
	if (intersections == NULL)
		return (NULL);
	if (intersections->t1 >= 0)
	{
		first = (t_hit *)malloc(sizeof(t_hit));
		first->t = intersections->t1;
		first->obj = sphere;
	}
	if (intersections->t2 >= 0 && intersections->t2 > intersections->t1)
	{
		first = (t_hit *)malloc(sizeof(t_hit));
		first->t = intersections->t2;
		first->obj = sphere;
	}
	return (first);
}

void	prepare_computations(t_comps *comps, t_ray *rt, t_hit *hit)
{
	comps->light = hit->light;
	comps->t = hit->t;
	comps->obj = hit->obj;
	comps->position = ray_position(rt, comps->t);
	comps->eye_vec = vector_multipli_scalar(-1, rt->direction);
	get_obj_props(comps->obj, comps);
	if (vector_abs(comps->normal_vec, comps->eye_vec) < 0)
	{
		comps->inside = 1;
		comps->normal_vec = vector_multipli_scalar(-1, comps->normal_vec);
	}
	else
		comps->inside = 0;
	comps->reflect_vec = reflect(rt->direction, comps->normal_vec);
	comps->over_point = vector_addition(comps->position,
		vector_multipli_scalar(EPSILON, comps->normal_vec));
}

int	is_shadowed(t_comps *comps, t_light *light)
{
	t_coo	*path;
	double	distance;
	t_ray	*rc;
	t_hit	*hit;
	t_intersec	*intersec;
	int	result;

	path = vector_subtration(light->posi, comps->over_point);
	distance = vector_abs(path, path);
	rc = create_ray(comps->over_point, vector_normalize(path));
	intersec = sphere_intersection(rc, comps->obj);
	//intersec = plane_intersection(rc, comps->obj);
	hit = hiter_point(intersec, comps->obj);
	if (hit && hit->t < distance)
		result = 0;
	else
		result = 1;
	return (result);
}

static void	set_light_params(t_comps *args, t_ltparams *params, t_light *lt)
{
	params->effective_color = vector_multipli(args->obj->material->color,
	lt->intensity);
	params->light_v = vector_normalize(vector_subtration(lt->posi,
		args->over_point));
	params->ambient = vector_multipli_scalar(args->obj->material->ambient, params->effective_color);
	params->light_dot_normal = vector_abs(params->light_v, args->normal_vec);
}


t_coo	*lighting(t_comps args, t_light *current_light, int in_shadow)
{
	t_ltparams	params;

	set_light_params(&args, &params, current_light);
	if (params.light_dot_normal < 0 || in_shadow == 1)
	{
		params.diffuse = create_vector(0, 0, 0, 0);
		params.specular = create_vector(0, 0, 0, 0);
	}
	else
	{
		params.diffuse = vector_multipli_scalar((args.obj->material->diffuse * params.light_dot_normal),
			params.effective_color);
		params.reflect_v = reflect(vector_multipli_scalar(-1, params.light_v),
			args.normal_vec);
		params.reflect_dot_eye = vector_abs(params.reflect_v, args.eye_vec);
		if (params.reflect_dot_eye <= 0)
			params.specular = create_vector(0, 0, 0, 0);
		else
			params.specular = vector_multipli_scalar(args.obj->material->specular *
			(pow(params.reflect_dot_eye, args.obj->material->shininess)), current_light->intensity);
	}
	return (vector_addition(
	vector_addition(params.diffuse, params.specular), params.ambient));
}

t_coo	*position(t_ray *ray, double t)
{
	t_coo	*aux = vector_multipli_scalar(t, ray->direction);
	t_coo	*position = vector_addition(ray->origin, aux);
	return (position);
}

t_coo	*slighting(t_coo *position, t_light *light, t_coo *eye, t_material *material, t_coo *normal, int shadow)
{
	t_coo	*temp = material->color;
	t_coo	*effectivecolor = vector_multipli(temp, light->intensity);
	t_coo	*lightvec = vector_normalize(vector_subtration(light->posi, position));
	t_coo	*ambienteColor = vector_multipli_scalar(material->ambient, temp);
	t_coo	*difusecolor;
	t_coo	*specularcolor;

	double	lDOtn = vector_abs(lightvec, normal);
	if (lDOtn <= 0.0 || shadow)
	{
		difusecolor = create_vector(0.0, 0.0, 0.0, 0.0);
		specularcolor = create_vector(0.0, 0.0, 0.0, 0.0);
	}
	else
	{
		difusecolor = vector_multipli_scalar(lDOtn, vector_multipli_scalar(material->diffuse, effectivecolor));
		t_coo	*refle = reflect(vector_multipli_scalar(-1.0, lightvec), normal);
		double	rDote = vector_abs(refle, eye);
		if (rDote <= 0.0)
			specularcolor = create_vector(0.0, 0.0, 0.0, 0.0);
		else
		{
			//Shinniness ou Brilho e depois do rDote
			double	factor = pow(rDote, 200.0);
			specularcolor = vector_multipli_scalar(material->specular * factor, light->intensity);
		}
	}
	return vector_addition(vector_addition(ambienteColor, difusecolor), specularcolor);
}

int	render(t_data *img)
{
	t_cam	*cam;
	t_ray	*ray;
	t_intersec	*intersec;
	t_sphere	*spher;
	t_light		*light;
	int color;
	t_comps	comp;

	int	y = 0;
	cam = init_cam();
	spher = init_sphere();
	render_sphere_transform(spher);
	light = (t_light *)malloc(sizeof(t_light));
	light->posi = create_vector(0, 8, -3, 0);
	light->intensity = create_vector(1, 1 ,1 , 1);
	t_coo	*rgb;

	while (y < NY)
	{
		int	x = 0;
		while (x < NX)
		{
			ray = ray_for_pixel(cam, x, y);
			//printf("ray_origin : (%f, %f, %f)\t ray_direction : (%f, %f, %f)\n", ray->origin->x,ray->origin->y, ray->origin->z, ray->direction->x, ray->direction->y, ray->direction->z);
			intersec = sphere_intersection(ray, spher);
			//intersec = plane_intersection(ray, spher);
			t_hit	*hit = hiter_point(intersec, spher);
			if (hit)
			{
				t_coo	*hitposition = position(ray, hit->t);
				prepare_computations(&comp, ray, hit);
				//rgb = slighting(hitposition, light, ray->direction, spher->material, vector_normalize(hitposition), is_shadowed(&comp, light));
				rgb = lighting(comp, light, is_shadowed(&comp,light));
			}
			else
				rgb = create_vector(0, 0, 0, 0);
			color = ((int)(255.99 * rgb->x)<<16) + ((int)(255.99 * rgb->y)<<8) + ((int)(255.99 * rgb->z));
			my_mlx_pixel_put(img, x, y, color);
	//printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
	// printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
	// printf("%f %f %f %f\n", comp.eye_vec->x, comp.eye_vec->y, comp.eye_vec->z, comp.eye_vec->w);
			x++;
		}
		y++;
	}

// int	i = 0;
// 	while (i < 4)
// 	{
// 		int	y = 0;
// 		while (y < 4)
// 		{
// 			printf("%f ", cam->transform[i][y]);
// 			y++;
// 		}
// 		printf("\n");
// 		i++;
// printf("%f %f %f %f\n", ray->direction->x, ray->direction->y, ray->direction->z, ray->direction->w);
// 	}
}

int	main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, NX, NY, "Ray_Sphere");
	img.img = mlx_new_image(mlx, NX, NY);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	render(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}