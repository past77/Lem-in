/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:45:58 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/14 15:46:00 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void				init_lem(t_lemin *lem, t_ways *ways)
{
	lem->finish = 0;
	lem->alone = 0;
	lem->started = 0;
	lem->len_way = 0;
	lem->num_ants = 0;
	lem->errors = 0;
	lem->ants = NULL;
	ways->start = NULL;
	ways->end = NULL;
	ways->len_path = 0;
}

int					ft_new_isalpha(char *str, t_lemin *lem)
{
	int				i;

	i = 0;
	if (!str)
		errors('r', lem);
	while (str[i] != '\0')
	{
		if ((str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

t_list				*ft_lstnew_link(void *content, size_t content_size)
{
	t_list			*newlst;

	if (content == NULL)
		return (NULL);
	newlst = (t_list *)malloc(sizeof(t_list));
	if (newlst == NULL)
		return (NULL);
	newlst->next = NULL;
	newlst->content = content;
	newlst->content_size = content_size;
	return (newlst);
}

static t_lemin		*new_elem(char *name)
{
	t_lemin	*lem_n;

	if (!name)
		return (NULL);
	if (!(lem_n = (t_lemin *)malloc(sizeof(t_lemin))))
		return (NULL);
	lem_n->name = ft_strdup(name);
	if (lem_n->name == NULL)
	{
		free(lem_n);
		return (NULL);
	}
	lem_n->find = 0;
	lem_n->visited = 0;
	lem_n->near = NULL;
	lem_n->from = NULL;
	return (lem_n);
}

int					parse_room(char *input, t_lemin *lem)
{
	char			**split;
	int				x;
	int				y;

	if (ft_lenspc(input, ' ') != 2)
		return (0);
	split = ft_strsplit(input, ' ');
	if (ft_new_isalpha(split[2], lem))
		errors('p', lem);
	x = ft_atoi(split[1]);
	y = ft_atoi(split[2]);
	if (x == -25678 || x == 25678 || y == -25678 || y == 25678)
		errors('n', lem);
	ft_lstadd(&lem->room, ft_lstnew_link(new_elem(split[0]), 8));
	clear_split(split);
	return (1);
}
