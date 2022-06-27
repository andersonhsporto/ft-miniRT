/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_ray.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 12:03:35 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/26 21:55:05 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*ray_to_object_space(t_ray *ray, double **local)
{
	t_ray	*res;
	double	**inverse;
	double	**aux;

	res = (t_ray *)malloc(sizeof(t_ray));
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

double	*reflect(double *v, double *n)
{
	const double	*temp = vector_multipli_scalar(2.0 * vector_abs(v, n), n);
	double			*res;

	res = vector_subtraction(v, (double *)temp);
	free((double *)temp);
	return(res);
}

t_hit	*hit_point(t_intersec *intersections, double *color)
{
	t_hit	*first;

	if (intersections)
	{
		first = (t_hit *)malloc(sizeof(t_hit));
		first->color = color;
		if ((intersections->cont == 2 || intersections->cont == 3) && !(intersections->t1 < 0.0))
		{
			first->t = intersections->t1;
			return (first);
		}
		if ((intersections->cont == 1 || intersections->cont == 3) && !(intersections->t2 < 0.0))
		{
			first->t = intersections->t2;
			return (first);
		}
	}
	return (NULL);
}
