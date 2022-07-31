/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:49:17 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 14:36:35 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "struct.h"

int			legal_char(char character);
int			out_range_coo(t_coo *vector, double min, double max);
void		get_line_scene(t_mini *data, char *line);

int			find_ambient(t_mini *data, char	**string);
t_ambient	*init_ambient(char	**string, t_mini *data);

int			find_camera(t_mini *data, char	**string);
t_cam_d		*init_camera(char	**string);

int				find_light(t_mini *data, char **string);
t_light_d		*init_light(char **string);

t_coo			*str_to_coo_vector(char	*string, char *error_message);

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