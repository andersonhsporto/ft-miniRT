#include "minirt.h"

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

double	**sub_matrix(double	**a, int index[2], int col, int row)
{
	int		i;
	int		j;
	int		idx[2];
	double	**res;

	i = 0;
	idx[0] = 0;
	res = create_matrix(row, col);
	while (idx[0] < row)
	{
		if (i == index[0])
			i++;
		j = 0;
		idx[1] = 0;
		while (idx[1] < col)
		{
			if (j == index[1])
				j++;
			res[idx[0]][idx[1]] = a[i][j];
			j++;
			idx[1]++;
		}
		idx[0]++;
		i++;
	}
	return (res);
}

double		det_3x3(double **mat)
{
	double	result;

	result = (mat[0][0] * mat[1][1] * mat[2][2] +
			mat[0][1] * mat[1][2] * mat[2][0] +
			mat[0][2] * mat[1][0] * mat[2][1])
			-
			(mat[2][0] * mat[1][1] * mat[0][2] +
			mat[2][1] * mat[1][2] * mat[0][0] +
			mat[2][2] * mat[1][0] * mat[0][1]);
	return (result);
}

double	cofator_4x4(double **a, int index[2])
{
	double	**sub;
	double	cofator;

	sub = sub_matrix(a, index, 3, 3);
	if ((index[0] + index[1]) % 2 == 0)
	{
		cofator = det_3x3(sub);
	}
	else
	{
		cofator = -1 * det_3x3(sub);
	}
	free_matrix(sub, 3);
	return (cofator);
}

double	**scalar_4x4_matrix(double **mat, double abs)
{
	double	**new;
	size_t	i;
	size_t	j;

	i = 0;
	new = create_matrix(4, 4);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new[i][j] = mat[i][j] * abs;
			j++;
		}
		i++;
	}
	return (new);
}

double	**matrix_inverter(double **a)
{
	double	**res;
	double	**tmp;
	double	**transp;
	double	abs;
	int		index[2];

	tmp = create_matrix(4, 4);
	abs = matrix_determinant(a);
	if (abs == 0)
		return (NULL);
	index[0] = 0;
	while (index[0] < 4)
	{
		index[1] = 0;
		while (index[1] < 4)
		{
			tmp[index[0]][index[1]] = cofator_4x4(a, index);
			index[1]++;
		}
		index[0]++;
	}
	transp = matrix_transpose(tmp);
	res = scalar_4x4_matrix(transp, 1 / abs);
	free_matrix(tmp, 4);
	return (res);
}

double	**identity(double x, double y, double z)
{
	double	**res;
	int		i;

	i = 0;
	res = (double **)malloc(sizeof(double *) * 4);
	while (i < 4)
	{
		res[i] = (double *)malloc(sizeof(double) * 4);
		i++;
	}
	res[0][0] = (double)x;res[0][1] = 0.0;res[0][2] = 0.0;res[0][3] = 0.0;
	res[1][0] = 0.0;res[1][1] = (double)y;res[1][2] = 0.0;res[1][3] = 0.0;
	res[2][0] = 0.0;res[2][1] = 0.0;res[2][2] = (double)z;res[2][3] = 0.0;
	res[3][0] = 0.0;res[3][1] = 0.0;res[3][2] = 0.0;res[3][3] = 1.0;
	return (res);
}

double	**translation(double x, double y, double z)
{
	double	**res;

	res = identity(1, 1, 1);
	res[0][3] = x;
	res[1][3] = y;
	res[2][3] = z;
	return (res);
}
