/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_char_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 21:36:36 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/05/19 21:48:32 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	slice(char *str);
static double	dot_divide(int nbr);

double	str_to_double(char *str)
{
	double	number;
	double	sign;
	int		index;

	number = 0;
	sign = 1;
	index = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index++] == '-')
			sign = -1;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		number = number * 10 + (str[index] - '0');
		index++;
	}
	if (str[index] == '.')
	{
		index++;
		number += slice(&str[index]);
	}
	return (sign * number);
}

static double	slice(char *str)
{
	int		i;
	double	ret;

	i = 0;
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret *= 10;
		ret += str[i] - '0';
		i++;
	}
	ret *= dot_divide(i);
	return (ret);
}

static double	dot_divide(int nbr)
{
	int		index;
	double	result;

	result = 1;
	index = 0;
	while (index < nbr)
	{
		result /= 10;
		index++;
	}
	return (result);
}