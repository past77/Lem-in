/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_for_algo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:05:50 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/14 16:05:51 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	check_way(t_list **way, t_lemin *dot)
{
	if (dot->from != NULL)
	{
		ft_lstadd(way, ft_lstnew_link(dot, 1));
		check_way(way, dot->from);
	}
}

int			same_ways(void *lst_content, void *content)
{
	t_list	*way;
	t_list	*way1;

	way = (t_list *)(lst_content);
	way1 = (t_list *)(content);
	while (way1 && way && way->content == way1->content)
	{
		way = way->next;
		way1 = way1->next;
	}
	if (!way && !way1)
		return (1);
	else
		return (0);
	return (0);
}

void		ft_lstiter4(t_lemin *lem, t_lemin *param1,
				t_lemin *param2, void (*f)(t_lemin *, t_lemin *, t_lemin *))
{
	t_list *temp;

	if (!f)
		return ;
	temp = lem->room;
	while (lem->room)
	{
		f(lem, param1, param2);
		lem->room = lem->room->next;
	}
	lem->room = temp;
}

t_list		*ft_lst_reverse(t_list *head)
{
	t_list	*current;
	t_list	*new;
	t_list	*prev;

	if (!head || !(head->next))
		return (head);
	prev = NULL;
	current = head;
	while (current != NULL)
	{
		new = current;
		current = current->next;
		new->next = prev;
		prev = new;
	}
	return (new);
}

void		find_paths(t_lemin *end_dot, int similar, t_lemin *lem)
{
	t_list	*way;
	t_list	*placenode;
	int		len;
	int		i;

	i = 0;
	if (!end_dot)
		return ;
	placenode = end_dot->near;
	while (placenode != NULL)
	{
		way = NULL;
		check_way(&way, (t_lemin *)placenode->content);
		if (similar)
			way = ft_lst_reverse(way);
		len = ft_lstlen(way);
		if (way != NULL && ft_lstfind(lem->all_ways, way, same_ways) == NULL)
		{
			lem->a_len++;
			ft_lstadd(&lem->all_ways, ft_lstnew_link(way, len));
		}
		else
			ft_lstdel(&way, NULL);
		placenode = placenode->next;
	}
}
