/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:26:07 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/27 01:49:30 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "file.h"
# include "error_msg.h"

# include "tracer.h"

# include <stdio.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include <string.h> // check in end

# define WIDTH 600
# define HEIGHT 600
# define RESOLUTION 600

# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17
# define EXPOSE 2
# define ESC 65307
# define BUTTON_RELEASE (1L << 1)
# define EXPOSURE_MASK (1L << 15)
# define NO_EVENT 0L

int			check_args(int argc, char **argv);
int			check_extension(char *file);
void		init_data(t_mini *data);

void		print_error(char *error_message);

void		check_file(t_mini *data, char *file);

int			allowed_symbol(char character);

int			matrix_len(char **matrix);
void		matrix_free(char **matrix);
char		*replace_string(char *string, char character);
int			out_range_double(t_vector vector, double min, double max);
void		swap_double(double *a, double *b);

double		str_to_double(char *str);

double		get_viewport_height(int fov);
void		orienting_camera(t_mini *data);


int			exit_esc(int keycode, t_mini *data);
int			red_cross(t_mini *data);
int			put_image(t_mini *data);

void	rt_pixel_put_vector(t_image *img, int x, int y, t_vector color);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);

void	debug(t_mini *data);
void	print_vector(char *vector, t_vector vec);
void	print_cam_data(t_datacam *data);
void	render(t_mini *data, t_scene *scene, t_image *img);

t_hit		*hit_scene_object(t_mini *data);
t_ray		*ray_direction(t_mini *data, int x, int y);
double		*there_is_light(t_mini *data);

double		*slighting(double *position, t_mini *data, double *eye);

void		*diffuse_specular_zero(t_utils	*utils);

void	hit(t_mini *data, int x, int y);

t_intersec	*sphere_intersection(t_ray *rayy, t_sphere *lst);
t_intersec	*cylinder_intersection(t_ray *ray, t_cylinder *ptr);
t_intersec	*plane_intersection(t_ray *ray, t_plane *ptr);

#endif