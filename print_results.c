/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_results.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:06:50 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/04/18 17:13:00 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			*first_step(int paths, t_lemin *lem)
{
	int		i;
	t_list	*path;
	int		*len_of_path;

	int k;
	k = 0;
	i = -1;
	len_of_path = (int*)malloc(sizeof(int) * paths);//+1
	path = lem->saved;
	while (path)
	{
		len_of_path[k++] = lem->len_way[(path)->content_size];
		path = path->next;
	}
	return (len_of_path);
}

char		*get_room(t_lemin *lem, int y, int x)
{
	int		l;
	t_list	*sav2;
	t_lemin	*le4;
	t_list	**search;
	char	*temp;

	l = 0;
	sav2 = lem->saved;
	//le4 = (t_lemin *)malloc(sizeof(t_lemin ) * lem->num_ants);//carefully
	search = (t_list **)malloc(sizeof(t_list *) * lem->num_ants);
	while (y > 0)
	{
		sav2 = sav2->next;
		y--;
	}
	search[l] = (t_list *)sav2->content;
	l = 0;
	while (x > 0)
	{
		search[l] = search[l]->next;
		x--;
	}
	le4 = (t_lemin *)(search[l]->content);
	temp = le4->name;
	//ft_lstdel(search, NULL);
	free(search);
	//delete_everything(le4);
	return (temp);
}

void	print_paths(t_list *sav, t_ways *ways, t_lemin *lem, int *len_of_path)
{
	int l;
	int p;
	t_lemin *le3;
	t_list **pr_pt;
	static int num = 1;

	l = 0;
	//le3 = (t_lemin *)malloc(sizeof(t_lemin ) * lem->num_ants);
	pr_pt = (t_list **)malloc(sizeof(t_list *) * lem->num_ants);//cchanged
	while(l < ft_lstlen(sav))
	{
		ft_printf("{magenta}\npath[%d] - (%d): \n", num++, len_of_path[l] + 1);
		pr_pt[l] = (t_list *)sav->content;
		p = 0;
		while(len_of_path[l] > p++)
		{
			le3 = (t_lemin *)(pr_pt[l]->content);
			ft_printf("{green}%s-->", le3->name);
			pr_pt[l] = pr_pt[l]->next;
			if (pr_pt[l] == NULL)
				ft_printf("%s\n", ways->end->name);
		}
		l++;
		sav = sav->next;
	}
	free(pr_pt); //segfoult
	//free(le3);
	//ft_lstdel(pr_pt, NULL);
}

void	print_results(t_lemin *lem, t_ways *ways)
{
	int	sum_paths;
	int	paths;
	int *len_of_path;
	t_list *sav;
	
	sav = lem->saved;
	len_of_path = 0;
	sum_paths = 0;
	paths = ft_lstlen(lem->saved);
	
	len_of_path = first_step(paths, lem);
	if (lem->req <= 50)
		print_paths(sav, ways, lem, len_of_path);
	ft_printf("{n}");
	print_ants(lem, ways, paths, len_of_path);
	free(len_of_path);//only in small map
}
