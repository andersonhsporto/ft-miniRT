#include "minirt.h"

t_intersec	*get_hit(int x, int y, t_mini *data, t_poly *poly)
{
	t_caster	*intersec;
	t_intersec	*hit;
	t_element	*tmp;

	data->ray = ray_for_pixel(data->cam, x, y);
	intersec = init_intersec_list();
	tmp = data->element;
	while (tmp != NULL)
	{
		if (tmp->type == sphere)
			all_intersec(intersec, data->ray, poly->sphere[0], tmp->ptr, sphere_intersection);
		else if (tmp->type == cylinder)
			all_intersec(intersec, data->ray, poly->cylinder[0], tmp->ptr, cylinder_intersec);
		else if (tmp->type == plane)
			all_intersec(intersec, data->ray, poly->plane[0], tmp->ptr, plane_intersection);
		tmp = tmp->next;
	}
	hit = hiter_point(intersec);
	free(intersec);
	return(hit);
}

t_intersec	*get_shadow_hit(t_coo *over_point, t_coo *path, t_poly *poly, t_mini *data)
{
	t_caster	*intersec;
	t_intersec	*hit;
	t_ray		*ray;
	t_element	*tmp;

	ray = create_ray(over_point, vector_normalize(path));
	intersec = init_intersec_list();
	tmp = data->element;
	while (tmp != NULL)
	{
		if (tmp->type == sphere)
			all_intersec(intersec, ray, poly->sphere[0], tmp->ptr, sphere_intersection);
		else if (tmp->type == cylinder)
			all_intersec(intersec, ray, poly->cylinder[0], tmp->ptr, cylinder_intersec);
		else if (tmp->type == plane)
			all_intersec(intersec, ray, poly->plane[0], tmp->ptr, plane_intersection);
		tmp = tmp->next;
	}
	hit = hiter_point(intersec);
	free(intersec);
	return(hit);
}
