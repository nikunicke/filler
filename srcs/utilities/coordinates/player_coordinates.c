/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_coordinates.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:30:50 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/29 19:00:35 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		offset(char *piece, t_data *game)
{
	int		offset;
	int		piece_i;
	int		piece_y;

	piece_y = game->piece->y;
	piece_i = piece - game->piece->area;
	offset = game->map->y * (piece_i / piece_y) + (piece_i % piece_y);
	return (offset);
}

static int		put_piece(char *piece, t_point *map, t_point *crd, t_data *game)
{
	t_point		ref;
	t_point		sum;
	int			boffset;

	while ((piece = ft_strchr(piece, '*')))
	{
		boffset = offset(piece, game);
		ref = set_point(boffset / game->map->y, boffset % game->map->y);
		sum = point_add(crd, &ref);
		if (sum.x == map->x &&
			sum.y == map->y && piece++)
			continue;
		if (sum.x < 0 || sum.y < 0 ||
			sum.y > game->map->y - 1 ||
			game->map->area[point_index(sum, game->map)] != '.')
		{
			free(map);
			free(crd);
			map = NULL;
			crd = NULL;
			return (0);
		}
		piece++;
	}
	return (1);
}

static t_point	*offset_point(int map_i, char *piece, t_data *game)
{
	t_point		*point;

	point = new_point(0, 0);
	point->x = (map_i / game->map->y) - (offset(piece, game) / game->map->y);
	point->y = (map_i % game->map->y) - (offset(piece, game) % game->map->y);
	return (point);
}

static t_list	*coordinates(char *map_index, char *piece, t_data *game)
{
	int			map_i;
	t_list		*next_item;
	t_list		*item;
	t_point		*crd;
	t_point		*map_point;

	item = ft_lstnew(NULL, 0);
	if (ft_strchr(piece + 1, '*'))
		item->next = coordinates(map_index, ft_strchr(piece + 1, '*'), game);
	map_i = map_index - game->map->area;
	map_point = new_point(map_i / game->map->y, map_i % game->map->y);
	crd = offset_point(map_i, piece, game);
	piece = game->piece->area;
	if (!put_piece(piece, map_point, crd, game))
	{
		next_item = item->next;
		free(item);
		item = NULL;
		return (next_item);
	}
	item->content = crd;
	item->content_size = sizeof(t_point);
	free(map_point);
	map_point = NULL;
	return (item);
}

t_list			*available_coordinates(t_data *game)
{
	char	*map;
	char	*piece;
	t_list	*head;
	t_list	*tmp;

	head = ft_lstnew(NULL, sizeof(t_list));
	tmp = head;
	map = game->map->area;
	piece = ft_strchr(game->piece->area, '*');
	while ((map = ft_strchr(map, game->player->mark)))
	{
		// head->next = ft_lstnew(coordinates(map, piece, game), sizeof(t_list));
		head->next = ft_lstnew(NULL, 0);
		head->next->content = coordinates(map, piece, game);
		head->next->content_size = sizeof(t_list);
		if (((t_list *)head->next)->content == NULL)
		{
			free(head->next);
			head->next = NULL;
			map++;
			continue ;
		}
		head = head->next;
		map++;
	}
	head = tmp->next;
	free(tmp);
	tmp = NULL;
	return (head);
}
