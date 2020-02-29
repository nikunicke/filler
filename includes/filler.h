/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:37:49 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/29 18:58:40 by npimenof         ###   ########.fr       */
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

int fde; // remember this

typedef struct	s_player 
{
	int			id;
	char		mark;
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

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

t_player		*new_player(void);
t_grid			*new_grid(char *identifier);
t_data			*new_game(t_player *(*new_player)(), t_grid *(*new_grid)());

t_point			*new_point(int x, int y);
t_point			set_point(int x, int y);
t_point			point_add(t_point *sum, t_point *point);
int				point_index(t_point point, t_grid *map);
int				point_distance(t_point *a, t_point *b);

void			update_area(t_grid **map);

int				npimenof(t_data *game);
t_list			*available_coordinates(t_data *game);
void			get_opponent_coordinates(t_list **head, t_data *game);

int				ft_log(char *msg, ...);
#endif