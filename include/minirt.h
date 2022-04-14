#ifndef	MINIRT
# define MINIRT
# include "struct.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <assert.h>

t_coo	*matrix_addition(t_coo *a, t_coo *b);

t_coo	*matrix_subtration(t_coo *a, t_coo *b);

t_coo	*matrix_multipli_scalar(double scalar, t_coo *a);
#endif