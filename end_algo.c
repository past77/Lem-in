/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:38:38 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/04/08 17:38:39 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		fill_visit(t_list *list, void *v_value, t_lemin *lem)
{
	int			*value;

	value = (int *)v_value;
	lem->len_visit[(list)->content_size] = *value;
}

void			accept_path(t_list **curr, t_list *new_p, t_lemin *lem)
{
	int			num2;
	int			max;

	max = INT_MAX;
	num2 = 0;
	ft_lstadd(curr, ft_lstnew_link((t_list *)new_p->content,
							new_p->content_size));
	ft_lstdel2(&lem->saved, NULL);
	lem->saved = ft_lstcopy(*curr);
	lstiter_lem(lem->cros[(new_p)->content_size], &num2, lem, fill_visit);
}

void			resolve(t_list **curr, t_list *all_paths, t_lemin *lem)
{
	while (all_paths && !((lem->len_visit)[all_paths->content_size]))
		all_paths = all_paths->next;
	if (!all_paths)
		return ;
	accept_path(curr, all_paths, lem);
	resolve(curr, all_paths->next, lem);
}

void			end_algo(t_lemin *lem)
{
	t_list		*eway;
	int			i;

	eway = NULL;
	resolve(&eway, lem->all_ways, lem);
	ft_lstdel2(&eway, NULL);
	i = -1;
	while (++i < lem->len_path)
		ft_lstdel(&lem->cros[i], NULL);
}
