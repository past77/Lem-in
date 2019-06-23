/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_and_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 17:13:35 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/12 17:13:37 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		errors(char c, t_lemin *lem)
{
	if (c == 'm')
		ft_printf("{red}%s\n", "ERROR, maps" );
	else if (c == 'a')
		ft_printf("{red}%s\n", "ERROR, ants" );
	else if (c == 'i')
		ft_printf("{red}%s\n", "ERROR, incorrect input" );
	else if(c == 'l')
		ft_printf("{red}%s\n", "ERROR, link" );
	else if (c == 's')
		ft_printf("{red}%s\n", "ERROR, same" );
	else if (c == 'r')
		ft_printf("{red}%s\n", "ERROR, rooms" );
	else if (c =='n')
		ft_printf("{red}%s\n", "ERROR, numbers" );
	else if (c == 'c')
		ft_printf("{red}%s\n", "ERROR, comments!" );
	else if (c == 'e')
		ft_printf("{red}%s\n", "ERROR, end" );
	else if (c == 'p')
		ft_printf("{red}%s\n", "ERROR" );
	delete_everything(lem);
	system("leaks lem-in");
	exit (-1);
}
void		ft_required(t_lemin *lem)
{
	char *str;

	str = ft_strsub(lem->ants, 39, 3);
	lem->req = ft_atoi(str);
	free(str);
}

void		lem_del_node(void *el, size_t len)
{
	t_lemin		*elem;
	int			len1;

	len1 = len;
	elem = (t_lemin *)el;
	if (elem)
	{
		free(elem->name);
		ft_lstdel(&elem->near, NULL);
		free(elem);
	}
}

void	delete_everything(t_lemin *lem)
{
	t_list	*list;

	ft_lstdel(&lem->room, lem_del_node);
	ft_lstdel(&lem->all_ways, NULL);
	ft_lstdel(&lem->room, NULL);
	free(lem->ants);
	 list = lem->lst_input;
	while (list) 
	{
		//free(list->content);
		lem->lst_input = list->next;
		free(list);
		list = lem->lst_input;
	}
}

void	ft_lstdelone2(t_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !*alst)
		return ;
	if (del)
		del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}

void	ft_lstdel2(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*old;

	if (!alst)
		return ;
	while (*alst)
	{
		old = ((*alst)->next);
		ft_lstdelone2(alst, del);
		*alst = old;
	}
	*alst = NULL;
}


