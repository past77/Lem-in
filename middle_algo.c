/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:39:38 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/04/05 15:39:40 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		clear_cross(t_list *pa, t_list *pb)
{
	t_list		*p_node;
	int			flag;
	int			p;

	flag = 0;
	p_node = pb;
	while (pa && p_node && !flag)
	{
		pb = p_node;
		while (pb && !flag && pa->content != pb->content)
			pb = pb->next;
		p = pb != NULL;
		flag = p;
		pa = pa->next;
	}
	return (flag);
}

static void		find_cross(t_list *cr_path, t_lemin *lem)
{
	t_list		*curr;
	static int	j;

	j = cr_path->content_size;
	curr = (t_list *)cr_path->content;
	cr_path = cr_path->next;
	while (cr_path != NULL)
	{
		if (clear_cross(curr, (t_list *)cr_path->content))
			ft_lstadd(&lem->cros[j],
				ft_lstnew_link((t_list *)cr_path->content,
				cr_path->content_size));
		cr_path = cr_path->next;
	}
}

static void		cmp(t_list *way, t_lemin *lem)
{
	static int	i;

	lem->len_way[i] = way->content_size;
	lem->len_visit[i] = 2;
	way->content_size = i;
	i++;
}

void			middle_al_bfc(t_lemin *lem)
{
	lem->all_ways = sort_list(lem->all_ways, croissant);
	lem->cros = (t_list **)ft_memalloc(sizeof(t_list *) * lem->a_len);
	lem->len_way = (int *)malloc(sizeof(int) * lem->a_len);
	lem->len_visit = (char *)malloc(sizeof(char) * lem->a_len);
	ft_lstiter3(lem->all_ways, lem, cmp);
	ft_lstiter3(lem->all_ways, lem, find_cross);
	end_algo(lem);
}
