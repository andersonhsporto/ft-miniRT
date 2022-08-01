/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_start_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algabrie <alefgabrielr@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 22:29:10 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/31 22:43:14 by algabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	legal_char(char character)
{
	if (ft_strchr("0123456789-., \t\n\r", character))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	divide_coo(t_coo *coo, int nbr)
{
	coo->x = coo->x / nbr;
	coo->y = coo->y / nbr;
	coo->z = coo->z / nbr;
}
