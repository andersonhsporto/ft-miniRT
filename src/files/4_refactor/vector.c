#include "minirt.h"

t_coo	vector_multipli_scalar_temp(double scalar, t_coo *a)
{
	t_coo	res;

	res.x = a->x * scalar;
	res.y = a->y * scalar;
	res.z = a->z * scalar;
	res.w = a->w * scalar;
	return (res);
}

t_coo	vector_addition_temp(t_coo *a, t_coo *b)
{
	t_coo	res;

	res.x = a->x + b->x;
	res.y = a->y + b->y;
	res.z = a->z + b->z;
	res.w = a->w + b->w;
	return (res);
}

t_coo	vector_subtration_temp(t_coo *a, t_coo *b)
{
	t_coo	res;

	res.x = a->x - b->x;
	res.y = a->y - b->y;
	res.z = a->z - b->z;
	res.w = a->w - b->w;
	return (res);
}

t_coo	create_vector_temp(double x, double y, double z, double w)
{
	t_coo	res;

	res.x = x;
	res.y = y;
	res.z = z;
	res.w = w;
	return (res);
}

t_coo	vector_normalize_temp(t_coo *a)
{
	t_coo	res;
	double	lenght;

	lenght = vector_lenght(a);
	res.x = a->x / lenght;
	res.y = a->y / lenght;
	res.z = a->z / lenght;
	return (res);
}

static t_coo	get_cylinder_normal_temp(double height, t_coo *o_point)
{
	double		dist;
	double		min;
	double		max;

	max = height / 2.0;
	min = -1.0 * max;
	dist = pow(o_point->x, 2) + pow(o_point->z, 2);
	if (dist < 1 && (o_point->y >= max - EPSILON))
		return (create_vector_temp(0, 1, 0, 0));
	else if (dist < 1 && (o_point->y <= min + EPSILON))
		return (create_vector_temp(0, -1, 0, 0));
	else
		return (create_vector_temp(o_point->x, 0, o_point->z, 0));
}

t_coo	normal_object_type_temp(t_coo o_point, double *obj_type_height)
{
	t_coo	temp = create_vector_temp(0, 0, 0, 1);
	if (obj_type_height[0] == sphere)
		return (vector_subtration_temp(&o_point, &temp));
	else if (obj_type_height[0] == plane)
		return (create_vector_temp(0, 1, 0, 0));
	else if (obj_type_height[0] == cylinder)
		return (get_cylinder_normal_temp(obj_type_height[1], &o_point));
}

t_coo	normal_at_temp(double **transform, t_coo *w_point, double *obj_type_height)
{
	t_coo	o_point;
	t_coo	o_normal;
	t_coo	w_normal;
	double	**inv_trans;
	double	**transp_trans;

	inv_trans = matrix_inverter(transform);
	o_point = mult_matrix_vector_temp(inv_trans, w_point);
	o_normal = normal_object_type_temp(o_point, obj_type_height);
	transp_trans = matrix_transpose(inv_trans);
	w_normal = mult_matrix_vector_temp(transp_trans, &o_normal);
	w_normal.w = 0;
	return (vector_normalize_temp(&w_normal));
}