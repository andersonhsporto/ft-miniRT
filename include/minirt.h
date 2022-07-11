#ifndef	MINIRT
# define MINIRT
# include "struct.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <assert.h>
# include <limits.h>

#define NX 640
#define NY 480
#define SPHERE 1
#define PLANE 2
#define CYLINDER 3
# define EPSILON 0.00001

t_coo	*vector_addition(t_coo *a, t_coo *b);

t_coo	*vector_subtration(t_coo *a, t_coo *b);

t_coo	*vector_multipli_scalar(double scalar, t_coo *a);

double	vector_lenght(t_coo *a);

t_coo	*vector_normalize(t_coo *a);

double	vector_abs(t_coo *a, t_coo *b);

t_coo	*vector_cross(t_coo *a, t_coo *b);

t_coo	*vector_multipli(t_coo *a, t_coo *b);

t_coo	*create_vector(double x, double y, double z, double w);

double	matrix_determinant(double **a);

double	**matrix_transpose(double **a);

double	**matrix_multiply(double **a, double **b);

double	**matrix_inverter(double **a);

double	**identity(double x, double y, double z);

double	**translation(double x, double y, double z);

double	**vector_to_matrix(t_coo *a);

double	**create_matrix(int col, int line);

double	matrix_x_multiply(double a[2][2]);

t_coo	*mult_matrix_vector(double **m1, t_coo *t1);

static double	**calculate_orientation(t_coo *left, t_coo *true_up, t_coo *forward, t_coo *from);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

double	cofator_4x4(double **a, int index[2]);

double	**sub_matrix(double	**a, int index[2], int col, int row);

double	**scalar_4x4_matrix(double **mat, double abs);

t_intersec	*plane_intersection(t_ray *base_ray, t_plane *obj, int obj_pos);

t_sphere	*init_sphere(void);

void	render_sphere_transform(t_sphere *sphere);

t_intersec	*sphere_intersection(t_ray *base_ray, t_sphere *obj, int obj_pos);

t_ray	*ray_for_pixel(t_cam *cam, int x, int y);

t_ray	*create_ray(t_coo *origin, t_coo *direction);

double	**view_transform(t_coo *from, t_coo *to, t_coo *up);

void	camera_pixel_size(int width, int height, t_cam *cam);

t_cam	*init_cam(void);

t_coo	*reflect(t_coo *v, t_coo *n);

t_coo	*normal_object_type(t_material *poly, t_coo *o_point, double *obj_type_height);

t_coo	*normal_at(double **transform, t_coo *w_point, t_material *poly, double *obj_type_height);

void	prepare_computations(t_comps *comps, t_ray *rt, t_intersec *hit, t_light *light, t_poly	*poly);

t_coo	*ray_position(t_ray *ray, double t);

t_caster	*put_intersection_in_cast(t_caster *cast, t_intersec *intersec);

t_caster	*init_intersec_list(t_caster *list);

int	is_shadowed(t_comps *comps, t_light *light, t_poly *poly);

t_coo	*lighting(t_comps args, t_light *current_light, int in_shadow);

void	all_sphere_intersec(t_caster *cast, t_ray *ray, t_poly *poly);

t_intersec	*hiter_point(t_caster	*head);

void	all_plane_intersec(t_caster *cast, t_ray *ray, t_poly *poly);

int	render(t_data *img);

t_ray	*ray_to_object_space(t_ray *ray, double **matrix);

t_plane	*init_plane(void);

double	**normal_rotation_matrix(t_coo *normal);

void	render_plane_transform(t_plane *plane);

t_cylinder	*init_cylinder(void);

void	render_cylinder_transform(t_cylinder *cylinder);

t_intersec	*cylinder_intersec(t_ray *base_ray, t_cylinder *cylinder, int pos);

void	all_cylinder_intersec(t_caster *cast, t_ray *ray, t_poly *poly);

t_coo	*slighting(t_coo *position, t_light *light, t_coo *eye, t_material *material, t_coo *normal, int is_shadow);
#endif
