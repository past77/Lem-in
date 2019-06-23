/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 19:23:33 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/04/27 13:52:42 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			helper(t_lemin *lem)
{
	static int	key;
	char		**split;
	char		**split2;

	if ((!ft_strncmp(lem->ants, "#Here is the number of lines required: ", 22)))
		ft_required(lem);
	ft_printf("%s\n", lem->ants);
	split = ft_strsplit(lem->ants, ' ');
	split2 = ft_strsplit(lem->ants, '-');
	if (ft_atoi(lem->ants) != 0 && !split[1] && !split2[1])
	{
		key++;
		if (key > 1)
		{
			errors('a', lem);
		}
	}
	clear_split(split);
	clear_split(split2);
}

int				helper2(int len, char **sigh, t_lemin *lem)
{
	static int	ers;
	static int	ere;

	if (len == 0)
		return (0);
	if ((!ft_strcmp(*sigh, "##start")))
	{
		if (++ers >= 2)
			errors('i', lem);
	}
	if ((!ft_strcmp(*sigh, "##end")))
	{
		if (++ere >= 2)
			errors('i', lem);
	}
	if (!**sigh || **sigh == '\0')
		errors('i', lem);
	return (1);
}

int				find_comments(t_lemin *lem, char **s)
{
	int			len;

	*s = NULL;
	len = get_next_line(0, s);
	while (len > 0 && *s && (*s)[0] == '#' && lem->ants == 0)
	{
		if (len > 0 && (*s)[0] == '#' && (!ft_strcmp(*s, "##start")
			|| !ft_strcmp(*s, "##end")) && lem->ants == NULL)
			errors('c', lem);
		ft_printf("%s\n", *s);
		len = get_next_line(0, s);
	}
	lem->ants = *s;
	if (lem->ants != NULL)
		helper(lem);
	helper2(len, s, lem);
	while (len > 0 && *s && (((*s)[0] == '#' && (*s)[1] != '#') ||
		((*s)[0] == '#' && (*s)[1] == '#' &&
		ft_strcmp(*s, "##start") && ft_strcmp(*s, "##end"))))
	{
		ft_lstadd(&lem->lst_input, ft_lstnew_link(*s, 8));
		*s = NULL;
		len = get_next_line(0, s);
	}
	return (len > 0);
}

t_lis			*read_data(t_lemin *lem, t_lis *lst, t_ways *ways)
{
	char		*sigh;

	sigh = NULL;
	find_comments(lem, &sigh);
	if (lem->ants == NULL || ft_new_isalpha(lem->ants, lem))
		errors('m', lem);
	lem->num_ants = ft_atoi(lem->ants);
	if (!lem->num_ants)
		errors('a', lem);
	ft_lstadd2(&lem->lst_input, ft_lstnew_link(sigh, 1));
	if (lem->num_ants < 0)
		errors('a', lem);
	free(sigh);
	while (find_comments(lem, &sigh) > 0)
	{
		ft_lstadd(&lem->lst_input, ft_lstnew_link(sigh, 1));
		if (sigh[0] == '\0' || sigh[0] == 'L')
			errors('i', lem);
		if (sigh[0] == '#' && sigh[1] == '#')
			pars_start_to_end(sigh, ways, lem);
		parse_link(sigh, lem, ways);
		parse_room(sigh, lem);
		free(sigh);
	}
	return (lst);
}

int				main(void)
{
	t_lemin		*lem;
	t_ways		ways;
	t_lis		*lst;

	lst = NULL;
	lem = ft_memalloc(sizeof(t_lemin));
	init_lem(lem, &ways);
	read_data(lem, lst, &ways);
	if (ways.end == NULL || ways.start == NULL)
		errors('l', lem);
	ways.start->num_ants = lem->num_ants;
	start_bfc(ways.start, ways.end, lem, &ways);
	start_b(ways.end, ways.start, lem, &ways);
	middle_al_bfc(lem);
	print_results(lem, &ways);
	del_rooms(lem);
	//free(lem->cros);
	//delete_everything(lem);
	system("leaks lem-in");
	return (0);
}
