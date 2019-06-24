/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 20:14:08 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/06/23 20:14:10 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		ft_memdel((void **)&arr);
	}
}

void		ft_required(t_lemin *lem)
{
	char *str;

	str = ft_strsub(lem->ants, 39, 3);
	lem->req = ft_atoi(str);
	free(str);
}

void		del_rooms(t_lemin *lem)
{
	t_list	*del;

	while (lem->room)
	{
		del = lem->room;
		lem->room = lem->room->next;
		free(del);
	}
}

void		try_first_move_super(t_lemin *lem, t_ant **a2, int *m, int *y)
{
	int		*moved2;

	moved2 = m;
	(*a2)->y = *y;
	(*a2)->x++;
	(*moved2)++;
	lem->started--;
	(*a2) = (*a2)->next;
}

void		first_move_super(t_lemin *lem, t_ant *ant2, int sp, int *ln)
{
	int		y;
	int		moved2;

	while (ant2->next && (ant2->y == -2 || ant2->y > -1))
		ant2 = ant2->next;
	moved2 = 0;
	y = 0;
	while (y < sp && moved2 < sp && ant2 && lem->num_ants)
	{
		if (norm_way(lem, y, ln))
			try_first_move_super(lem, &ant2, &moved2, &y);
		y++;
	}
}
