#include "../../include/minirt.h"

double	vector_abs(t_coo *a, t_coo *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
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

t_coo	*creat_vector(double x, double y, double z)
{
	t_coo	*res;

	res = (t_coo *)malloc(sizeof(t_coo));
	res->x = x;
	res->y = y;
	res->z = z;
	return (res);
}
