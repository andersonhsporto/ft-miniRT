/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:09:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/19 19:48:48 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "vector.h"
# include "tracer.h"

enum e_type
{
	sphere,
	plane,
	square,
	cylinder,
	triangle,
	light,
	camera,
	ambient,
	none
};

typedef	struct s_record {
	double		t;
	double		max;
	double		min;
	t_vector	p;
	t_vector	normal;
	t_vector	albedo;
}				t_record;

typedef struct s_datacam {
	double		viewport_height;
	double		viewport_width;
	double		ratio;
	t_vector	view_up;
	t_vector	w;
	t_vector	u;
	t_vector	v;
	t_vector	hori_dir;
	t_vector	vert_dir;
	t_vector	lower_left_corner;
}	t_datacam;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_cylinder {
	t_vector	coordinates;
	t_vector	normalized;
	double		radius;
	double		height;
	t_vector	color;
}	t_cylinder;

typedef struct s_plane {
	t_vector	coordinates;
	t_vector	normalized;
	t_vector	color;
}	t_plane;

typedef struct s_sphere {
	t_vector	center;
	double		diameter;
	t_vector	color;
}				t_sphere;

typedef struct s_element {
	int					type;
	void				*ptr;
	t_vector			color;
	struct s_element	*next;
}	t_element;

typedef struct s_light {
	t_vector	point;
	double		bright;
}	t_light;

typedef struct s_cam {
	t_vector	view_point;
	t_vector	normalized_vector;
	int			fov;
}	t_cam;

typedef struct s_ambient {
	double		ratio;
	t_vector	rgb;
}	t_ambient;

typedef struct s_index {
	int		ambient;
	int		camera;
}	t_index;

typedef struct s_mini {
	int				argc;
	char			**argv;
	t_index			index;
	t_ambient		*light_a;
	t_cam			*cam;
	t_light			*light;
	t_element		*element;
	t_datacam		*data_cam;
	t_record		hit_record;
	t_ray			ray;
	t_mlx			mlx;
	t_image			img;
	t_scene			*scene;
}	t_mini;

#endif
