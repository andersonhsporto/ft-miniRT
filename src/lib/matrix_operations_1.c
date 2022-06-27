#include "../../include/minirt.h"

t_coo	*vector_addition(t_coo *a, t_coo *b)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	res->w = a->w + b->w;
	return (res);
}

t_coo	*vector_multipli(t_coo *a, t_coo *b)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x * b->x;
	res->y = a->y * b->y;
	res->z = a->z * b->z;
	res->w = a->w * b->w;
	return (res);
}

t_coo	*vector_subtration(t_coo *a, t_coo *b)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	res->w = a->w - b->w;
	return (res);
}

t_coo	*vector_multipli_scalar(double scalar, t_coo *a)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x * scalar;
	res->y = a->y * scalar;
	res->z = a->z * scalar;
	res->w = a->w * scalar;
	return (res);
}

double	vector_lenght(t_coo *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z + a->w * a->w));
}

double	**matrix_inverter(double **a, double abs)
{
	double	**res;
	int		jboo;
	int		iboo;
	int		signal = 1.0;
	double	matrix[3][3];

	res = create_matrix(4, 4);
	if (abs == 1.0)
		return (a);
	for (size_t t = 0; t < 4; t++)
	{
		if (t % 2 == 1)
			signal = -1.0;
		for (size_t u = 0; u < 4; u++)
		{
			if ((t % 2 == 0 && u % 2 == 1) || (t % 2 == 1 && u % 2 == 0))
				signal = -1.0;
			iboo = 0;
			for (size_t i = 0; i < 3; i++)
			{
				if (i == t)
					iboo = 1;
				jboo = 0;
				for (size_t j = 0; j < 3; j++)
				{
					if (j == u)
						jboo = 1;
					matrix[i][j] = a[i + iboo][j + jboo];
				}
			}
			res[t][u] = (signal * matrix_cofactor(matrix)) / abs;
			signal = 1.0;
		}
	}
	return (res);
}
