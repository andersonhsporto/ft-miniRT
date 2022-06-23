/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 00:39:56 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/23 02:20:05 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// position		*hitposition,
// t_light_d		*light data->scene->light[0],
// eye				data->ray->direction,
// t_material_d	data->scene->object[0]->material,
// normal			vector_normalize_double(hitposition)

// double	light_dot()

double	*difuse_color(double l_dot, t_material_d *material, t_light_d *light)
{
	const	double	*color = vector_multipli(material->color, light->intensity);
	double			*difuse_color;

	difuse_color = vector_multipli_scalar(l_dot, \
					vector_multipli_scalar(material->diffuse, color));
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

double	*slighting(double *position, t_light_d *light, double *eye, t_material_d *material)
{
	double	*ambientColor = vector_multipli_scalar(material->ambient, material->color);
	double	*specularcolor;
	double	*normal = vector_normalize_double(position);
	double	*difusecolor;

	double	lDOtn = l_dot(light->posi, normal, position);
	if (lDOtn <= 0.0)
	{
		difusecolor = vector_zero();
		specularcolor = vector_zero();
	}
	else
	{
		difusecolor = difuse_color(lDOtn, material, light);
		double	rDote = r_dot(light, normal, eye);
		if (rDote <= 0.0)
			specularcolor = vector_zero();
		else
		{
			//Shinniness ou Brilho e depois do rDote
			double	factor = pow(rDote, 200.0);
			specularcolor = vector_multipli_scalar(material->specular * factor, light->intensity);
		}
	}
	return vector_addition(vector_addition(ambientColor, difusecolor), specularcolor);
}
