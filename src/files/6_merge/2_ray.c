/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:07:06 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/18 01:22:28 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*position(t_ray_re *ray, double t)
{
	double	*aux = vector_multipli_scalar(t, ray->direction);
	double	*position = vector_addition(ray->origin, aux);
	free(aux);
	return (position);
}

t_ray_re	*ray_to_object_space(t_ray_re *ray, double **local)
{
	t_ray_re	*res;
	double	**inverse;
	double	**aux;

	res = (t_ray_re *)malloc(sizeof(t_ray_re));
	aux = (double **)malloc(sizeof(double *));

	inverse = matrix_inverter(local, matrix_determinant(local));
	aux[0] = ray->direction;
	aux = matrix_multiply(aux, inverse, 1);
	res->direction = aux[0];
	aux[0] = ray->origin;
	aux = matrix_multiply(aux, inverse, 1);
	res->origin = aux[0];
	return (res);
}

double	*slighting(double *position, t_light_re *light, double *eye, t_material_re *material, double *normal)
{
	double	*temp = material->color;
	double	*effectivecolor = vector_multipli(temp, light->intensity);
	double	*lightvec = vector_normalize(vector_subtraction(light->posi, position));
	double	*ambienteColor = vector_multipli_scalar(material->ambient, temp);
	double	*difusecolor;
	double	*specularcolor;

	double	lDOtn = vector_abs(lightvec, normal);
	if (lDOtn <= 0.0)
	{
		difusecolor = make_point(0.0, 0.0, 0.0);
		specularcolor = make_point(0.0, 0.0, 0.0);
	}
	else
	{
		difusecolor = vector_multipli_scalar(lDOtn, vector_multipli_scalar(material->diffuse, effectivecolor));
		double	*refle = reflect(vector_multipli_scalar(-1.0, lightvec), normal);
		double	rDote = vector_abs(refle, eye);
		if (rDote <= 0.0)
			specularcolor = make_point(0.0, 0.0, 0.0);
		else
		{
			//Shinniness ou Brilho e depois do rDote
			double	factor = pow(rDote, 200.0);
			specularcolor = vector_multipli_scalar(material->specular * factor, light->intensity);
		}
	}
	return vector_addition(vector_addition(ambienteColor, difusecolor), specularcolor);
}
