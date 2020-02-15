/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:07:50 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/15 19:44:08 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "filler.h"
#include "get_next_line.h"
#include "libft.h"

// FUNC FOR STRUCT
int			player_num(void)
{
	char		*line;
	static int	num = 0; // not norminettable --> solution: check if num is explicitly one or two and return accordingli....
	int			i;

	if (num)
		return (num == 1 ? 2 : 1);
	i = 0;
	while (ft_get_next_line(1, &line) > 0 && i++ < 2)
	{
		if (ft_strstr(line, "$$$ exec p"))
		{
			num = ft_atoi(&line[ft_strcspn(line, "12")]);
			ft_strdel(&line);
			return (num);
		}
		ft_strdel(&line);
	}
	return (0);
}

int			board_size(void)
{
	char	*line;
	int		i;

	i = 0;
	while (ft_get_next_line(1, &line) > 0 && i++ < 10)
	{
		if (ft_strstr(line, "Plateau"))
		{
			i = ft_strcspn(line, "0123456789");
			i = ft_atoi(&line[i]) * ft_atoi(&line[i + ft_strspn(&line[i], "0123456789")]);
			ft_strdel(&line);
			return (i);
		}
		ft_strdel(&line);
	}
	return (0);
}

t_data		*new_game(t_player *(*new_player)(), t_grid *(*new_grid)())
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	data->player = new_player();
	data->opponent = new_player();
	data->map = new_grid();
	data->piece = NULL;
	return (data);
}

t_player	*new_player(void)
{
	t_player	*player;
	int			p_num;

	p_num = player_num();
	if (p_num != 1 && p_num != 2)
		return (NULL);
	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->num = p_num;
	player->points = 0;
	return (player);
}

t_grid		*new_grid(void)
{
	t_grid	*grid;
	char	*area;
	int		size;

	size = board_size();
	if (!(grid = malloc(sizeof(t_grid))))
		return (NULL);
	if (!(area = malloc(sizeof(size))))
		return (NULL);
	grid->x = 0;
	grid->y = 0;
	grid->area = ft_memset(area, '.', size);
	return (grid);
}



// NORMAL FUNC
// void		*get_players(t_data **data)
// {
// 	char	*line;
// 	int		i;

// 	i = 0;
// 	while (ft_get_next_line(1, &line) > 0 && i++ < 10)
// 	{
// 		if (ft_strstr(line, "$$$ exec p"))
// 		{
// 			(*data)->player = new_player(ft_atoi(&line[ft_strcspn(line, "12")]));
// 			ft_strdel(&line);
// 			break;
// 		}
// 		ft_strdel(&line);
// 	}
// 	if ((*data)->player == NULL)
// 		exit (1);
// 	(*data)->opponent = new_player((*data)->player->num == 1 ? 2 : 1);
// }

t_data		*setup_game_env(void)
{
	char	*line;
	t_data	*game;

	game = new_game(new_player, new_grid);
	// get_players(&data);
	return (game);
}

int		main(void)
{
	int		index;
	char	*line;
	t_data	*data;

	data = setup_game_env();
	printf("PLAYER: %d\n", data->player->num);
	printf("OPPENE: %d\n", data->opponent->num);
	printf("MAP: %s\n", data->map->area);
	// while (ft_get_next_line(1, &line) > 0)
	// {
	// 	printf("%s\n", line);
	// 	free(line);
	// 	line = NULL;

	// }
	// char	*line;
	// char	*dim;
	// int		index;
	// // int		buf_size;

	// dim = NULL;
	// while (ft_get_next_line(1, &line) > 0)
	// {
	// 	if (ft_strstr(line, "Plateau") || ft_strstr(line, "Piece"))
	// 	{
	// 		index = ft_strcspn(line, "0123456789");
	// 		dim = ft_strsub(line, index, ft_strcspn(line + index, ":"));
	// 		printf("Dimensions: %s\n", dim);
	// 	}
	// 	free(dim);
	// 	free(line);
	// 	dim = NULL;
	// 	line = NULL; // Consider fixin ft_del_args for this. Addresses not being set to NULL in this scope
	// }
	// system("leaks a.out");
	return (0);
}
