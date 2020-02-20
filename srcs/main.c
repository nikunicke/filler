/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:07:50 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/20 14:23:22 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_data		*setup_game(void)
{
	t_data	*game_env;

	if (!(game_env = new_game(new_player, new_grid)))
		return (NULL);
	return (game_env);
}

int			game_loop(t_data *game, int (*algorithm)())
{	
	game->player->algorithm = algorithm;
	while (1)
	{
		if(!(game->piece = new_grid("Piece")))
			return (1);
		if (!(game->player->algorithm(game)))
			return (0);
		update_area(game->map);
		ft_strdel(&game->piece->area);
		free(game->piece);
	}
	return (0);
}

int			main(void)
{
	t_data	*data;

	// fd = open("filler.log", O_RDWR);
	if (!(data = setup_game()))
		return (1);
	if (game_loop(data, PLAYER))
		return (1);
	// system("leaks npimenof.filler");
	// close(fd);
	return (0);
}
