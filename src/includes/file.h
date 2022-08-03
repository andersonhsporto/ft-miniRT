/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:49:17 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/08/02 01:23:49 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "struct.h"

# define NO_EVENT 0L

int			legal_char(char character);
int			out_range_coo(t_coo *vector, double min, double max);
void		get_line_scene(t_mini *data, char *line);

int			find_ambient(t_mini *data, char	**string);
t_ambient	*init_ambient(char **string, t_mini *data);
int			find_camera(t_mini *data, char	**string);
t_cam_d		*init_camera(char **string, t_mini *data);

int			find_light(t_mini *data, char **string);
t_light_d	*init_light(char **string, t_mini *data);

t_coo		str_to_coo_vector(char *string, int *error);

t_element	*element_new(int type, int id, void *element);
t_element	*get_last_node(t_element *lst);
void		element_add_back(t_element **lst, t_element *new);

int			find_sphere(char **string);
void		lst_new_sphere(t_mini *data, char **string);

int			find_plane(char **string);
void		lst_new_plane(t_mini *data, char **string);

int			find_cylinder(char **string);
void		lst_new_cylinder(t_mini *data, char **string);

#endif