/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_1_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:04:59 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/02 00:35:39 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersec	*cylinder_intersec(t_ray *base_ray, void *ptr)
{
	const t_cylinder_d	*cyd = (t_cylinder_d *)ptr;
	t_cy_intersec		cy_data;

	cy_data.ray = ray_to_object_space(base_ray, cyd->transform);
	cy_data.a = pow(cy_data.ray.direction.x, 2) + \
	pow(cy_data.ray.direction.z, 2);
	cy_data.b = (2 * cy_data.ray.origin.x * cy_data.ray.direction.x) + \
		(2 * cy_data.ray.origin.z * cy_data.ray.direction.z);
	cy_data.c = (pow(cy_data.ray.origin.x, 2) + \
	pow(cy_data.ray.origin.z, 2)) - 1.0;
	cy_data.disc = pow(cy_data.b, 2) - (4 * cy_data.a * cy_data.c);
	cy_data.vals[0] = cy_data.a;
	cy_data.vals[1] = cy_data.b;
	cy_data.vals[2] = cy_data.disc;
	return (create_intersec(cy_data.vals, &cy_data.ray, (t_cylinder_d *)cyd));
}
