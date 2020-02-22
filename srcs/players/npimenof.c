/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npimenof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:46:06 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/22 19:17:28 by npimenof         ###   ########.fr       */
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
	return (offset);
}

t_list	*coordinates(char *map_index, char *piece_index, t_data *game)
{
	int			offset;
	int			crd;
	int			map_i;
	char		*copy;
	t_list		*item;

	item = ft_lstnew(NULL, 0);
	// printf("Item addr: %p\n", &item);

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
			game->map->area[crd + offset] != '.')
			return (item);
		piece_index++;
	}
	printf("Piece fits at %d %d\n", crd / game->map->y, crd % game->map->y);
	item->content = &crd;
	item->content_size = sizeof(int);
	return (item);
}

int		available_coordinates(t_data *game)
{
	char	*map_index;
	char	*piece_index;
	t_list	*head;
	t_list	*tmp;
	int		i;

	i = 0;
	head = ft_lstnew(NULL, sizeof(t_list));
	// printf("%p\n", &head);
	tmp = head;
	map_index = game->map->area;
	piece_index = ft_strchr(game->piece->area, '*');
	while ((map_index = ft_strchr(map_index, 'X')))
	{
		head->next = ft_lstnew((void *)coordinates(map_index, piece_index, game), sizeof(t_list));
		// printf("Head->content [ element: %d, addr: %p ]\n", i, &head->content);
		map_index++;
		head = head->next;
		i++;
		printf("\n");
	}
	head = tmp;
	// printf("\n%p\n", &head);
	// printf("\n%p\n", &tmp);
	printf("\n\n\n");
	i = 0;
	t_list	*item;
	int		a;
	while (head)
	{
		// printf ("%p\n", &head->content);
		printf("Head->content [ element: %d, addr: %p ]\n", i, &head->content);
		item = (t_list *)head->content;
		// if (((t_list *)&head->content)->content != NULL)
		// {
		// 	printf("%d\n\n", *(int *)((t_list *)&head->content)->content);
		// }
		while (item)
		{
			if (item->content == NULL)
			{
				item = item->next;
				continue;
			}
			a = *((int *)item->content);
			printf("%d, ", a);
			item = item->next;
		}
		printf("\n\n");
		i++;
		head = head->next;
	}
	return (0);
}

int		npimenof(t_data *game)
{
	// int		i;
	// int		j;

	// i = ft_strcspn(game->map->area, "oO");
	// j = ft_strcspn(game->map->area, "xX");
	available_coordinates(game);
	
	return (0);
}
