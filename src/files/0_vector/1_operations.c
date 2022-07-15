/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_operations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 23:58:47 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/15 20:32:01 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vector_scale(t_vector v, double k)
{
	t_vector	v_scaled;

	v_scaled.x = v.x * k;
	v_scaled.y = v.y * k;
	v_scaled.z = v.z * k;
	return (v_scaled);
}
