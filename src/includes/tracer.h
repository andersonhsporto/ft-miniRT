# ifndef TRACER_H
#define TRACER_H

#include "struct.h"

typedef struct s_material
{
	double	*color;
	double	ambient;
	double	diffuse;
	double	specular;
}	t_material_d;

typedef struct s_light_d
{
	double	*intensity;
	double	*posi;
}	t_light_d;

typedef struct s_intersec
{
	int		cont;
	double	t1;
	double	t2;
}	t_intersec;

typedef struct s_hit_d
{
	double			t;
}	t_hit;

typedef struct s_object_d
{
	double		radius;
	double		**matrix;
	char		type;
	double		*position;
	t_material_d	*material;
}	t_obj_d;

typedef struct s_scene
{
	t_light_d			**light;
	t_obj_d			**object;
	int				cont;
}	t_scene;

typedef struct s_ray {
	double	*origin;
	double	*direction;
}	t_ray;

t_scene	*init_scene(void);

double	**matrix_multiply(double **a, double **b, int line);
double	**matrix_transpose(double **a);
double	matrix_x_multiply(double a[2][2]);
double	matrix_cofactor(double a[3][3]);
double	matrix_determinant(double **a);
double	*vector_addition(double *a, double *b);
double	*vector_multipli(double *a, double *b);
double	*vector_subtraction(double *a, double *b);
double	*vector_multipli_scalar(double scalar, double *a);
double	vector_length_double(double *a);

double	**rotation_y(double r);
double	vector_abs(double *a, double *b);
double	*vector_cross_double(double *a, double *b);
double	*vector_normalize_double(double *a);
double	*create_vector(double x, double y, double z);

double	**create_matrix(int col, int line);
double	**matrix_inverter(double **a, double abs);
double	*reflect(double *v, double *n);


double		**matrix_identify(double x, double y, double z, double w);
t_ray		*ray_to_object_space(t_ray *ray, double **local);
double		*make_point(double x, double y, double z);
t_intersec	*plane_intersection(t_ray *ray);
t_intersec	*sphere_intersection(t_ray *rayy, t_obj_d *obj);
t_intersec	*cylinder_intersection(t_ray *ray, t_obj_d *obj);
t_hit		*hit_point(t_intersec *intersections);
double		*position(t_ray *ray, double t);
double		*slighting(double *position, t_light_d *light, double *eye, t_material_d *material, double *normal);
t_hit		*hit_scene_object(t_ray *ray, t_scene *scene);

t_scene		*init_scene(void);
#endif
