#include "minirt.h"

void free_data(t_mini *data)
{
	free(data->cam->orientation);
	return ;
}