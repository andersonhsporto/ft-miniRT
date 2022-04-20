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

t_coo	*vector_subtration(t_coo *a, t_coo *b)
{
	t_coo *res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	res->w = 0;
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
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
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
	res->w = a->w / lenght;
	return (res);
}
