/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer_of_worlds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 16:13:35 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/15 14:52:23 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

#define MAP(game) game->map->area
#define N(point) point.x - 1, point.y
#define NE(point) point.x - 1, point.y + 1
#define E(point) point.x, point.y + 1
#define SE(point) point.x + 1, point.y + 1
#define S(point) point.x + 1, point.y
#define SW(point) point.x + 1, point.y - 1
#define W(point) point.x, point.y - 1
#define NW(point) point.x - 1, point.y - 1

int		to_index(int x, int y, int w)
{
	// ft_log("to_index: %d\n", x * y + y);
	return ((x * w) + y);
}

t_point	index_to_coords(int index, t_data *game) {
	t_point point;

	point.x = index / game->map->y;
	point.y = index % game->map->y;
	return (point);
}

int		check_coord(int x, int y, t_data *game)
{
	if (x < 0 ||
		y < 0 ||
		x >= game->map->x ||
		y >= game->map->y)
		return (0);
	return (1);
}

void	check_around(t_point p, int *heatmap, double heat, t_data *game)
{
	// ft_log("heat: %lf\n", heat);
	if (check_coord(N(p), game) && heatmap[to_index(N(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
	if (check_coord(NE(p), game) && heatmap[to_index(NE(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
	if (check_coord(E(p), game) && heatmap[to_index(E(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
	if (check_coord(SE(p), game) && heatmap[to_index(SE(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
	if (check_coord(S(p), game) && heatmap[to_index(S(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
	if (check_coord(SW(p), game) && heatmap[to_index(SW(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
	if (check_coord(W(p), game) && heatmap[to_index(W(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
	if (check_coord(NW(p), game) && heatmap[to_index(NW(p), game->map->y)] > (int)heat)
		heatmap[to_index(p.x, p.y, game->map->y)] = (int)heat;
}

void	set_heat(t_data *game, int *heatmap, double heat) {
	int		i;
	int		max_x;
	int		max_y;

	max_x = game->map->x;
	max_y = game->map->y;
	i = -1;
	while (++i < (max_y * max_x))
	{
		// heatmap[i] = check_around(index_to_coords(i, game), heatmap, heat, game) ? (int)heat : heatmap[i];
		if ((int)heat > heatmap[i])
		{
			check_around(index_to_coords(i, game), heatmap, heat, game);
				// heatmap[i] = (int)heat;
		}
	}
}

int		*create_heatmap(t_data *game)
{
	int		i;
	int		size;
	double	heat;
	int		*heatmap;
	char	*ptr;

	size = game->map->x * game->map->y;
	if (!(heatmap = malloc(sizeof(int) * size)))
		return (NULL);
	ft_bzero(heatmap, size);
	ptr = game->map->area;
	while ((ptr = ft_strchr(ptr, game->opponent->mark)))
	{
		// ft_log("asd: %d\n", ptr - MAP(game));
		heatmap[ptr++ - MAP(game)] = 15000;
	}
	heat = 10000;
	i = -1;
	while (++i < (game->map->x + game->map->y) && (heat /= 1.1))
		set_heat(game, heatmap, heat);
	return (heatmap);
}

t_point	*best_option(t_data *game)
{
	int		*heatmap;
	int		x;
	int		i;

	heatmap = create_heatmap(game);
	i = 0;
	while (i < game->map->x * game->map->y)
	{
		x = 0;
		while (x++ < game->map->y && i < game->map->x * game->map->y)
			ft_log("%d\t", heatmap[i++]);
		ft_log("\n");
	}
	return (NULL);
}

int		write_coords(t_point *point)
{
	if (point)
	{
		ft_putnbr_fd(point->x, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(point->y, 1);
		ft_putchar_fd('\n', 1);
		free(point);
		point = NULL;
	}
	else
	{
		write(1, "0 0\n", 4);
		return (0);
	}
	return (1);
}

int		destroyer_of_worlds(t_data *game)
{
	t_list	*coords;
	t_list	*enemy_coords;
	t_point *result;

	result = NULL;
	coords = available_coordinates(game);
	enemy_coords = opponent_coords(game);
	result = best_option(game);
	// ft_lstdel(&coords, ft_del_lstcontent);
	// ft_lstdel(&enemy_coords, ft_del_lstcontent);
	return (write_coords(result));
}
