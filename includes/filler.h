/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:37:49 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/18 15:12:45 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define PLAYER destroyer_of_worlds
# define POINT(list) ((t_point *)list->content)
# define EMBEDDED(list) ((t_list *)list->content)

# include "libft.h"
# include "get_next_line.h"

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
t_point			i_to_point(int index, t_grid *map);
int				to_index(t_point p, int w);
int				write_point(t_point *point);

void			update_area(t_grid **map);

int				npimenof(t_data *game);
int				destroyer_of_worlds(t_data *game);
int				*create_heatmap(t_data *game);
t_list			*available_coordinates(t_data *game);
t_list			*opponent_coords(t_data *game);
t_list			*opponent_coords2(t_data *game);

int				ft_log(char *msg, ...);

#endif
