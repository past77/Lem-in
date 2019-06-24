/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:24:42 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/05/14 16:24:43 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_move(t_lemin *lem, t_ant *ant, char c)
{
	char	*name_t;

	name_t = get_room(lem, ant->y, ant->x - 1);
	if (c == 's')
		ft_printf("{cyan}L%ld-%s{-} ", ant->ant, name_t);
	else if (c == 'm')
		ft_printf("{yellow}L%ld-%s{-} ", ant->ant, name_t);
	else if (c == 'f')
		ft_printf("{yellow}L%ld-%s{-} ", ant->ant, name_t);
}

void		first_move(t_lemin *lem, t_ant *ant, int sp, int *ln)
{
	int		y;
	int		moved;

	while (ant->next && (ant->y == -2 || ant->y > -1))
		ant = ant->next;
	moved = 0;
	y = 0;
	while (y < sp && moved < sp && ant && lem->num_ants)
	{
		if (norm_way(lem, y, ln))
			try_first_move(lem, &ant, &moved, &y);
		y++;
	}
}

void		try_first_move(t_lemin *lem, t_ant **ant, int *moved, int *y)
{
	(*ant)->y = *y;
	(*ant)->x++;
	print_move(lem, (*ant), 's');
	(*moved)++;
	lem->started--;
	(*ant) = (*ant)->next;
}

void		move_along(t_lemin *lem, t_ant *ant, int *ln, t_ways *ways)
{
	while (ant)
	{
		if (ant->y >= 0)
		{
			ant->x++;
			if (ln[ant->y] == ant->x)
				print_move(lem, ant, 'f');
			else if (ant->x > ln[ant->y])
			{
				ft_printf("{blue}L%ld-%s ", ant->ant, ways->end->name);
				ant->y = -2;
				lem->finish++;
			}
			else
				print_move(lem, ant, 'm');
		}
		ant = ant->next;
	}
}

void		move_along_super(t_lemin *lem, t_ant *ant2, int *ln2)
{
	while (ant2)
	{
		if (ant2->y >= 0)
		{
			ant2->x++;
			if (ant2->x > ln2[ant2->y])
			{
				ant2->y = -2;
				lem->finish++;
			}
		}
		ant2 = ant2->next;
	}
}
