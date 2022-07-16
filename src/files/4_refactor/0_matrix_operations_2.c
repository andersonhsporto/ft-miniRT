#include "minirt.h"

double	vector_abs(t_coo *a, t_coo *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

double	**vector_to_matrix(t_coo *a)
{
	double	**res;

	res = (double **)malloc(sizeof(double *));
	res[0] = (double *)malloc(sizeof(double) * 4);
	res[0][0] = a->x;
	res[0][1] = a->y;
	res[0][2] = a->z;
	res[0][3] = a->w;
	return (res);
}

t_coo	*vector_cross(t_coo *a, t_coo *b)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = (a->y * b->z) - (a->z * b->y);
	res->y = (a->z * b->x) - (a->x * b->z);
	res->z = (a->x * b->y) - (a->y * b->x);
	res->w = 0;
	return (res);
}

t_coo	*vector_normalize(t_coo *a)
{
	t_coo	*res;
	double	lenght;

	lenght = vector_lenght(a);
	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x / lenght;
	res->y = a->y / lenght;
	res->z = a->z / lenght;
	return (res);
}

t_coo	*create_vector(double x, double y, double z, double w)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = x;
	res->y = y;
	res->z = z;
	res->w = w;
	return (res);
}

double	**matrix_multiply(double **a, double **b)
{
	double	**res;
	double	*var;

	res = (double **)malloc(sizeof(double *) * 4);
	for (int i = 0; i < 4; i++)
	{
		var = (double *)malloc(sizeof(double) * 4);
		for (size_t u = 0; u < 4; u++)
		{
			var[u] = 0;
			for (size_t j = 0; j < 4; j++)
			{
				var[u] += a[i][j] * b[j][u];
			}
		}
		res[i] = var;
	}
	return (res);
}

t_coo	*mult_matrix_vector(double **m1, t_coo *t1)
{
	t_coo	*new_t;
	double		*new;
	size_t		i;
	size_t		j;
	double		current[4];

	i = 0;
	new = (double *)ft_calloc(4, sizeof(double));
	current[0] = t1->x;
	current[1] = t1->y;
	current[2] = t1->z;
	current[3] = t1->w;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new[i] += (m1[i][j] * current[j]);
			j++;
		}
		i++;
	}
	new_t = create_vector(new[0], new[1], new[2], new[3]);
	free(new);
	return (new_t);
}

double	**matrix_transpose(double **a)
{
	double	b[4][4];

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			b[i][j] = a[i][j];
		}
	}
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			a[i][j] = b[j][i];
		}
	}
	return (a);
}


double	matrix_determinant(double **a)
{
	double	res;
	double	*sub;
	int		index[2];

	index[0] = 0;
	index[1] = 0;
	sub = (double *)malloc(sizeof(double) * 4);
	while (index[1] < 4)
	{
		sub[index[1]] = cofator_4x4(a, index);
		index[1]++;
	}
	res = a[0][0] * sub[0] + a[0][1] * sub[1]
		+ a[0][2] * sub[2] + a[0][3] * sub[3];
	return (res);
}

double	**create_matrix(int col, int line)
{
	double	**res;
	int		i;

	i = 0;
	res = (double **)malloc(sizeof(double *) * line);
	while (i < line)
	{
		res[i] = (double *)malloc(sizeof(double) * col);
		i++;
	}
	return (res);
}

double	matrix_x_multiply(double a[2][2])
{
	return (a[0][0] * a[1][1] - (a[0][1] * a[1][0]));
}