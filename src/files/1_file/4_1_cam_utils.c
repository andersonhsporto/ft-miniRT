#include "minirt.h"

static double	degrees_to_radians(const double degrees);

void	start_camera(t_cam_d *cam) //search leaks
{
	cam->transform = view_transform(cam->view_point, vector_addition(cam->view_point, cam->orientation),
		vector_cross(vector_cross(cam->orientation, create_vector(0, 1, 0, 0)), cam->orientation));
	cam->transform = matrix_inverter(cam->transform);
	camera_pixel_size(WIDTH, HEIGHT, cam);
	cam->origin = mult_matrix_vector(cam->transform, create_vector(0, 0, 0, 1));
}

static double degrees_to_radians(const double degrees)
{
	return (degrees * M_PI / 180);
}
