/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_transform.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:36:01 by algabrie          #+#    #+#             */
/*   Updated: 2022/08/01 01:23:26 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_coo	*get_forward(t_coo *to, t_coo *from);

double	**view_transform(t_coo *from, t_coo *to, t_coo *up)
{
	t_coo		*forward;
	t_coo		*up_normal;
	t_coo		*left;
	t_coo		*true_up;
	double		**orientation;

	forward = get_forward(to, from);
	up_normal = vector_normalize(up);
	left = vector_cross(forward, up_normal);
	true_up = vector_cross(left, forward);
	orientation = calculate_orientation(left, true_up, forward, from);
	free((t_coo *)up_normal);
	free((t_coo *)left);
	free((t_coo *)true_up);
	free((t_coo *)forward);
	return (orientation);
}

static t_coo	*get_forward(t_coo *to, t_coo *from)
{
	const t_coo	*temp = vector_subtraction(to, from);
	const t_coo	*forward = vector_normalize((t_coo *)temp);

	free((t_coo *)temp);
	return ((t_coo *)forward);
}
