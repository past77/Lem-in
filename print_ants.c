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

void			kill_all_the_ants(t_ant *a)
{
	t_ant		*c;
	t_ant		*n;

	c = a;
	while (c)
	{
		n = c->next;
		free(c);
		c = n;
	}
}

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

void			print_ants(t_lemin *lem, t_ways *ways, int sum_paths, int *ln)
{
	t_ant		*ant;
	static int	total = 1;
	static int	total2 = 0;
	t_ant		*ant2;
	int *ln2;
	ln2 = ln;
	int dif;

	total = 0;
	ant = make_list(lem);
	ant2 = make_list(lem);
	ft_putchar('\n');
	lem->started = lem->num_ants;
	while (lem->finish < lem->num_ants)
	{
		if (total2)
			move_along_super(lem, ant2, ln2);
		if (lem->started > 0)
			first_move_super(lem, ant2, sum_paths, ln2);
		total2++;
	}
	lem->finish = 0;
	lem->started = lem->num_ants;
	dif = total2 - lem->req;
	while (lem->finish < lem->num_ants)
	{
		if (total)
			move_along(lem, ant, ln, ways);
		if (lem->started > 0)
			first_move(lem, ant, sum_paths, ln);
		if((total > total2/2 - dif/2) && (total < total2/2 + dif/2))
		{
		if (total)
			move_along_super(lem, ant, ln);
		if (lem->started > 0)
			first_move_super(lem, ant, sum_paths, ln);
		}
		write(1, "\n", 1);
		total++;
	}
	kill_all_the_ants(ant);
	kill_all_the_ants(ant2);
ft_printf("{n}\n");
	ft_printf("{magenta}TOTAL LEN OF PATHS : %d\n", total);
}
