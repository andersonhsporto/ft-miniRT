#ifndef	MINIRT
# define MINIRT
# include "struct.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <assert.h>
# include <limits.h>

#define NX 640
#define NY 480
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

static double	**calculate_orientation(t_coo *left, t_coo *true_up, t_coo *forward, t_coo *from);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

double	cofator_4x4(double **a, int index[2]);

double	**sub_matrix(double	**a, int index[2], int col, int row);

double	**scalar_4x4_matrix(double **mat, double abs);
#endif
