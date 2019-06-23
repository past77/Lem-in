/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_alg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 18:44:04 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/03/23 18:44:05 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		bfs_step(t_list_2d **head_lst, t_list_2d **prior_lst, t_lemin *end)
{
	t_lemin *busy;
	t_list	*t_node;
	t_lemin *lem_node;
	int		nd;

	nd = 0;
	busy = (t_lemin *)lst_busy_prior(head_lst, prior_lst);
	t_node = busy->near;
	while (t_node != NULL)
	{
		lem_node = (t_lemin *)(t_node->content);
		if (lem_node->visited == 0 && busy != end)
		{
			nd = lem_node != end;
			lem_node->visited = nd;
			busy->visited++;
			lem_node->from = busy;
			lst2d_stepmodif(head_lst, prior_lst, lst2d_nlink(lem_node));
		}
		t_node = t_node->next;
	}
}

void		alone_way(t_lemin *start1, t_lemin *end)
{
	int	ant;

	ant = 0;
	while (++ant <= start1->num_ants)
		ft_printf("{cyan}L%d-%s ", ant, end->name);
	ft_printf("\n");
}

static void	clean_detect(t_lemin *lem, t_lemin *param1, t_lemin *param2)
{
	t_lemin		*node;

	param2 = NULL;
	node = (t_lemin *)(lem->room)->content;
	node->from = NULL;
	if (lem->min_way <= 2)
		node->visited = (node->visited == 100000000) ? node->visited : 0;
	else if (node != param1 && node->visited >= lem->min_way)
	{
		node->find++;
		node->visited = INT_MAX * (node->find >= 2);
		lem->min_way = lem->min_way * (node->find <= 2);
	}
	else
		node->visited = 0;
}

void		start_b(t_lemin *start, t_lemin *end, t_lemin *lem, t_ways *ways)
{
	t_list_2d *head_lst;
	t_list_2d *prior_lst;

	lem->min_way = 0;
	head_lst = NULL;
	prior_lst = NULL;
	lst2d_step(&head_lst, &prior_lst, lst2d_nlink(start));
	while (head_lst != NULL)
		bfs_step(&head_lst, &prior_lst, end);
	find_paths(end, start != ways->start, lem);
	ft_lstiter4(lem, ways->start, ways->end, clean_detect);
}

void		start_bfc(t_lemin *start, t_lemin *end, t_lemin *lem, t_ways *ways)
{
	t_list_2d *head_lst;
	t_list_2d *prior_lst;

	lem->min_way = 0;
	head_lst = NULL;
	prior_lst = NULL;
	lst2d_step(&head_lst, &prior_lst, lst2d_nlink(start));
	while (head_lst != NULL)
		bfs_step(&head_lst, &prior_lst, end);
	find_paths(end, start != ways->start, lem);
	ft_lstiter4(lem, ways->start, ways->end, clean_detect);
	if (lem->a_len == 0)
	{
		if (one_path1(ways->end, ways->start))
		{
			alone_way(ways->start, ways->end);
			exit(-1);
		}
		else
			errors('e', lem);
	}
}
