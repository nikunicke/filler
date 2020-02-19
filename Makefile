# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 11:47:57 by npimenof          #+#    #+#              #
#    Updated: 2020/02/18 12:19:18 by npimenof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = npimenof.filler

FLAGS = -Wall -Werror -Wextra

SRCS = srcs/main.c

UTILS = srcs/utilities/player.c\
		srcs/utilities/game.c\
		srcs/utilities/grid.c\

PLAYER = srcs/players/npimenof.c

OBJS = main.o\
		player.o\
		game.o\
		grid.o\
		npimenof.o\

LIBFT = ./libft
LIBFTINCL = ./libft/includes

INCL = ./includes

all: $(NAME)

$(NAME): $(SRCS) $(UTILS) $(PLAYER)
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME) $(SRCS) $(UTILS) $(PLAYER) -L$(LIBFT) -lft -I$(LIBFTINCL) -I$(INCL)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make flcean $(LIBFT)

re: fclean all
