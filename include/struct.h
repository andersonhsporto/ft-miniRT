#ifndef STRUCT_H
#define STRUCT_H

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
	t_coo	*center;
	double	diameter;
	double	radius;
	double	**transform;
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

typedef struct intersect_list
{
	double	t;
	int		obj_type;
	int		obj_pos;
	struct intersect_list	*next;
}	t_intersec;

typedef struct s_caster
{
	int	cont;
	t_intersec	*intersec;
}	t_caster;

typedef struct			s_ltparams
{
	double		light_dot_normal;
	double		reflect_dot_eye;
	t_coo	*effective_color;
	t_coo	*light_v;
	t_coo	*ambient;
	t_coo	*diffuse;
	t_coo	*specular;
	t_coo	*reflect_v;
}						t_ltparams;

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

#endif