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

typedef struct s_hit
{
	t_scene	*obj;
	double	t;
}	t_hit;

typedef struct s_intersec
{
	double	t1;
	double	t2;
}	t_intersec;

typedef struct intersect_list
{
	double	t;
	t_scene	*obj;
	struct intersect_list	*next;
}	t_intersect_list;

typedef struct s_light
{
	t_coo	*intensity;
	t_coo	*posi;
}	t_light;

typedef struct		s_comps
{
	double		t;
	t_coo	*position;
	t_light	*light;
	t_coo	*eye_vec;
	t_scene	*obj;
	t_coo	*normal_vec;
	t_coo	*reflect_vec;
	t_coo	*over_point;
	int		inside;
}		t_comps;

#endif