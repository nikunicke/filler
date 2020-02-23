/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npimenof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:46:06 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/23 18:04:39 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

int		calculate_offset(char *piece_index, t_data *game)
{
	int		offset;
	int		piece_i;
	int		piece_y;

	piece_y = game->piece->y;
	piece_i = piece_index - game->piece->area;
	offset = game->map->y * (piece_i / piece_y) + (piece_i % piece_y);
	// printf("offset: %d\n", offset);
	return (offset);
}

int		check_row(int crd, int offset, t_data *game)
{
	int		map_row;
	int		limit;

	map_row = (crd + offset) / game->map->y;
	limit = (crd / game->map->y) + (game->piece->x - 1);
	if (map_row > limit)
		return (1);
	return (0);
}

t_list	*coordinates(char *map_index, char *piece_index, t_data *game)
{
	int			offset;
	int			crd;
	int			map_i;
	char		*copy;
	t_list		*item;

	item = ft_lstnew(NULL, 0);
	if ((copy = ft_strchr(piece_index + 1, '*')))
		item->next = coordinates(map_index, copy, game);
	map_i = map_index - game->map->area;
	crd = map_i - calculate_offset(piece_index, game);
	piece_index = game->piece->area;
	while ((piece_index = ft_strchr(piece_index, '*')))
	{
		offset = calculate_offset(piece_index, game);
		if (crd + offset == map_i && piece_index++)
			continue ;
		if (crd + offset < 0 || crd + offset > (game->map->x * game->map->y) ||
			game->map->area[crd + offset] != '.' || check_row(crd, offset, game))
			return (item);
		piece_index++;
	}
	printf("Piece fits at %d %d\n", crd / game->map->y, crd % game->map->y);
	item->content = malloc(sizeof(int));
	ft_memcpy(item->content, &crd, sizeof(int));
	item->content_size = sizeof(int);
	return (item);
}

t_list	*available_coordinates(t_data *game)
{
	char	*map_index;
	char	*piece_index;
	t_list	*head;
	t_list	*tmp;
	int		i;

	i = 0;
	head = ft_lstnew(NULL, sizeof(t_list));
	tmp = head;
	map_index = game->map->area;
	piece_index = ft_strchr(game->piece->area, '*');
	while ((map_index = ft_strchr(map_index, 'X')))
	{
		head->next = ft_lstnew((void *)coordinates(map_index, piece_index, game), sizeof(t_list));
		map_index++;
		head = head->next;
		i++;
	}
	head = tmp;
	return (head);
}

void	traverse_linked_linked_list(t_list *head)
{
	t_list	*item;
	int		a;
	
	while (head)
	{
		item = (t_list *)head->content;
		while (item)
		{
			if (item->content == NULL)
			{
				item = item->next;
				continue;
			}
			a = *((int *)item->content);
			printf("%d ", a);
			item = item->next;
		}
		printf("\n");
		head = head->next;
	}
}

int		npimenof(t_data *game)
{
	t_list	*coordinates;

	coordinates = available_coordinates(game); // remember to free this shit
	traverse_linked_linked_list(coordinates);
	return (0);
}
