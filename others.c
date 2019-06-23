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

void			del_arr(char **arr)
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

void 		del_rooms(t_lemin *lem)
{
	t_list		*del;
	while(lem->room)
	{
		del = lem->room;
		lem->room = lem->room->next;
		free(del);
	}
}

