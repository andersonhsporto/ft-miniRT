#include "minirt.h"

static double	degrees_to_radians(const double degrees);
static double	get_viewport_height(const double fov);
static double	get_aspect_ratio(void);
static t_vector	get_lower_left_corner(const t_cam_d *cam);

void	start_camera(t_cam_d *cam)
{
	cam->viewport_height = 	get_viewport_height(cam->fov);
	cam->viewport_width = cam->viewport_height * get_aspect_ratio();
	cam->vup = vector_new(0, 1, 0);
	cam->w = unit_vector(vector_mult(cam->orientation, -1));
	cam->horizontal = vector_mult(cam->u, cam->viewport_width);
	cam->vertical = vector_mult(cam->v, cam->viewport_height);
	cam->lower_left_corner = get_lower_left_corner(cam);
	printf("viewport_height: %f\n", cam->viewport_height);
	printf("viewport_width: %f\n", cam->viewport_width);
	print_vector("vup", cam->vup);
	print_vector("w", cam->w);
	print_vector("u", cam->u);
	print_vector("v", cam->v);
	print_vector("horizontal", cam->horizontal);
	print_vector("vertical", cam->vertical);
	print_vector("lower_left_corner", cam->lower_left_corner);
}

static double degrees_to_radians(const double degrees)
{
	return (degrees * M_PI / 180);
}

static double	get_viewport_height(const double fov)
{
	const double	degrees = degrees_to_radians(fov);
	const double	h = tan(degrees / 2.0);
	return (2.0 * h);
}

static double	get_aspect_ratio(void)
{
	const double	width = WIDTH * 1.0;
	const double	height = HEIGHT * 1.0;
	return (width / height);
}

static t_vector	get_lower_left_corner(const t_cam_d *cam)
{
	const t_vector	temp = vector_sub(cam->view_point, \
							vector_div(cam->horizontal, 2.0));
	const t_vector	temp2 = vector_sub(temp, \
							vector_div(cam->vertical, 2.0));
	t_vector		lower_left_corner;

	lower_left_corner = vector_sub(temp2, cam->w);
	return (lower_left_corner);
}
