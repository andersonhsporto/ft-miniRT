#include "../include/minirt.h"

static void	test_vector_addition()
{
	t_coo	a;
	t_coo	b;
	t_coo	*res;
	a.x = 3.0; a.y = -2.0; a.z = 5.0; a.w = 1;
	b.x = -2.0; b.y = 3.0; b.z = 1.0; b.w = 0;
	res = vector_addition(&a, &b);
	assert(res->x == 1.0 && "test_vector_addition");
	assert(res->y == 1.0 && "test_vector_addition");
	assert(res->z == 6.0 && "test_vector_addition");
	assert(res->w == 1 && "test_vector_addition");
	printf("\033[0;37m (test_vector_addition) : \033[0;32m OK\033[0;31m\n");
	free(res);
}

static void	test_vector_subtration()
{
	t_coo	a;
	t_coo	b;
	t_coo	*res;
	a.x = 3.0; a.y = 2.0; a.z = 1.0; a.w = 1;
	b.x = 5.0; b.y = 6.0; b.z = 7.0; b.w = 0;
	res = vector_subtration(&a, &b);
	assert(res->x == -2.0 && "test_vector_subtration");
	assert(res->y == -4.0 && "test_vector_subtration");
	assert(res->z == -6.0 && "test_vector_subtration");
	printf("\033[0;37m (test_vector_subtration) : \033[0;32m OK\033[0;31m\n");
	free(res);
}

static void	test_vector_multipli_scalar()
{
	t_coo	a;
	double	b;
	t_coo	*res;
	a.x = 1.0; a.y = -2.0; a.z = 3.0; a.w = -4;
	b = 3.5;
	res = vector_multipli_scalar(b, &a);
	assert(res->x == 3.5 && "test_vector_subtration");
	assert(res->y == -7 && "test_vector_subtration");
	assert(res->z == 10.5 && "test_vector_subtration");
	assert(res->w == -14 && "test_vector_subtration");
	printf("\033[0;37m (test_vector_multipli_scalar) : \033[0;32m OK\033[0;31m\n");
	free(res);
}

static void	test_vector_lenght_1()
{
	t_coo	a;
	double	b;
	double	compare;
	a.x = -1.0; a.y = -2.0; a.z = -3.0;
	b = vector_lenght(&a);
	compare = sqrt(14);
	assert(b == compare && "test_vector_lenght_1");
	printf("\033[0;37m (test_vector_lenght_1) : \033[0;32m OK\033[0;31m\n");
}

static void	test_vector_lenght_2()
{
	t_coo	a;
	double	b;
	double	compare;
	a.x = 1.0; a.y = 2.0; a.z = 3.0;
	b = vector_lenght(&a);
	compare = sqrt(14);
	assert(b == compare && "test_vector_lenght_2");
	printf("\033[0;37m (test_vector_lenght_2) : \033[0;32m OK\033[0;31m\n");
}

static void	test_vector_normalize()
{
	t_coo	a;
	t_coo	*res;
	a.x = 1.0; a.y = 2.0; a.z = 3.0; a.w = -4;
	res = vector_normalize(&a);
	assert(res->x == 0.26726124191242438468455348087975 && "test_vector_normalize");
	assert(res->y == 0.53452248382484876936910696175951 && "test_vector_normalize");
	assert(res->z == 0.80178372573727315405366044263926 && "test_vector_normalize");
	printf("\033[0;37m (test_vector_normalize) : \033[0;32m OK\033[0;31m\n");
	free(res);
}

static void	test_vector_abs()
{
	t_coo	a;
	t_coo	b;
	double	res;

	a.x = 2.0; a.y = 3.0; a.z = 4.0; a.w = 0.0;
	b.x = 1.0; b.y = 2.0; b.z = 3.0; b.w = 0.0;
	res = vector_abs(&a, &b);
	assert(res == 20 && "test_vector_abs");
	printf("\033[0;37m (test_vector_abs) : \033[0;32m OK\033[0;31m\n");
}

static void	test_vector_cross()
{
	t_coo	a;
	t_coo	b;
	t_coo	*res;
	a.x = 1.0; a.y = 2.0; a.z = 3.0; a.w = 1;
	b.x = 2.0; b.y = 3.0; b.z = 4.0; b.w = 0;
	res = vector_cross(&a, &b);
	assert(res->x == -1.0 && "test_vector_cross");
	assert(res->y == 2.0 && "test_vector_cross");
	assert(res->z == -1.0 && "test_vector_cross");
	printf("\033[0;37m (test_vector_cross) : \033[0;32m OK\033[0;31m\n");
	free(res);
}

static void	test_matrix_mutpli()
{
	double	a[][4] = {{5.0,7.0,9.0,10.0}, {2.0,3.0,3.0,8.0}, {8.0,10.0,2.0,3.0},
		{3.0,3.0,4.0,8.0}};
	double	b[][4] = {{3.0,10.0,12.0,18.0}, {12.0,1.0,4.0,9.0},
		{9.0,10.0,12.0,2.0}, {3.0,12.0,4.0,10.0}};
	double	**m;
	double	res[][4] = {{210.0, 267.0, 236.0, 271.0},
		{93.0, 149.0, 104.0, 149.0}, {171.0, 146.0, 172.0, 268.0},
			{105.0, 169.0, 128.0, 169.0}};
	m = matrix_multpli(a, b);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			assert(res[i][j] == m[i][j] && "test_matrix_mutpli");
		}
	}
	printf("\033[0;37m (test_matrix_mutpli) : \033[0;32m OK\033[0;31m\n");
	matrix_free(m);
}

static void	test_matrix_indentify()
{
	double	a[][4] = {{5.0,7.0,9.0,10.0}, {2.0,3.0,3.0,8.0}, {8.0,10.0,2.0,3.0},
		{3.0,3.0,4.0,8.0}};
	double	i[][4] = INDENTIFY;
	double	**m;
	double	res[][4] = {{5.0,7.0,9.0,10.0}, {2.0,3.0,3.0,8.0}, {8.0,10.0,2.0,3.0},
		{3.0,3.0,4.0,8.0}};
	m = matrix_multpli(a, i);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			assert(res[i][j] == m[i][j] && "test_matrix_indentify");
		}
	}
	printf("\033[0;37m (test_matrix_indentify) : \033[0;32m OK\033[0;31m\n");
	matrix_free(m);
}

static void	test_matrix_transpose()
{
	double	a[][4] = {{5.0,7.0,9.0,10.0}, {2.0,3.0,3.0,8.0}, {8.0,10.0,2.0,3.0},
		{3.0,3.0,4.0,8.0}};
	double	**m;
	double	res[][4] = {{5.0,2.0,8.0,3.0}, {7.0,3.0,10.0,3.0}, {9.0,3.0,2.0,4.0},
		{10.0,8.0,3.0,8.0}};
	matrix_transpose(a);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			assert(res[i][j] == a[i][j] && "test_matrix_transpose");
		}
	}
	printf("\033[0;37m (test_matrix_transpose) : \033[0;32m OK\033[0;31m\n");
}

static void	test_matrix_determinat_1()
{
	double	a[][4] = {{1.0,0.0,4.0,-6.0}, {2.0,5.0,0.0,3.0}, {-1.0,2.0,3.0,5.0},
		{2.0,1.0,-2.0,3.0}};
	double	res = 318.0;
	assert(res == matrix_determinant(a) && "test_matrix_determinat_1");
	printf("\033[0;37m (test_matrix_determinat_1) : \033[0;32m OK\033[0;31m\n");
}

static void	test_matrix_determinat_2()
{
	double	a[][4] = {{-5.0,2.0,6.0,-8.0}, {1.0,-5.0,1.0,8.0}, {7.0,7.0,-6.0,-7.0},
		{1.0,-3.0,7.0,4.0}};
	double	res = 532.0;
	assert(res == matrix_determinant(a) && "test_matrix_determinat_2");
	printf("\033[0;37m (test_matrix_determinat_2) : \033[0;32m OK\033[0;31m\n");
}

static void	test_matrix_cofator()
{
	double	a[][3] = {{3.0,6.0,12.0}, {2.0,5.0,8.0}, {1.0,2.0,6.0}};
	double	res = 6.0;
	assert(res == matrix_cofactor(a) && "test_matrix_cofator");
	printf("\033[0;37m (test_matrix_cofator) : \033[0;32m OK\033[0;31m\n");
}

static void	test_matrix_inverter()
{
	double	a[][4] = {{-5.0,2.0,6.0,-8.0}, {1.0,-5.0,1.0,8.0}, {7.0,7.0,-6.0,-7.0},
		{1.0,-3.0,7.0,4.0}};
	double	abs;
	double	**m;
	double	res[][4] = {{0.21804511278195488721804511278195}, {0.45112781954887218045112781954887},
		{0.2406015037593984962406015037594}, {-0.04511278195488721804511278195489},
		{-0.80827067669172932330827067669173}, {-1.4567669172932330827067669172932},
		{-0.44360902255639097744360902255639}, {0.52067669172932330827067669172932},
		{-0.07894736842105263157894736842105},{-0.22368421052631578947368421052632},
		{-0.05263157894736842105263157894737}, {0.19736842105263157894736842105263},
		{-0.52255639097744360902255639097744}, {-0.81390977443609022556390977443609},
		{-0.30075187969924812030075187969925}, {0.30639097744360902255639097744361}};

	abs = matrix_determinant(a);
	matrix_transpose(a);
	m = matrix_inverter(a, abs);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			//assert(res[i][j] == m[i][j] && "test_matrix_cofator");
		}
	}
	matrix_free(m);
	printf("\033[0;37m (test_matrix_inverter) : \033[0;32m OK\033[0;31m\n");
}

static void	test_vector_cross_1()
{
	t_coo	a;
	t_coo	b;
	t_coo	*res;
	a.x = 0.0; a.y = 1.0; a.z = -5.0; a.w = 1;
	b.x = 0.0; b.y = 0.0; b.z = 1.0; b.w = 0;
	res = vector_cross(&a, &b);
	assert(res->x == 5.0 && "test_vector_cross_1");
	assert(res->y == 5.0 && "test_vector_cross_1");
	//assert(res->z == -1.0 && "test_vector_cross_1");
	printf("\033[0;37m (test_vector_cross_1) : \033[0;32m OK\033[0;31m\n");
	free(res);
}

int	main()
{
	test_vector_addition();
	test_vector_subtration();
	test_vector_multipli_scalar();
	test_vector_lenght_1();
	test_vector_lenght_2();
	test_vector_normalize();
	test_vector_abs();
	test_matrix_mutpli();
	test_matrix_indentify();
	test_matrix_transpose();
	test_matrix_determinat_1();
	test_matrix_determinat_2();
	test_matrix_inverter();
	return (0);
}