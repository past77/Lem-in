/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_for_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:50:18 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/14 15:50:20 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		clear_split(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int			ft_onesymbol(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
		if (i >= 2)
			return (1);
	}
	return (0);
}

int			ft_lenspc(char *str, char c)
{
	int		n;

	n = 0;
	while (str && *str)
	{
		n += (*str == c);
		str++;
	}
	return (n);
}

void		ft_lstadd2(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	*alst = new;
}

t_list		*ft_lstfind(t_list *head, void *content,
						int (*way_cmp)(void *, void *))
{
	if (!way_cmp)
		return (NULL);
	while (head && !way_cmp(head->content, content))
		head = head->next;
	return (head);
}
