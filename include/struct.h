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
}				t_coo;

typedef struct	s_ray {
	t_coo	*origin;
	t_coo	*direction;
}				t_ray;

typedef struct	s_scenes {
	t_coo	*center;
	double	radius;
	double	t;
	t_coo	*p;
	t_coo	*normal;
	t_coo	*material;
	char	type;
}				t_scene;

typedef struct	s_cam {
	t_coo	*lower_left_corner;
	t_coo	*horizontal;
	t_coo	*origin;
	t_coo	*vertical;
}				t_cam;

typedef struct	s_view {
	t_scene	**scenes;
	t_cam	*cam;
}				t_view;
#endif