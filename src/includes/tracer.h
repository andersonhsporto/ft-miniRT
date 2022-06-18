#ifndef TRACER_H
#define TRACER_H

typedef struct s_material_re
{
	double	*color;
	double	ambient;
	double	diffuse;
	double	specular;
}	t_material_re;

typedef struct s_light_re
{
	double	*intensity;
	double	*posi;
}	t_light_re;

typedef struct s_intersec_re
{
	int		cont;
	double	t1;
	double	t2;
}	t_intersec_re;

typedef struct s_ray_re
{
	double	*origin;
	double	*direction;
}	t_ray_re;

typedef struct s_hit_re
{
	double			t;
}	t_hit_re;

typedef struct s_obj_re
{
	double			radius;
	double			**matrix;
	char			type;
	double			*position;
	t_material_re	*material;
}	t_obj_re;

typedef struct s_scene_re
{
	t_light_re			**light;
	t_obj_re			**object;
	int				cont;
}	t_scene_re;

typedef struct	s_img_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img_data;

t_scene_re	*init_seine(void);
double		**create_matrix(int col, int line);
double		**matrix_inverter(double **a, double abs);
double		**matrix_multpli(double **a, double **b, int line);
double		**matrix_transpose(double **a);
double		matrix_x_multpli(double a[2][2]);
double		matrix_cofactor(double a[3][3]);
double		matrix_determinant(double **a);
double	**matrix_multiply(double **a, double **b, int line);

double		**rotation_y(double r);
double		vector_abs(double *a, double *b);
double		*vector_cross(double *a, double *b);
double		*vector_normalize(double *a);
double		*create_vector(double x, double y, double z);
double		*vector_addition(double *a, double *b);
double		*vector_multipli(double *a, double *b);
double		*vector_subtraction(double *a, double *b);
double		*vector_multipli_scalar(double scalar, double *a);
double		vector_lenght(double *a);
double		*make_point(double x, double y, double z);
double		*reflect(double *v, double *n);

double		*position(t_ray_re *ray, double t);
t_hit_re	*hiter_seine_object(t_ray_re *ray, t_scene_re *scene);
t_ray_re	*ray_to_object_space(t_ray_re *ray, double **local);

double	*slighting(double *position, t_light_re *light, double *eye, t_material_re *material, double *normal);

#endif
