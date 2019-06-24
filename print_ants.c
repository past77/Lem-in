/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 16:14:19 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/11 16:14:20 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_ant	*new_ant(void)
{
	t_ant		*new;
	static int	num = 0;

	new = (t_ant *)malloc(sizeof(t_ant));
	new->ant = ++num;
	new->y = -1;
	new->x = 0;
	new->next = NULL;
	return (new);
}

int				norm_way(t_lemin *lem, int y, int *len_of_path)
{
	int			y1;
	uintmax_t	moves;

	if (y == 0)
		return (1);
	y1 = y - 1;
	moves = 0;
	while (y1 >= 0)
	{
		moves += len_of_path[y] - len_of_path[y1];
		y1--;
	}
	if ((uintmax_t)lem->started >= moves)
		return (1);
	else
		return (0);
}

t_ant			*make_list(t_lemin *lem)
{
	t_ant		*ant;
	t_ant		*cur;
	int			num;

	ant = new_ant();
	cur = ant;
	num = 0;
	while (num < lem->num_ants)
	{
		cur->next = new_ant();
		cur = cur->next;
		num++;
	}
	return (ant);
}

void			clean_print(t_ant *ant, int total)
{
	kill_ants(ant);
	ft_printf("{n}\n");
	ft_printf("{magenta}TOTAL LEN OF PATHS : %d\n", total);
	ft_printf("{n}\n");
}

void			print_ants(t_lemin *lem, t_ways *ways, int sum_paths, int *ln)
{
	t_ant		*ant;
	static int	total = 0;
	int			t;
	int			dif;

	ant = make_list(lem);
	t = super_func(ln, lem, sum_paths);
	dif = t - lem->req;
	while (lem->finish < lem->num_ants)
	{
		if (total)
			move_along(lem, ant, ln, ways);
		if (lem->started > 0)
			first_move(lem, ant, sum_paths, ln);
		if (lem->req > 50 && (total > t / 2 - dif / 2) && (total < t / 2 + dif / 2))
		{
			if (total)
				move_along_super(lem, ant, ln);
			if (lem->started > 0)
				first_move_super(lem, ant, sum_paths, ln);
		}
		write(1, "\n", 1);
		total++;
	}
	clean_print(ant, total);
}
