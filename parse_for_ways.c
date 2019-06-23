/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_for_ways.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 15:53:58 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/14 15:53:59 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			one_path1(t_lemin *end, t_lemin *start)
{
	t_list	*lst;
	int		alone;
	t_lemin	*node;

	lst = start->near;
	alone = 0;
	while (!alone && lst)
	{
		node = (t_lemin *)lst->content;
		alone = ft_strcmp(node->name, end->name) == 0;
		lst = lst->next;
	}
	return (alone);
}

int			way_cmp(void *cmp, void *line)
{
	if (cmp == NULL || line == NULL)
		return (0);
	return (!ft_strcmp(((t_lemin *)cmp)->name, (char *)line));
}

void		parse_ways(char *name1, char *name2, t_lemin *lem)
{
	t_list	*room1;
	t_list	*room2;

	room1 = ft_lstfind(lem->room, name1, way_cmp);
	room2 = ft_lstfind(lem->room, name2, way_cmp);
	if (!room1 || !room2)
		errors('r', lem);
	ft_lstadd(&(((t_lemin *)room1->content)->near),
		ft_lstnew_link((t_lemin *)room2->content, 8));
	ft_lstadd(&(((t_lemin *)room2->content)->near),
		ft_lstnew_link((t_lemin *)room1->content, 8));
}

void		parse_link(char *input, t_lemin *lem, t_ways *ways)
{
	char	**split;

	if (ft_lenspc(input, '-') != 1)
		return ;
	split = ft_strsplit(input, '-');
	if (split[0] == NULL || split[1] == NULL)
		errors('l', lem);
	if (ft_strcmp(split[0], split[1]) == 0)
		errors('s', lem);
	if ((split[0] && split[1]) && (!ways->start || !ways->end))
		errors('i', lem);
	parse_ways(split[0], split[1], lem);
	clear_split(split);
}

void		pars_start_to_end(char *sigh, t_ways *ways, t_lemin *lem)
{
	char	*line;

	if (ft_strcmp(sigh, "##start") && ft_strcmp(sigh, "##end"))
		return ;
	find_comments(lem, &line);
	ft_lstadd(&lem->lst_input, ft_lstnew_link(line, 1));
	if (parse_room(line, lem) == 1)
	{
		ways->start = (!ft_strcmp(sigh, "##start")) ?
						lem->room->content : ways->start;
		ways->end = (!ft_strcmp(sigh, "##end")) ?
						lem->room->content : ways->end;
	}
	else
		errors('i', lem);
	free(line);
}
