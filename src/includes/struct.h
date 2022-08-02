/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:09:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/02 00:27:04 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

enum e_bool
{
	false,
	true
};

typedef struct s_cy_intersec {
	t_ray			ray;
	double			a;
	double			b;
	double			c;
	double			disc;
	double			vals[3];
}	t_cy_intersec;

typedef struct s_sp_intersec {
	t_ray	ray;
	t_coo	temp;
	t_coo	sphere_to_ray;
	double	dot;
	double	vals[3];
}	t_sp_intersec;

typedef struct s_utils {
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;
}	t_utils;

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

typedef struct s_cylinder_d
{
	int			id;
	t_coo 		coordinates;
	t_coo 		normalized;
	double		radius;
	double 		height;
	t_coo 		color;
	double 		**transform;
	int			transform_id;
} t_cylinder_d;

typedef struct s_plane_d
{
	int			id;
	t_coo		coordinates;
	t_coo		normalized;
	t_coo		color;
	double		**transform;
	int			transform_id;
}	t_plane_d;

typedef struct s_sphere_d
{
	int			id;
	int			transform_id;
	t_coo		center;
	t_coo		color;
	double		radius;
	double		**transform;
}	t_sphere_d;

typedef struct s_element {
	int					type;
	int					id;
	void				*ptr;
	struct s_element	*next;
}	t_element;

typedef struct s_light_d {
	t_coo		point;
	double		bright;
	t_coo		intensity;
	double		diffuse;
	double		ambient;
	double		specular;
	double		shininess;
	double		reflect;
}	t_light_d;

typedef struct s_cam_d {
	t_coo		view_point;
	t_coo		orientation;
	double		fov;

	double		**transform;
	t_coo		origin;
	double		pixel_size;
	double		half_height;
	double		half_width;
}	t_cam_d;

typedef struct s_ambient {
	double		ratio;
	t_coo		rgb;
}	t_ambient;

typedef struct s_index
{
	int ambient;
	int camera;
	int light;
	int sphere;
	int plane;
	int cylinder;
} t_index;

typedef struct s_error
{
	int line_error;
	int multiple_ambient;
	int ambient_color;
	int rgb;
	int ambient_ratio;
	int multiple_camera;
	int camera_view_point;
	int camera_orientation;
	int camera_fov;
	int light_point;
	int light_bright;
	int sp_coord;
	int pl_coord;
	int pl_normalized;
	int cy_coord;
	int cy_normalized;
	int minimum_args;
}	t_error;

typedef struct s_mini
{
	int 		argc;
	char		**argv;
	t_index		index;
	t_ambient	*light_a;
	t_cam_d		*cam;
	t_light_d	*light;
	t_element	*element;
	t_mlx		*mlx;
	t_image		img;
	t_ray		ray;
	t_intersec	*hit;
	t_error 	error;
} t_mini;

#endif
