/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:09:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/23 01:56:04 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "vector.h"
# include "refactor.h" //TODO: remove this

enum e_type
{
	sphere,
	plane,
	cylinder,
	light,
	camera,
	ambient,
	none
};

typedef struct s_utils {
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;
}	t_utils;

typedef	struct s_record {
	double		t;
	double		max;
	double		min;
	t_vector	p;
	t_vector	normal;
	t_vector	albedo;
}				t_record;

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

typedef struct s_cylinder_d {
	int			id;
	t_coo		*coordinates;
	t_coo		*normalized;
	double		radius;
	double		height;
	t_coo		*color;
	double		**transform;
}	t_cylinder_d;

typedef struct s_plane_d {
	int			id;
	t_coo		*coordinates;
	t_coo		*normalized;
	t_coo		*color;
	double		**transform;
}	t_plane_d;

typedef struct s_sphere_d {
	int			id;
	t_coo		*center;
	t_coo		*color;
	double		radius;
	double		**transform;
}				t_sphere_d;

typedef struct s_element {
	int					type;
	int					id;
	void				*ptr;
	t_vector			color;
	struct s_element	*next;
}	t_element;

typedef struct s_light_d {
	t_coo		*point;
	double		bright;
	t_coo		*intensity;
	double		diffuse;
	double		ambient;
	double		specular;
	double		shininess;
	double		reflect;
}	t_light_d;

typedef struct s_cam_d {
	t_coo		*view_point;
	t_coo		*orientation;
	double		fov;

	double		**transform;
	t_coo		*origin;
	double		pixel_size;
	double		half_height;
	double		half_width;
}	t_cam_d;

typedef struct s_ambient {
	double		ratio;
	t_coo		*rgb;
}	t_ambient;

typedef struct s_index {
	int		ambient;
	int		camera;
	int		sphere;
	int		plane;
	int		cylinder;
}	t_index;

typedef struct s_mini {
	int				argc;
	char			**argv;
	t_index			index;
	t_ambient		*light_a;
	t_cam_d			*cam;
	t_light_d		*light;
	t_element		*element;
	t_mlx			*mlx;
	t_image			img;
	t_record		hit_record;
	t_ray			*ray;
}	t_mini;

#endif
