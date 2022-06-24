/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:49:17 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/24 12:25:14 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "struct.h"

int			legal_char(char character);
int			out_range_int(t_vector vector, int min, int max);
void		get_line_scene(t_mini *data, char *line);

int			find_ambient(t_mini *data, char	**string);
t_ambient	*init_ambient(char	**string);
t_vector	*init_rgb(char	*string);

int			find_camera(t_mini *data, char	**string);
t_cam		*init_camera(char **string);

int			find_light(t_mini *data, char **string);
t_light		*init_light(char **string);

t_vector	str_to_double_vector(char *string, char *error_message);
double		*str_to_double_pointer(char	*string, char *error_message);

t_element	*element_new(int type, void *element);
t_element	*get_last_node(t_element *lst);
void		element_add_back(t_element **lst, t_element *new);

int			find_sphere(char **string);
t_sphere	*init_sphere(char **string);
void		lst_new_sphere(t_mini *data, char **string);

int			find_plane(char **string);
t_plane		*init_plane(char **string);
void		lst_new_plane(t_mini *data, char **string);

int			find_cylinder(char **string);
t_cylinder	*init_cylinder(char **string);
void		lst_new_cylinder(t_mini *data, char **string);

#endif