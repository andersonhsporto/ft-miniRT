#include "../include/minirt.h"

double	vector_abs(t_coo *a, t_coo *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

t_coo	*vector_cross(t_coo *a, t_coo *b)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	return (res);
}

double	**matrix_multpli(double a[4][4], double b[4][4])
{
	double	**res;
	double	*var;

	res = (double **)malloc(sizeof(double *) * 4);
	for (size_t i = 0; i < 4; i++)
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

void	matrix_transpose(double a[4][4])
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
}

double	matrix_x_multpli(double a[2][2])
{
	return (a[0][0] * a[1][1] - (a[0][1] * a[1][0]));
}

double	matrix_cofactor(double a[3][3])
{
	double	res;
	int		jboo;
	double	signal;
	double	matrix[2][2];
	int		size = 2;

	res = 0.0;
	for (size_t u = 0; u < 3; u++)
	{
		signal = 1.0;
		if (u % 2 == 1)
			signal = -1.0;
		for (size_t i = 0; i < 2; i++)
		{
			jboo = 0;
			for (size_t j = 0; j < size; j++)
			{
				if (j == u)
					jboo = 1;
				matrix[i][j] = a[i + 1][j + jboo];
			}
		}
		res += (signal * a[0][u]) * matrix_x_multpli(matrix);
	}
	return (res);
}

double	matrix_determinant(double a[4][4])
{
	double	res;
	int		jboo;
	int		size = 3;
	int		signal;
	double	matrix[3][3];

	res = 0.0;
	for (size_t u = 0; u < 4; u++)
	{
		signal = 1.0;
		if (u % 2 == 1)
			signal = -1.0;
		for (size_t i = 0; i < 3; i++)
		{
			jboo = 0;
			for (size_t j = 0; j < size; j++)
			{
				if (j == u)
					jboo = 1;
				matrix[i][j] = a[i + 1][j + jboo];
			}
		}
		res += (signal * a[0][u]) * matrix_cofactor(matrix);
	}
	return (res);
}

void	matrix_free(double **a)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(a[i]);
		i++;
	}
	free(a);
}
