# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 16:58:57 by ppolozhe          #+#    #+#              #
#    Updated: 2019/03/07 17:39:58 by ppolozhe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
LIBFT = libft/
LIB = libft/includes/
CFLAGS  = -Wall -Wextra -Werror
CC = @gcc -g
LEM_H = lem_in.h

SRC = main.c start_alg.c lists.c middle_algo.c end_algo.c print_results.c \
print_ants.c err_and_clear.c parser.c func_for_parse.c parse_for_ways.c \
lists_for_algo.c lists2.c sort_list.c print_ants2.c others.c

OBJ = $(SRC:.c=.o)

LIBA = $(addprefix $(LIBFT), libft.a)

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(LIBA) $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -I $(LEM_H) $(LIBA) -o $(NAME)
	@echo "\x1B[35m\0 compiled\x1B[0m\0"

%.o: %.c $(LEM_H)
	$(CC) $(CFLAGS) -c -I $(LIB) $< -o $@

$(LIBA):
		@make -sC $(LIBFT)
clean:
		@make clean -C $(LIBFT)
		@rm -f $(OBJ)

fclean: clean
		@make fclean -C $(LIBFT)
		@rm -f $(NAME)

re: fclean all
