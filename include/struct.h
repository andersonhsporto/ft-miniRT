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

typedef struct	s_sences {
	t_coo	*center;
	double	raio;
	t_coo	*p;
	double	t;
	t_coo	*normal;
	t_coo	*material;
}				t_sence;

#endif