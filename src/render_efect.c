/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_efect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:26:05 by algabrie          #+#    #+#             */
/*   Updated: 2022/04/28 20:17:58 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_coo	*reflect(t_coo *v, t_coo *n)
{
	t_coo	*var;
	t_coo	*res;

	var = vector_multipli_scalar(2.0*vector_abs(v,n),n);
	res = vector_subtration(v, var);
	free(var);
	return(res);
}

t_ray	*scatter(t_ray *ray, t_scene *rec, t_ray *scattered)
{
	t_coo	*reflected;

	reflected = reflect(vector_normalize(ray->direction), rec->normal);
	scattered = (t_ray *)malloc(sizeof(t_ray));
	scattered->origin = rec->p;
	scattered->direction = reflected;
	if (vector_abs(scattered->direction, rec->normal) > 0)
		return (scattered);
	return(NULL);
}