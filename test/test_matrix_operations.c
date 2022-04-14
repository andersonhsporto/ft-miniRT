#include "../include/minirt.h"

static void	test_matrix_addition()
{
	t_coo	a;
	t_coo	b;
	t_coo	*res;
	a.x = 3.0; a.y = -2.0; a.z = 5.0; a.w = 1;
	b.x = -2.0; b.y = 3.0; b.z = 1.0; b.w = 0;
	res = matrix_addition(&a, &b);
	assert(res->x == 1.0 && "test_matrix_addition");
	assert(res->y == 1.0 && "test_matrix_addition");
	assert(res->z == 6.0 && "test_matrix_addition");
	assert(res->w == 1 && "test_matrix_addition");
	free(res);
}

static void	test_matrix_subtration()
{
	t_coo	a;
	t_coo	b;
	t_coo	*res;
	a.x = 3.0; a.y = 2.0; a.z = 1.0; a.w = 1;
	b.x = 5.0; b.y = 6.0; b.z = 7.0; b.w = 0;
	res = matrix_subtration(&a, &b);
	assert(res->x == -2.0 && "test_matrix_subtration");
	assert(res->y == -4.0 && "test_matrix_subtration");
	assert(res->z == -6.0 && "test_matrix_subtration");
	free(res);
}

static void	test_matrix_multipli_scalar()
{
	t_coo	a;
	double	b;
	t_coo	*res;
	a.x = 1.0; a.y = -2.0; a.z = 3.0; a.w = -4;
	b = 3.5;
	res = matrix_multipli_scalar(b, &a);
	assert(res->x == 3.5 && "test_matrix_subtration");
	assert(res->y == -7 && "test_matrix_subtration");
	assert(res->z == 10.5 && "test_matrix_subtration");
	assert(res->w == -14 && "test_matrix_subtration");
	free(res);
}

int	main()
{
	test_matrix_addition();
	test_matrix_subtration();
	test_matrix_multipli_scalar();
	return (0);
}