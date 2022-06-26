
// double	get_sphere_discriminant(t_ray *ray, t_obj_d *obj, double *oc)
// {
// 	const double	a = vector_abs(ray->direction, ray->direction);
// 	const double	b = 2.0 * vector_abs(oc, ray->direction);
// 	const double	c = vector_abs(oc, oc) - (obj->radius * obj->radius);

// 	return ((b * b) - (4.0 * a * c));
// }

// t_intersec	*get_intersection(t_ray *ray, double *oc, double discriminant)
// {
// 	const double	a = vector_abs(ray->direction, ray->direction);
// 	const double	b = 2.0 * vector_abs(oc, ray->direction);
// 	t_intersec		*intersection_points;

// 	intersection_points = (t_intersec *)malloc(sizeof(t_intersec));
// 	intersection_points->t1 = (-b - sqrt(discriminant)) / (2.0 * a);
// 	intersection_points->t2 = (-b + sqrt(discriminant)) / (2.0 * a);
// 	intersection_points->cont = 3;
// 	return (intersection_points);
// }

// t_intersec	*sphere_intersection(t_ray *rayy, t_li *obj)
// {
// 	const t_ray		*ray = ray_to_object_space(rayy, matrix_identify(1,1,1,1));
// 	const double	*oc = vector_subtraction(ray->origin, obj->position);
// 	const double	discriminant = get_sphere_discriminant(ray, obj, oc);
// 	t_intersec		*intersection_points;

// 	if (discriminant < 0)
// 	{
// 		free((double *)oc);
// 		return (NULL);
// 	}
// 	intersection_points = get_intersection(ray, oc, discriminant);
// 	free((double *)oc);
// 	return (intersection_points);
// }
