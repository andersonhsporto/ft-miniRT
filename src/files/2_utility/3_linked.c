/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_linked.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 03:02:52 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/23 01:30:06 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_element	*element_new(int type, int id, void *element)
{
	t_element	*list;

	list = malloc(sizeof(t_element));
	if (list)
	{
		list->type = type;
		list->id = id;
		list->ptr = element;
		list->next = (0);
		return (list);
	}
	return (0);
}

t_element	*get_last_node(t_element *lst)
{
	if (lst)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (0);
}

void	element_add_back(t_element **lst, t_element *new)
{
	t_element	*last_node;

	if (*lst)
	{
		last_node = get_last_node(*lst);
		last_node->next = new;
	}
	else
	{
		*lst = new;
	}
}
