#include "minirt.h"

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

void	print_matrix(double **matrix, int size)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			printf("%f ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("<>>>>>>>>>>>>>>>>>>\n");
}


void	start_camera(t_cam_d *cam)
{
	const t_coo	*temp = double_cross(cam);
	const t_coo *add = vector_addition(&cam->view_point, &cam->orientation);
	double		**temp_matrix;
	t_coo		*temp_vector;

	temp_matrix = view_transform(&cam->view_point, (t_coo *)add, (t_coo *)temp);
	print_matrix(temp_matrix, 4);
	cam->transform = matrix_inverter(temp_matrix);
	print_matrix(cam->transform , 4);
	free_matrix(temp_matrix, 4);
	free((t_coo *)temp);
	free((t_coo *)add);
	camera_pixel_size(WIDTH, HEIGHT, cam);
	temp_vector = create_vector(0, 0, 0, 1);
	cam->origin = mult_matrix_vector_temp(cam->transform, temp_vector);
	free(temp_vector);
}
