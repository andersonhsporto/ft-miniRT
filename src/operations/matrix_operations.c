#include "../include/minirt.h"

t_coo	*matrix_addition(t_coo *a, t_coo *b)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	res->w = a->w + b->w;
	return (res);
}

t_coo	*matrix_subtration(t_coo *a, t_coo *b)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	res->w = 0;
	return (res);
}

t_coo	*matrix_multipli_scalar(double scalar, t_coo *a)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x * scalar;
	res->y = a->y * scalar;
	res->z = a->z * scalar;
	res->w = a->w * scalar;
	return (res);
}
