# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/18 11:47:57 by npimenof          #+#    #+#              #
#    Updated: 2020/02/25 11:44:46 by npimenof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = npimenof.filler

FLAGS = -Wall -Werror -Wextra

SRCS = srcs/main.c

UTILS = srcs/utilities/player.c\
		srcs/utilities/game.c\
		srcs/utilities/grid.c\
		srcs/utilities/point.c

PLAYER = srcs/players/npimenof.c

LOGGER = srcs/logging/logger.c

OBJS = main.o\
		player.o\
		game.o\
		grid.o\
		npimenof.o\

LIBFT = ./libft
LIBFTINCL = ./libft/includes

INCL = ./includes

all: $(NAME)

$(NAME): $(SRCS) $(UTILS) $(PLAYER) $(LOGGER)
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME) $(SRCS) $(UTILS) $(PLAYER) $(LOGGER) -L$(LIBFT) -lft -I$(LIBFTINCL) -I$(INCL)

clean:
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all
