#ifndef REFACTOR_H
# define REFACTOR_H

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_coordinate {
	double	x;
	double	y;
	double	z;
	double	w;
}				t_coo;

typedef struct s_light
{
	t_coo	*intensity;
	t_coo	*posi;
}	t_light;

typedef struct	s_ray {
	t_coo	*origin;
	t_coo	*direction;
}				t_ray;

typedef struct	s_scenes {
	t_coo	*center;
	double	radius;
	t_coo	*p;
	t_coo	*normal;
	t_coo	*material;
	char	type;
}				t_scene;

typedef struct	s_material
{
	t_coo	*color;
	double	diffuse;
	double	ambient;
	double	specular;
	double	shininess;
	double	reflect;
}	t_material;

typedef struct	s_sphere
{
	t_coo		*center;
	double		diameter;
	double		radius;
	double		**transform;
	t_material	*material;
}	t_sphere;

typedef struct	s_cylinder
{
	t_coo		*pos;
	t_coo		*norm;
	double		diameter;
	double		radius;
	double		height;
	t_material	*material;
	double		**transform;
}		t_cylinder;

typedef struct	s_plane
{
	t_coo	*pos;
	t_coo	*norm;
	double	**transform;
	t_material	*material;
}	t_plane;

typedef struct s_objects
{
	t_sphere	**sphere;
	t_plane		**plane;
	t_cylinder	**cylinder;
}	t_poly;

typedef struct	s_cam {
	t_coo	*view;
	t_coo	*pos;
	double	fov;
	double	**transform;
	t_coo	*origin;
	double	pixel_size;
	double	half_height;
	double	half_width;
}				t_cam;

typedef struct	s_view {
	t_scene	**scenes;
	t_cam	*cam;
}				t_view;

typedef struct s_intersect_list
{
	double					t;
	int						obj_type;
	int						obj_pos;
	struct s_intersect_list	*next;
}	t_intersec;

typedef struct s_caster
{
	int			cont;
	t_intersec	*intersec;
}	t_caster;

typedef struct	s_ltparams
{
	double		light_dot_normal;
	double		reflect_dot_eye;
	t_coo		*effective_color;
	t_coo		*light_v;
	t_coo		*ambient;
	t_coo		*diffuse;
	t_coo		*specular;
	t_coo		*reflect_v;
}				t_ltparams;

typedef struct		s_comps
{
	double		t;
	t_coo	*position;
	t_light	*light;
	t_coo	*eye_vec;
	t_poly	*poly;
	t_material	*material;
	t_coo	*normal_vec;
	t_coo	*reflect_vec;
	t_coo	*over_point;
	int		inside;
}		t_comps;

typedef struct s_sence
{
	t_sphere	**obj;
	t_plane		**plane;
}	t_sence;


#define NX 600
#define NY 600
#define SPHERE 1
#define PLANE 2
#define CYLINDER 3
# define EPSILON 0.00001

t_coo	*vector_addition(t_coo *a, t_coo *b);

t_coo	*vector_subtration(t_coo *a, t_coo *b);

t_coo	*vector_multipli_scalar(double scalar, t_coo *a);

double	vector_lenght(t_coo *a);

t_coo	*vector_normalize(t_coo *a);

double	vector_abs(t_coo *a, t_coo *b);

t_coo	*vector_cross(t_coo *a, t_coo *b);

t_coo	*vector_multipli(t_coo *a, t_coo *b);

t_coo	*create_vector(double x, double y, double z, double w);

double	matrix_determinant(double **a);

double	**matrix_transpose(double **a);

double	**matrix_multiply(double **a, double **b);

double	**matrix_inverter(double **a);

double	**identity(double x, double y, double z);

double	**translation(double x, double y, double z);

double	**vector_to_matrix(t_coo *a);

double	**create_matrix(int col, int line);

double	matrix_x_multiply(double a[2][2]);

t_coo	*mult_matrix_vector(double **m1, t_coo *t1);

double	**calculate_orientation(t_coo *left, t_coo *true_up, t_coo *forward, t_coo *from);

double	cofator_4x4(double **a, int index[2]);

double	**sub_matrix(double	**a, int index[2], int col, int row);

double	**scalar_4x4_matrix(double **mat, double abs);

t_intersec	*plane_intersection(t_ray *base_ray, t_plane *obj, int obj_pos);

t_sphere	*init_sphere_re(void);

void	render_sphere_transform(t_sphere *sphere);

t_intersec	*sphere_intersection(t_ray *base_ray, t_sphere *obj, int obj_pos);

t_ray	*create_ray(t_coo *origin, t_coo *direction);

double	**view_transform(t_coo *from, t_coo *to, t_coo *up);

void	camera_pixel_size(int width, int height, t_cam *cam);

t_cam	*init_cam(void);

t_coo	*reflect(t_coo *v, t_coo *n);

t_coo	*normal_object_type(t_material *poly, t_coo *o_point, double *obj_type_height);

t_coo	*normal_at(double **transform, t_coo *w_point, t_material *poly, double *obj_type_height);

t_coo	*ray_position(t_ray *ray, double t);

t_caster	*put_intersection_in_cast(t_caster *cast, t_intersec *intersec);

t_caster	*init_intersec_list(void);

void	all_sphere_intersec(t_caster *cast, t_ray *ray, t_poly *poly, t_sphere *list);

t_intersec	*hiter_point(t_caster	*head);

t_ray	*ray_to_object_space(t_ray *ray, double **matrix);

t_plane	*init_plane_re(void);

double	**normal_rotation_matrix(t_coo *normal);

void	render_plane_transform(t_plane *plane);

t_cylinder	*init_cylinder_re(void);

void	render_cylinder_transform(t_cylinder *cylinder);

t_intersec	*cylinder_intersec(t_ray *base_ray, t_cylinder *cylinder, int pos);

t_coo	*slighting(t_coo *position, t_light *light, t_coo *eye, t_material *material, t_coo *normal, int is_shadow);

#endif
