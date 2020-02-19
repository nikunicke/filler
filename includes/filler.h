/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:37:49 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/19 10:59:46 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# define FILLER_H
# define PLAYER npimenof

int				fd;

typedef struct	s_player 
{
	int			id;
	int			points;
	int			(*algorithm)();
}				t_player;

typedef struct	s_grid
{
	int			x;
	int			y;
	char		*area;
}				t_grid;

typedef struct	s_data
{
	t_player	*player;
	t_player	*opponent; 
	t_grid		*map;
	t_grid		*piece;
}				t_data;

t_player		*new_player(void);
t_grid			*new_grid(char *identifier);
t_data			*new_game(t_player *(*new_player)(), t_grid *(*new_grid)());

void			update_area(t_grid *map);

int				npimenof(t_data *game);

#endif