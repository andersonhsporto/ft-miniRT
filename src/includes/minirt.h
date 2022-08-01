/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:26:07 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 21:36:08 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "libft.h"
#include "file.h"
#include "error_msg.h"

#include <stdio.h>
#include <mlx.h>
#include <fcntl.h>
#include <math.h>
#include <string.h> // TODO VERIFICAR SE É REALMENTE NECESSARIO

#define WIDTH 10
#define HEIGHT 10

#define EPSILON 0.00001

#define KEY_RELEASE 3
#define DESTROY_NOTIFY 17
#define EXPOSE 12
#define ESC 65307
#define BUTTON_RELEASE (1L << 1)
#define EXPOSURE_MASK (1L << 15)
#define NO_EVENT 0L

int check_args(int argc, char **argv);
int check_extension(char *file);
void init_data(t_mini *data);

void print_error(char *error_message);

void check_file(t_mini *data, char *file);

int allowed_symbol(char character);

int matrix_len(char **matrix);
void matrix_free(char **matrix);
char *replace_string(char *string, char character);

double str_to_double(char *str);

int	there_file_error(t_mini *data);

int print_image(t_mini *data);
int exit_esc(int keycode, t_mini *data);
int red_cross(t_mini *data);

void divide_coo(t_coo *coo, int nbr);

void my_mlx_pixel_put(t_image *data, int x, int y, int color);
void coo_pixel_put_vector(t_image *img, int y, int x, t_coo *color);

void start_camera(t_cam_d *cam);

void debug(t_mini *data); // TODO REMOVER
void print_vector_coo(char *vector, t_coo *vec);

// TODO trocar para clang no final

// Refactor // TODO: remove this

void get_hit(int x, int y, t_mini *data);
t_intersec *get_shadow_hit(t_coo *over_point, t_coo *path, t_mini *data);

int is_shadowed(t_comps *comps, t_mini *data);
t_coo lighting(t_comps args, int in_shadow, t_mini *data);
t_coo init_light_intensity(t_coo *rgb, double temp_data);
void prepare_computations(t_comps *comps, t_ray *rt, t_mini *data);
void render(t_mini *img);
t_ray ray_for_pixel(t_cam_d *cam, int x, int y);

void all_cylinder_intersec(t_caster *cast, t_ray *ray, t_poly *poly, t_sphere *list);
void all_plane_intersec(t_caster *cast, t_ray *ray, t_poly *poly, t_sphere *list);

void rt_mlx_pixel_put(t_image *data, int x, int y, t_coo *rgb);

void all_intersec(t_caster *cast, t_ray *ray, void *list, t_intersec *(f)(t_ray *, void *));

t_coo create_vector_temp(double x, double y, double z, double w); // add to header

//////////////////////////////////////////////////////////////////////////////////////////////
t_coo vector_subtraction_temp(t_coo *a, t_coo *b);
t_coo mult_matrix_vector_temp(double **m1, t_coo *t1);
t_coo normal_object_type_temp(t_coo o_point, double *obj_type_height);
t_coo normal_at_temp(double **transform, t_coo *w_point, double *obj_type_height);
t_coo vector_multipli_scalar_temp(double scalar, t_coo *a);
t_coo vector_addition_temp(t_coo *a, t_coo *b);

t_coo	str_to_coo_vector_temp(char	*string, int *error);

void camera_pixel_size(int width, int height, t_cam_d *cam);

t_coo vector_normalize_temp(t_coo *a);
void	free_mini(t_mini *data);
void	exit_and_free(t_mini *data, char *string, int code);
void	free_matrix(double **matrix, int line);

void	check_if_error(t_mini *data);
#endif