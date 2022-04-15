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

static void	test_matrix_lenght_1()
{
	t_coo	a;
	double	b;
	double	compare;
	a.x = -1.0; a.y = -2.0; a.z = -3.0;
	b = matrix_lenght(&a);
	compare = sqrt(14);
	assert(b == compare && "test_matrix_lenght_1");
}

static void	test_matrix_lenght_2()
{
	t_coo	a;
	double	b;
	double	compare;
	a.x = 1.0; a.y = 2.0; a.z = 3.0;
	b = matrix_lenght(&a);
	compare = sqrt(14);
	assert(b == compare && "test_matrix_lenght_2");
}

static void	test_matrix_normalize()
{
	t_coo	a;
	t_coo	*res;
	a.x = 1.0; a.y = 2.0; a.z = 3.0; a.w = -4;
	res = matrix_normalize(&a);
	assert(res->x == 0.26726124191242438468455348087975 && "test_matrix_normalize");
	assert(res->y == 0.53452248382484876936910696175951 && "test_matrix_normalize");
	assert(res->z == 0.80178372573727315405366044263926 && "test_matrix_normalize");
	free(res);
}

static void	test_matrix_abs()
{
	t_coo	a;
	t_coo	b;
	double	res;

	a.x = 2.0; a.y = 3.0; a.z = 4.0; a.w = 0.0;
	b.x = 1.0; b.y = 2.0; b.z = 3.0; b.w = 0.0;
	res = matrix_abs(&a, &b);
	assert(res == 20 && "test_matrix_abs");
}

static void	test_matrix_cross()
{
	t_coo	a;
	t_coo	b;
	t_coo	*res;
	a.x = 1.0; a.y = 2.0; a.z = 3.0; a.w = 1;
	b.x = 2.0; b.y = 3.0; b.z = 4.0; b.w = 0;
	res = matrix_cross(&a, &b);
	assert(res->x == -1.0 && "test_matrix_cross");
	assert(res->y == 2.0 && "test_matrix_cross");
	assert(res->z == -1.0 && "test_matrix_cross");
	free(res);
}

int	main()
{
	test_matrix_addition();
	test_matrix_subtration();
	test_matrix_multipli_scalar();
	test_matrix_lenght_1();
	test_matrix_lenght_2();
	test_matrix_normalize();
	test_matrix_abs();
	return (0);
}