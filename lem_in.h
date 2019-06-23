/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:51:30 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/03/13 15:52:07 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LEM_IN
# define LEM_IN
# include <unistd.h>
# include <stdlib.h> 
# include <stdio.h>
# include "libft/includes/libft.h"
# include "libft/includes/get_next_line.h"
# include "libft/ft_printf/ft_printf.h"


typedef struct			s_lemin
{
	int					a_len;
	int					finish;
	int					started;
	char				*name;
	int					x;
	int					y;
	t_list				*all_ways;
	int					alone;
	t_list				*near;
	int					visited;
	int					find;
	int					num_ants;
	int					errors;
	struct s_lemin		*from;
	char				*ants;
	t_list				**cros;
	int					len_path;
	int					*len_way;
	char				*len_visit;
	t_list				*saved;
	t_list				*lst_input;
	t_list				*room;
	int					min_way;
	char				*fin;
	int					req;
}						t_lemin;

typedef struct		s_list2
{
	char			*content;
	size_t			content_size;
	struct s_list2	*next;
	struct s_list2	*prev;
}					t_list2;


typedef struct			s_ways
{
	t_lemin				*start;
	t_lemin				*end;
	int					len_path;
}						t_ways;

typedef struct			t_lis
{
	t_list				*input;
}						t_lis;

typedef struct			s_list_2d
{
	struct s_list_2d	*prior;
	struct s_list_2d	*next;
	void				*content;
	size_t				content_size;
}						t_list_2d;

typedef struct			s_ant
{
	int					ant;
	int					y;
	int					x;
	struct s_ant		*next;
}						t_ant;

void		ft_required(t_lemin *lem);
void 		del_rooms(t_lemin *lem);
void 		del_input(t_lemin *lem);
void	ft_lstdel2(t_list **alst, void (*del)(void *, size_t));
void					delete_everything(t_lemin *lem);
void					ft_lstiterLem(t_list *lst, void *param, t_lemin *lem, void (*f)(t_list *, void *, t_lemin *));
void					ft_lstiter12(t_list *lst, void *param, void (*f)(t_list *, void *));
int						ft_lstlen(t_list *head);
t_list					*ft_sort_lst(t_list *lst, int (*cmp)(t_list *, t_list *));
void					ft_swap_lst(t_list *t1, t_list *t2);
t_list					*ft_lstnew_link(void *content, size_t content_size);
void					*lst_busy_prior(t_list_2d **head, t_list_2d **prior);
t_list_2d				*lst2d_nlink(void *content);
void					lst2d_step(t_list_2d **head, t_list_2d **prior, t_list_2d *new);
t_list					*ft_lstnew_link(void *content, size_t content_size);
t_list					*ft_lstfind(t_list *head, void *content, int (*way_cmp)(void *, void *));
int						way_cmp(void *g1, void *line);
void					errors(char c, t_lemin *lem);
void					end_algo(t_lemin *lem);
void					resolve(t_list **curr, t_list *all_paths, t_lemin *lem);


int						ft_new_isalpha(char *str, t_lemin *lem);
int						parse_room(char *input, t_lemin *lem);
void					clear_split(char **str);
int						ft_onesymbol(char *str);
int						ft_lenspc(char *str, char c);
void					ft_lstadd2(t_list **alst, t_list *new);
t_list					*ft_lstfind(t_list *head, void *content, int (*way_cmp)(void *, void *));
void					parse_ways(char *name1, char *name2, t_lemin *lem);
void					parse_link(char *input, t_lemin *lem, t_ways *ways);
void					pars_start_to_end(char *sigh, t_ways *ways, t_lemin *lem);
void					init_lem(t_lemin *lem, t_ways *ways);
int						find_comments(t_lemin *lem, char **s);
int						one_path1(t_lemin *end, t_lemin *start);
t_list					*ft_lst_reverse(t_list *head);
void					ft_lstiter4(t_lemin *lem, t_lemin *param1, t_lemin *param2, void (*f)(t_lemin *, t_lemin *, t_lemin *));
void					lstiter_lem(t_list *lst, void *param, t_lemin *lem,
								 void (*f)(t_list *, void *, t_lemin *));
void					find_paths(t_lemin *end_dot, int similar, t_lemin *lem);
void					alone_way(t_lemin *start1, t_lemin *end);
void					ft_lstiter3(t_list *lst, t_lemin *lem, void (*f)(t_list *, t_lemin *));
t_list					*sort_list(t_list *lst, int (*cmp_ways)(t_list *, t_list *));
int						croissant(t_list *way1, t_list *way2);
void					first_move(t_lemin *lem, t_ant *ant, int sum_paths, int *len_of_path);
void					first_move_super(t_lemin *lem, t_ant *ant, int sum_paths, int *len_of_path);
void					print_move(t_lemin *lem, t_ant *ant, char c);
void					move_along(t_lemin *lem, t_ant *ant, int *len_of_path, t_ways *ways);
void					move_along_super(t_lemin *lem, t_ant *ant, int *len_of_path);
int						norm_way(t_lemin *lem, int y, int *len_of_path);
void					try_first_move(t_lemin *lem, t_ant **ant, int *moved, int *y);

void					lst2d_stepmodif(t_list_2d **head, t_list_2d **prior, t_list_2d *new);

char					*get_room(t_lemin *lem, int y, int x);
void					print_ants(t_lemin *lem,t_ways *ways, int sum_paths, int *len_of_path);

t_list					*ft_lstcopy(t_list *lst);
void					middle_al_bfc();
void					ft_lstiter2_my(t_list *lst, t_lemin *lem, void *param, void (*f)(t_lemin *, t_list *, void *));
void					ft_lstiter2(t_list *lst, void *param, void (*f)(t_list *, void *));
void					start_bfc(t_lemin *start, t_lemin *end, t_lemin *lem, t_ways *ways);
void					start_b(t_lemin *start, t_lemin *end, t_lemin *lem, t_ways *ways);
void					print_results(t_lemin *lem, t_ways *ways);

#endif
