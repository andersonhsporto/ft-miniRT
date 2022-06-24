/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_lth_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:31:52 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/06/24 01:36:27 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*diffuse_specular_zero(t_utils	*utils)
{
	utils->diffuse = vector_zero();
	utils->specular = vector_zero();
	return ;
}
