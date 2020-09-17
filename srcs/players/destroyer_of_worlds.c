/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer_of_worlds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 16:13:35 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/17 18:08:24 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

#define MAP(game) game->map->area

#define NORTH 1
// #define NORTHE 2
#define EAST 2
// #define SOUTHE 4
#define SOUTH 3
// #define SOUTHW 6
#define WEST 4
// #define NORTHW 8


int		to_index(t_point p, int w)
{
	return ((p.x * w) + p.y);
}

t_point	index_to_coords(int index, t_grid *map) {
	t_point point;

	point.x = index / map->y;
	point.y = index % map->y;
	return (point);
}



int		check_coord(t_point p, t_grid *map)
{
	if (p.x < 0 ||
		p.y < 0 ||
		p.x >= map->x ||
		p.y >= map->y)
		return (0);
	return (1);
}

t_point compass(int direction, t_point p)
{
	if (direction == NORTH)
		return ((t_point){p.x + 1, p.y});
	// if (direction == NORTHE)
	// 	return ((t_point){p.x + 1, p.y + 1});
	if (direction == EAST)
		return ((t_point){p.x, p.y + 1});
	// if (direction == SOUTHE)
	// 	return ((t_point){p.x - 1, p.y + 1});
	if (direction == SOUTH)
		return ((t_point){p.x - 1, p.y});
	// if (direction == SOUTHW)
	// 	return ((t_point){p.x - 1, p.y - 1});
	if (direction == WEST)
		return ((t_point){p.x, p.y - 1});
	// if (direction == NORTHW)
	// 	return ((t_point){p.x + 1, p.y - 1});
	return (p);
}

int		check_around(t_point p, int *heatmap, double heat, t_grid *map)
{
	int		i;
	t_point r;

	i = WEST + 1;
	while (--i)
	{
		r = compass(i, p);
		if (check_coord(r, map) &&
			heatmap[to_index(r, map->y)] > (int)heat)
			return (1);
	}
	return (0);
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
		if ((int)heat > heatmap[i] &&
			check_around(index_to_coords(i, game->map), heatmap, heat, game->map))
				heatmap[i] = heat;
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
		heatmap[ptr++ - MAP(game)] = 15000;
	heat = 10000;
	i = -1;
	while (++i < (game->map->x + game->map->y) && (heat /= 1.1))
		set_heat(game, heatmap, heat);
	return (heatmap);
}

int		get_value(int *heatmap, t_point point, t_data *game)
{
	char	*ptr;
	t_point	p;
	int		value;

	value = 0;
	ptr = game->piece->area;
	// ft_log("%s\n", ptr);
	while ((ptr = ft_strchr(ptr, '*')))
	{
		p = index_to_coords(ptr - game->piece->area, game->piece);
		p.x += point.x;
		p.y += point.y;
		// ft_log("index: %d\n", index);
		value += heatmap[to_index(p, game->map->y)];
		ptr++;
	}
	// ft_log("value: %d\n", value);
	return (value);
}

t_point *most_valuable_point(t_data *game, int *heatmap)
{
	t_point *result;
	t_list	*coords;
	t_list	*p;
	int		value;
	int		max;

	result = NULL;
	coords = available_coordinates(game);
	max = 0;
	while (coords->next)
	{
		p = coords->next->content;
		while (p)
		{
			value = get_value(heatmap, *POINT(p), game);
			if (value > max)
			{
				max = value;
				result = POINT(p);
			}
			p = p->next;
		}
		coords = coords->next;
	}
	return (result);
}

t_point	*best_option(t_data *game)
{
	int		*heatmap;
	t_point *result;

	heatmap = create_heatmap(game);
	result = most_valuable_point(game, heatmap);
	// int		i;
	// int		x;
	// i = 0;
	// while (i < game->map->x * game->map->y)
	// {
	// 	x = 0;
	// 	while (x < game->map->y && i < game->map->x * game->map->y)
	// 	{
	// 		ft_log("%d\t", heatmap[i]);
	// 		x++;
	// 		i++;
	// 	}
	// 	ft_log("\n");
	// }
	// ft_log("\n\n");
	// free(heatmap);
	// heatmap = NULL;
	return (result);
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
	int		n;

	result = NULL;
	coords = available_coordinates(game);
	enemy_coords = opponent_coords(game);
	result = best_option(game);
	n = write_coords(result);
	ft_lstdel(&coords, ft_del_lstcontent);
	ft_lstdel(&enemy_coords, ft_del_lstcontent);
	return (n);
}
