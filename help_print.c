/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:32:01 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/06/24 13:32:03 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				super_func(int *ln, t_lemin *lem, int sum_paths)
{
	static int	total2 = 0;
	t_ant		*ant2;
	int			*ln2;

	ln2 = ln;
	ant2 = make_list(lem);
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
	kill_ants(ant2);
	return (total2);
}

void			kill_ants(t_ant *a)
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

void			dublic_room(t_lemin *lem)
{
	t_list		*lst;
	int			i;

	i = 0;
	while(lem->r)
	{
		lst = lem->r;
		while(lst)
		{
			if (!ft_strcmp(lst->content, lem->r->content))
			{
				i++;
				if (i == 2)
					errors('d', lem);
			}
			lst = lst->next;
		}
		i = 0;
		lem->r = lem->r->next;
	}
 }
