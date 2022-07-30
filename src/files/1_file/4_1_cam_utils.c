#include "minirt.h"

//vector_cross(vector_cross(&cam->orientation, create_vector(0, 1, 0, 0)), &cam->orientation))
t_coo	*double_cross(t_cam_d *cam)
{
	const t_coo	*new = create_vector(0, 1, 0, 0);;
	t_coo		*temp;
	t_coo		*cross;

	temp = vector_cross(&cam->orientation, (t_coo *)new);
	cross = vector_cross(temp, &cam->orientation);
	free((t_coo *)new);
	free(temp);
	return (cross);
}

void	start_camera(t_cam_d *cam)
{
	const t_coo	*temp = double_cross(cam);
	const t_coo *add = vector_addition(&cam->view_point, &cam->orientation);
	double		**temp_matrix;
	t_coo		*temp_vector;

	temp_matrix = view_transform(&cam->view_point, (t_coo *)add, (t_coo *)temp);
	cam->transform = matrix_inverter(temp_matrix);
	free_matrix(temp_matrix, 4);
	free((t_coo *)temp);
	free((t_coo *)add);
	camera_pixel_size(WIDTH, HEIGHT, cam);
	temp_vector = create_vector(0, 0, 0, 1);
	cam->origin = mult_matrix_vector_temp(cam->transform, temp_vector);
	free(temp_vector);
}
