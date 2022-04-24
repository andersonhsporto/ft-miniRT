#ifndef	MINIRT
# define MINIRT
# include "struct.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <assert.h>
# include <limits.h>

# define INDENTIFY {{1.0,0.0,0.0,0.0}, {0.0,1.0,0.0,0.0}, {0.0,0.0,1.0,0.0}, {0.0,0.0,0.0,1.0}}
t_coo	*vector_addition(t_coo *a, t_coo *b);

t_coo	*vector_subtration(t_coo *a, t_coo *b);

t_coo	*vector_multipli_scalar(double scalar, t_coo *a);

double	vector_lenght(t_coo *a);

t_coo	*vector_normalize(t_coo *a);

double	vector_abs(t_coo *a, t_coo *b);

t_coo	*vector_cross(t_coo *a, t_coo *b);

double	**matrix_multpli(double a[4][4], double b[4][4]);

void	matrix_free(double **a);

void	matrix_transpose(double a[4][4]);

double	matrix_determinant(double a[4][4]);

double	matrix_cofactor(double a[3][3]);

double	matrix_x_multpli(double a[2][2]);

double	**matrix_inverter(double a[4][4], double abs);

double	**create_matrix(int col, int line);

t_coo	*vector_multipli(t_coo *a, t_coo *b);
#endif