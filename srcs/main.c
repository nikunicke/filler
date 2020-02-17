/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:07:50 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/17 17:47:20 by npimenof         ###   ########.fr       */
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
int			get_player_id(void)
{
	static int	num = 0; // not norminettable --> solution: check if num is explicitly one or two and return accordingli....
	char		*line;
	int			i;
	
	if (num)
		return (num == 1 ? 2 : 1);
	i = 0;
	while (ft_get_next_line(0, &line) > 0 && i++ < 2)
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

int			*board_size(void)
{
	int				*xy;
	int				i;
	char			*line;

	if (!(xy = malloc(sizeof(int) * 2)))
		return (NULL);
	i = 0;
	while (ft_get_next_line(0, &line) > 0 && i++ < 10)
	{	
		if (ft_strstr(line, "Plateau"))
		{
			i = ft_strcspn(line, "0123456789");
			xy[0] = ft_atoi(&line[i]);
			xy[1] = ft_atoi(&line[i + ft_strspn(&line[i], "0123456789")]);
			ft_strdel(&line);
			return (xy);
		}
		ft_strdel(&line);
	}
	return (NULL);
}

t_data		*new_game(t_player *(*new_player)(), t_grid *(*new_grid)())
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->player = new_player()))
		return (NULL);
	if (!(data->opponent = new_player()))
		return (NULL);
	if (!(data->map = new_grid()))
		return (NULL);
	data->piece = NULL;
	return (data);
}

t_player	*new_player(void)
{
	t_player	*player;
	int			player_id;

	if (!(player_id = get_player_id()))
		return (NULL);
	if (player_id != 1 && player_id != 2)
		return (NULL);
	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->id = player_id;
	player->points = 0;
	player->algorithm = NULL;
	return (player);
}

t_grid		*new_grid(void)
{
	t_grid		*grid;
	char		*area;
	int			*dimensions;
	int			size;

	if (!(dimensions = board_size()))
		return (NULL);
	size = dimensions[0] * dimensions[1];
	if (!(grid = malloc(sizeof(t_grid))))
		return (NULL);
	if (!(area = ft_strnew(size)))
		return (NULL);
	grid->x = dimensions[0];
	grid->y = dimensions[1];
	grid->area = ft_memset(area, '.', size);
	free(dimensions);
	dimensions = NULL;
	return (grid);
}

t_data		*setup_game_env(void)
{
	t_data	*game_env;

	if (!(game_env = new_game(new_player, new_grid)))
		return (NULL);
	return (game_env);
}

void		update_map(t_grid *map)
{
	char	*line;
	int		i;
	FILE	*fp;

	fp = fopen("filler.log", "w+");
	i = 0;
	while (ft_get_next_line(0, &line) > 0 && i < map->x)
	{
		fprintf(fp, "%s\n", line);
		if (ft_strspn(line, " 	0123456789") > 4)
		{
			ft_strdel(&line);
			continue ;
		}
		ft_strncpy(&map->area[i * (map->y - 1)], &line[ft_strspn(line, " \t0123456789")], 17);
		ft_strdel(&line);
		i++;
	}
	fclose(fp);
}

// void		update_piece(t_grid *piece)
// {
// 	char	*line;

// 	while (ft_get_next_line(0, &line) > 0)
// 	{

// 	}
// 	return ;
// }

int			game_loop(t_data *game_env, void (*algorithm)())
{	
	char *line;

	game_env->player->algorithm = algorithm;
	while (1)
	{
		update_map(game_env->map);
		write(1, "12 14\n", 6);
	}
	// while (1)
	// {
	// 	update_map(game_env->map);
	// 	update_piece(game_env->piece);
	// 	write(1, "12 14\n", 6);
	// }
	// while (1)
	// {
		// update_piece(game_env->piece);
		// game_env->player->algorithm(game_env); // or just game_env?
		// write placement
	// }
	// Set algorithm to player
	// Start game loop
	// Update map - no reallocation is needed
	// Get next piece
	// Call player algorithm
	// Output desired coordinates
	return (0);
}

void		npimenof_dummy(void)
{
	printf("12 14\n");
	return ;
}

int			main(void)
{
	t_data	*data;

	if (!(data = setup_game_env()))
		return (1);
	if ((game_loop(data, PLAYER)))
		return (1);
	// system("leaks a.out");
	return (0);
}
