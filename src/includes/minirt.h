/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:26:07 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/04 10:04:24 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "file.h"
# include "error_msg.h"

# include <stdio.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 600
# define HEIGHT 600
# define EPSILON 0.00001
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define EXPOSE 12
# define ESC 65307
# define NO_EVENT 0L

int			check_args(int argc, char **argv);
int			check_extension(char *file);
void		init_data(t_mini *data);
void		print_error(char *error_message);
void		check_file(t_mini *data, char *file);
int			matrix_len(char **matrix);
void		matrix_free(char **matrix);
char		*replace_string(char *string, char character);
double		str_to_double(char *str);
int			print_image(t_mini *data);
int			exit_esc(int keycode, t_mini *data);
int			red_cross(t_mini *data);
void		divide_coo(t_coo *coo, int nbr);
void		start_camera(t_cam_d *cam);
void		get_hit(int x, int y, t_mini *data);
t_intersec	*get_shadow_hit(t_coo *over_point, t_coo *path, t_mini *data);
int			is_shadowed(t_comps *comps, t_mini *data);
t_coo		lighting(t_comps args, int in_shadow, t_mini *data);
t_coo		init_light_intensity(t_coo *rgb, double temp_data);
void		prepare_computations(t_comps *comps, t_ray *rt, t_mini *data);
void		render(t_mini *img);
t_ray		ray_for_pixel(t_cam_d *cam, int x, int y);
void		rt_mlx_pixel_put(t_image *data, int x, int y, t_coo rgb);
void		all_intersec(t_caster *cast, t_ray *ray, void *list, \
t_intersec *(f)(t_ray *, void *));
t_coo		create_vector_temp(double x, double y, double z, double w);
t_coo		vector_subtraction_temp(t_coo *a, t_coo *b);
t_coo		mult_matrix_vector_temp(double **m1, t_coo *t1);
t_coo		normal_object_type_temp(t_coo o_point, double *obj_type_height);
t_coo		vector_multipli_scalar_temp(double scalar, t_coo *a);
t_coo		vector_addition_temp(t_coo *a, t_coo *b);
double		matrix_determinant(double **a);
void		camera_pixel_size(int width, int height, t_cam_d *cam);
t_coo		vector_normalize_temp(t_coo *a);
void		free_mini(t_mini *data);
void		free_intersec_list(t_caster *intersect);
void		free_matrix(double **matrix, int line);
void		exit_and_free(t_mini *data, char *string, int code);
void		free_element_list(t_mini *data);
void		check_and_free(t_mini *data);
int			there_file_error(t_mini *data);
void		check_if_error(t_mini *data);
t_intersec	*create_intersec(double *vals, t_ray *ray, t_cylinder_d *cyd);
void		get_obj_props(t_comps *comps, int obj_type, int obj_pos, \
t_mini *data);
t_coo		*get_cylinder_normal(double height, t_coo *o_point);
void		get_normal_vec(t_element *node, double *ch, t_comps *comps, \
int obj_pos);
void		helper_cy(double **matrix, double *vector);
#endif
