#include "minirt.h"

void	print_element_lst(t_element *lst);
void	print_cam_data(t_datacam *data);

void	debug(t_mini *data)
{
	printf("DEBUG START\n");
	printf("Ambient ->r %f\n", data->light_a->ratio);
	printf("Ambient ->x %f\n", data->light_a->rgb[0]);
	printf("Ambient ->y %f\n", data->light_a->rgb[1]);
	printf("Ambient ->z %f\n\n", data->light_a->rgb[2]);
	printf("Camera FOV ->%d\n", data->cam->fov);
	printf("Camera View Point ->%f\n", data->cam->view_point.x);
	printf("Camera View Point ->%f\n", data->cam->view_point.y);
	printf("Camera View Point ->%f\n", data->cam->view_point.z);
	printf("Camera Normalized ->%f\n", data->cam->normalized_vector.x);
	printf("Camera Normalized ->%f\n", data->cam->normalized_vector.y);
	printf("Camera Normalized ->%f\n\n", data->cam->normalized_vector.z);
	printf("Light Brightness ->%f\n", data->light->bright);
	printf("Light Point ->x %f\n", data->light->point.x);
	printf("Light Point ->y %f\n", data->light->point.y);
	printf("Light Point ->z %f\n\n", data->light->point.z);
	print_element_lst(data->element);
	printf("DEBUG END\n");
	return ;
}

void	print_element_lst(t_element *lst)
{
	while (lst)
	{
		printf("Element Type ->%d\n", lst->type);
		if (lst->type == sphere)
		{
			t_sphere *sphere_debug = (t_sphere *)lst->ptr;
			printf("Sphere Center ->x %f\n", sphere_debug->center[0]);
			printf("Sphere Center ->y %f\n", sphere_debug->center[1]);
			printf("Sphere Center ->z %f\n", sphere_debug->center[2]);
			printf("Sphere Diameter ->%f\n", sphere_debug->diameter);
			printf("Sphere Color ->x %f\n", sphere_debug->color[0]);
			printf("Sphere Color ->y %f\n", sphere_debug->color[1]);
			printf("Sphere Color ->z %f\n", sphere_debug->color[2]);
			ft_putchar_fd('\n', 1);
		}
		else if (lst->type == plane)
		{
			t_plane *plane_debug = (t_plane *)lst->ptr;
			printf("Plane Normalized ->x %f\n", plane_debug->normalized.x);
			printf("Plane Normalized ->y %f\n", plane_debug->normalized.y);
			printf("Plane Normalized ->z %f\n", plane_debug->normalized.z);
			printf("Plane Color ->x %f\n", plane_debug->color.x);
			printf("Plane Color ->y %f\n", plane_debug->color.y);
			printf("Plane Color ->z %f\n\n", plane_debug->color.z);
		}
		else if (lst->type == cylinder)
		{
			t_cylinder *cylinder_debug = (t_cylinder *)lst->ptr;
			printf("Cylinder Center ->x %f\n", cylinder_debug->coordinates[0]);
			printf("Cylinder Center ->y %f\n", cylinder_debug->coordinates[1]);
			printf("Cylinder Center ->z %f\n", cylinder_debug->coordinates[2]);
			printf("Cylinder Normalized ->x %f\n", cylinder_debug->normalized[0]);
			printf("Cylinder Normalized ->y %f\n", cylinder_debug->normalized[1]);
			printf("Cylinder Normalized ->z %f\n", cylinder_debug->normalized[2]);
			printf("Cylinder Diameter ->%f\n", cylinder_debug->diameter);
			printf("Cylinder Height ->%f\n", cylinder_debug->height);
			printf("Cylinder Color ->x %f\n", cylinder_debug->color[0]);
			printf("Cylinder Color ->y %f\n", cylinder_debug->color[1]);
			printf("Cylinder Color ->z %f\n", cylinder_debug->color[2]);
		}
		lst = lst->next;
	}
	return ;
}

void	print_vector(char *vector, t_vector vec)
{
	printf("Vector %s: %f, %f, %f \n", vector, vec.x, vec.y, vec.z);
	return ;
}

void	print_cam_data(t_datacam *data)
{
	printf("\nDEBUG CAM DATA\n");
	printf("View Height ->%f\n", data->viewport_height);
	printf("View Width ->%f\n", data->viewport_width);
	print_vector("view_up", data->view_up);
	print_vector("w", data->w);
	print_vector("u", data->u);
	print_vector("v", data->v);
	print_vector("horizontal", data->hori_dir);
	print_vector("vertical", data->vert_dir);
	print_vector("llcorner", data->lower_left_corner);
	printf("DEBUG CAM DATA END\n");
	return ;
}

t_sphere	*get_sphere_in_list(t_element *lst)
{
	t_sphere	*sp;
	t_element	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (temp->type == sphere)
		{
			sp = temp->ptr;
			return (sp);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_cylinder	*get_cy_in_list(t_element *lst)
{
	t_cylinder	*cy;
	t_element	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (temp->type == cylinder)
		{
			cy = temp->ptr;
			return (cy);
		}
		temp = temp->next;
	}
	return (NULL);
}

t_plane	*get_plane_in_list(t_element *lst)
{
	t_plane		*ptr;
	t_element	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (temp->type == plane)
		{
			ptr = temp->ptr;
			return (ptr);
		}
		temp = temp->next;
	}
	return (NULL);
}
