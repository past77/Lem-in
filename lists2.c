/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:35 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/14 16:14:36 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_lstlen(t_list *head)
{
	int		i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

t_list		*ft_lstcopy(t_list *lst)
{
	t_list	*head;

	head = NULL;
	while (lst)
	{
		ft_lstadd(&head, ft_lstnew_link(lst->content, lst->content_size));
		lst = lst->next;
	}
	return (head);
}

void		lst2d_stepmodif(t_list_2d **head, t_list_2d **prior, t_list_2d *new)
{
	if (!new || !head || !prior)
		return ;
	new->next = *head;
	new->prior = NULL;
	if (*head)
		(*head)->prior = new;
	*head = new;
	if (!*prior)
		*prior = new;
}

void		ft_lstiter12(t_list *lst, void *param, void (*f)(t_list *, void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst, param);
		lst = lst->next;
	}
}

void		ft_lstiter3(t_list *lst, t_lemin *lem,
						void (*f)(t_list *, t_lemin *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst, lem);
		lst = lst->next;
	}
}
