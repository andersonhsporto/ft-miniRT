#ifndef	MINIRT
# define MINIRT
# include "struct.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <assert.h>
# include <limits.h>

#define NX 200
#define NY 100
#define NS 100

t_coo	*vector_addition(t_coo *a, t_coo *b);

t_coo	*vector_subtration(t_coo *a, t_coo *b);

t_coo	*vector_multipli_scalar(double scalar, t_coo *a);

double	vector_lenght(t_coo *a);

t_coo	*vector_normalize(t_coo *a);

double	vector_abs(t_coo *a, t_coo *b);

t_coo	*vector_cross(t_coo *a, t_coo *b);

t_coo	*vector_multipli(t_coo *a, t_coo *b);

t_coo	*creat_vector(double x, double y, double z);

t_coo	*background_3d_color(t_ray *ray);

t_coo	*point_at_parameter(double t, t_ray *ray);

int		hit_sphere(t_ray *ray, t_scene *sphere, double t_max, double t_min);

t_coo	*reflect(t_coo *v, t_coo *n);

void	make_image(t_data *img, t_view *view);

t_coo	*pixel_gerator(double y, double x, t_view *data);

t_coo	*colory(t_ray *ray, t_scene **hiter, int deat);

t_ray	*gerate_ray(t_cam	*cam, double u, double v);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

t_scene	*hiter_point(t_ray *ray, t_scene **hiter, t_scene *rec);

t_ray	*scatter(t_ray *ray, t_scene *rec, t_ray *scattered);
int	cylinder_intersection(t_ray *ray, t_scene *sphere, double t_max, double t_min);
#endif
