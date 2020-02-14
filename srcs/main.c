/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:07:50 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/14 16:32:58 by npimenof         ###   ########.fr       */
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

t_data		*init_filler_data(void)
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	data->player = NULL;
	data->opponent = NULL;
	data->map = NULL;
	data->piece = NULL;
	return (data);
}

t_player	*init_player(int p_num)
{
	t_player	*player;

	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->num = p_num;
	player->points = 0;
	return (player);
}

t_grid		*init_grid(int x, int y)
{
	t_grid	*grid;
	char	*area;
	if (!(grid = malloc(sizeof(t_grid))))
		return (NULL);
	if (!(area = malloc(sizeof(x * y))))
		return (NULL);
	grid->x = x;
	grid->y = y;
	grid->area = area;
	return (grid);
}

t_data		*setup_game_env(void)
{
	char	*line;
	t_data	*data;

	data = init_filler_data();
	while (ft_get_next_line(1, &line) > 0)
	{
		if (ft_strstr(line, "$$$ exec"))
		{
			
		}
		ft_strdel(&line);
	}
	return (data);
}

int		main(void)
{
	int		index;
	char	*line;
	t_data	*data;

	data = setup_game_env();
	while (ft_get_next_line(1, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;

	}
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
