#include "../include/minirt.h"

double	matrix_abs(t_coo *a, t_coo *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w);
}

t_coo	*matrix_cross(t_coo *a, t_coo *b)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
	return (res);
}
