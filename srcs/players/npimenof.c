/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npimenof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:46:06 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/20 17:04:54 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

int		possible_coordinates(char *map_index, char *piece_index, t_data *game)
{
	int			offset;
	int			crd;
	int			map_i;
	int			piece_i;
	char		*copy;

	if ((copy = ft_strchr(piece_index + 1, '*')))
		possible_coordinates(map_index, copy, game);
	piece_i = piece_index - game->piece->area;
	map_i = map_index - game->map->area;
	crd = map_i - (game->map->y * (piece_i / game->piece->y) + (piece_i % game->piece->y)); // create funktion of this?
	piece_index = game->piece->area;
	while ((piece_index = ft_strchr(piece_index, '*')))
	{
		piece_i = piece_index - game->piece->area;
		offset = game->map->y * (piece_i / game->piece->y) + (piece_i % game->piece->y);
		if (crd + offset == map_i && piece_index++)
			continue ;
		if (crd + offset < 0 || crd + offset > (game->map->x * game->map->y) ||
			game->map->area[crd + offset] != '.')
			return (0);
		piece_index++;
	}
	printf("Piece fits at %d %d\n", crd / game->map->y, crd % game->map->y);
	return (0);
}

int		available_coordinates(t_data *game)
{
	char	*map_index;
	char	*piece_index;

	map_index = game->map->area;
	piece_index = ft_strchr(game->piece->area, '*');
	while ((map_index = ft_strchr(map_index, 'X')))
	{
		possible_coordinates(map_index, piece_index, game);
		map_index++;
	}
	return (0);
}

int		npimenof(t_data *game)
{
	int		i;
	int		j;

	i = ft_strcspn(game->map->area, "oO");
	j = ft_strcspn(game->map->area, "xX");
	available_coordinates(game);
	return (0);
}
