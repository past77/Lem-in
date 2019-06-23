/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 17:47:23 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/03/23 17:47:24 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			lst2d_step(t_list_2d **head, t_list_2d **prior, t_list_2d *new)
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

void			lstiter_lem(t_list *lst, void *param, t_lemin *lem,
								void (*f)(t_list *, void *, t_lemin *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst, param, lem);
		lst = lst->next;
	}
}

void			ft_lstiter2_my(t_list *lst, t_lemin *lem,
							void *param, void (*f)(t_lemin *, t_list *, void *))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lem, lst, param);
		lst = lst->next;
	}
}

t_list_2d		*lst2d_nlink(void *content)
{
	t_list_2d	*new_list;

	if (!(new_list = (t_list_2d *)malloc(sizeof(t_list_2d))))
		return (NULL);
	new_list->prior = NULL;
	new_list->next = NULL;
	new_list->content = content;
	return (new_list);
}

void			*lst_busy_prior(t_list_2d **head, t_list_2d **prior)
{
	t_list_2d	*prev;
	void		*content;

	if (!prior || !head || !*head)
		return (NULL);
	if (*prior == *head)
		*head = NULL;
	content = (*prior)->content;
	prev = (*prior)->prior;
	free(*prior);
	*prior = prev;
	if (*prior)
		(*prior)->next = NULL;
	return (content);
}
