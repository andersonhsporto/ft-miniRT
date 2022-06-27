/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:39:56 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/26 23:11:13 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_lighting(double *position, t_utils *utils, t_light_d *light, t_mini *data);
double	*diffuse_color(double l_dot, t_mini *data, t_light_d *light);
double	r_dot(double *light, double *normal, double *eye);
double	l_dot(double *light, double *normal, double *position);

double	*slighting(double *position, t_mini *data, double *eye)
{
	const t_light_d	*light = data->scene->light[0];
	t_utils			utils;

	init_lighting(position, &utils, light, data);
	if (utils.dot_l <= 0.0)
		diffuse_specular_zero(&utils);
	else
	{
		utils.diffuse = diffuse_color(utils.dot_l, data, light);
		utils.dot_r = r_dot(light, utils.normal, eye);
		if (utils.dot_r <= 0.0)
			utils.specular = vector_zero();
		else
		{
			//Shinniness ou Brilho e depois do dot_r
			utils.factor = pow(utils.dot_r, 200.0);
			utils.specular = vector_multipli_scalar(0.9 * utils.factor, light->intensity);
		}
	}
	return vector_addition(vector_addition(utils.ambient, utils.diffuse), utils.specular);
}

void	init_lighting(double *position, t_utils *utils, t_light_d *light, t_mini *data)
{
	utils->ambient = vector_multipli_scalar(0.1, data->hit->color); // cor da luz
	utils->normal = vector_normalize_double(position);
	utils->dot_l = l_dot(light->posi, utils->normal, position);
	return ;
}

double	*diffuse_color(double l_dot, t_mini *data, t_light_d *light)
{
	const double	*color = vector_multipli(data->hit->color, light->intensity);
	double			*difuse_color;

	difuse_color = vector_multipli_scalar(l_dot, \
					vector_multipli_scalar(data->light_a->ratio, color));
	free((double *)color);
	return(difuse_color);
}

double	r_dot(double *light, double *normal, double *eye)
{
	const double	*scalar = vector_multipli_scalar(-1.0, light);
	const double	*refle = reflect(scalar, normal);
	const double	r_dot = vector_abs(refle, eye);

	free((double *)scalar);
	free((double *)refle);
	return(r_dot);
}

double	l_dot(double *light, double *normal, double *position)
{
	const double	*subtraction = vector_subtraction(light, position);
	const double	*lightvec = vector_normalize_double((double *)subtraction);
	const double	l_dot = vector_abs(lightvec, normal);

	free((double *)subtraction);
	free((double *)lightvec);
	return (l_dot);
}
