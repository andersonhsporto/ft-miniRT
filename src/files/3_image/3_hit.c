/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_hit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 22:50:44 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/08 23:39:52 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_sphere(t_mini *data, t_sphere *ptr);

int hit_element(t_mini *data, t_element *node)
{
	int	i;

	i = 0;
	if (node->type == sphere)
	{
		i = hit_sphere(data, (t_sphere *)node->ptr);
	}

	return (i);
}

int	hit(t_mini *data)
{
	t_element	*tmp;
	int 		i;


	tmp = data->element;
	i = 0;
	while (tmp != NULL)
	{
		if (hit_element(data, tmp))
		{
			printf("hit element\n");
			i = 1;
		}
		tmp = tmp->next;
	}
	return (i);
}