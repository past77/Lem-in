/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:20:08 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/14 16:20:09 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			croissant(t_list *way1, t_list *way2)
{
	if (!way1 || !way2)
		return (-1);
	if (way1->content_size <= way2->content_size)
		return (1);
	else
		return (0);
}

int			tri(t_list *lst, int (*cmp_ways)(t_list *, t_list *))
{
	while (lst->next != NULL)
	{
		if ((*cmp_ways)(lst, lst->next) == 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_list		*sort_list(t_list *lst, int (*cmp_ways)(t_list *, t_list *))
{
	t_list	*first;
	void	*swap;
	size_t	size;

	swap = 0;
	first = lst;
	while (tri(first, croissant) == 0)
	{
		lst = first;
		while (lst->next != NULL)
		{
			if ((*cmp_ways)(lst, lst->next) == 0)
			{
				swap = lst->content;
				lst->content = lst->next->content;
				lst->next->content = swap;
				size = lst->content_size;
				lst->content_size = lst->next->content_size;
				lst->next->content_size = size;
			}
			lst = lst->next;
		}
	}
	return (first);
}
