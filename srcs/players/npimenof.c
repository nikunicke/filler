/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npimenof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:46:06 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/19 16:28:58 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

// void	available_coords(t_grid *grid)
// {
// 	int		i;

// 	i = 0;
// 	while (grid->area[i])
// 	{
		 
// 	}
// }

int		test_piece(t_grid *map, t_grid *piece)
{
	static int	k;
	int		i;
	int		j;
	int		hits;
	char	*copy;

	hits = 0;
	i = 0;
	printf("size: %d\n", map->x * map->y);
	printf("iteration: %d\n", k);
	copy = &map->area[k];
	while (piece->area[i])
	{
		if (piece->area[i] == '*')
			piece->area[i] = 'X';
		i++;
	}
	i = 0;
	while (i < piece->x)
	{
		j = 0;
		while (j < piece->y && (j + (map->y * i)) + k < (map->x * map->y))
		{
			if (copy[j + (map->y * i)] == 'X' && piece->area[j + (piece->y * i)] == 'X')
				hits++;
			printf("%c", copy[j + (map->y * i)]);
			j++;
		}
		printf("\n");
		i++;
	}
	k += 1;
	printf("hits: %d\n\n\n", hits);
	return (hits);
}

int		available_coordinates(t_grid *map, t_grid *piece)
{
	int		i;
	int		index_list;

	i = 0;
	while (map->area[i])
	{
		test_piece(map, piece);
		i++;
	}
	printf("ITERATIONS: %d\n", i);
	return (1);
}

int		npimenof(t_data *game)
{
	int		i;
	int		j;

	i = ft_strcspn(game->map->area, "oO");
	j = ft_strcspn(game->map->area, "xX");
	available_coordinates(game->map, game->piece);
	printf("OPPONENT COORDS\nx: %d\ny: %d\n", i / game->map->y, i % game->map->y);
	printf("PLAYER   COORDS\nx: %d\ny: %d\n", j / game->map->y, j % game->map->y);
	return (0);
}
