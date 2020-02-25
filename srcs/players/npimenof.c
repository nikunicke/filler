/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npimenof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:46:06 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/25 18:58:41 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

int		offset(char *piece_index, t_data *game)
{
	int		offset;
	int		piece_i;
	int		piece_y;

	piece_y = game->piece->y;
	piece_i = piece_index - game->piece->area;
	offset = game->map->y * (piece_i / piece_y) + (piece_i % piece_y);
	return (offset);
}

int		check_row(int crd, int offset, t_data *game)
{
	int		map_row;
	int		limit_high;
	int		piece_row;
	piece_row = (ft_strrchr(game->piece->area, '*') - game->piece->area) / game->piece->y;
	map_row = (crd + offset) / game->map->y;
	limit_high = (crd / game->map->y) + (piece_row);
	if (map_row > limit_high)
		return (1);
	return (0);
}

t_list	*coordinates(char *map_index, char *piece_index, t_data *game)
{
	int			map_i;
	char		*copy;
	t_list		*item;
	t_point		ref;
	t_point		*crd;
	t_point		*map_point;
	int			boffset;

	item = ft_lstnew(NULL, 0);
	if ((copy = ft_strchr(piece_index + 1, '*')))
		item->next = coordinates(map_index, copy, game);
	map_i = map_index - game->map->area;
	boffset = offset(piece_index, game);
	map_point = new_point(map_i / game->map->y, map_i % game->map->y);
	crd = new_point((map_i / game->map->y) - (offset(piece_index, game) / game->map->y), (map_i % game->map->y) - (offset(piece_index, game) % game->map->y));
	piece_index = game->piece->area;
	while ((piece_index = ft_strchr(piece_index, '*')))
	{
		ref = set_point(offset(piece_index, game) / game->map->y, offset(piece_index, game) % game->map->y);
		if (point_addition(crd, &ref).x == map_point->x && point_addition(crd, &ref).y == map_point->y && piece_index++)
			continue;
		if (point_addition(crd, &ref).x < 0 || point_addition(crd, &ref).y < 0 || point_addition(crd, &ref).y > game->map->y - 1 ||
			game->map->area[point_to_index(point_addition(crd, &ref), game->map)] != '.')
		{
			free(map_point);
			free(crd);
			return (item);
		}
		piece_index++;
	}
	item->content = new_point((map_i / game->map->y) - (boffset / game->map->y), (map_i % game->map->y) - (boffset % game->map->y));
	item->content_size = sizeof(t_point); // make this shit shorter
	free(crd);
	free(map_point);
	return (item);
	// MAKE THIS FUNCTION READABLE ...
}

t_list	*available_coordinates(t_data *game)
{
	char	*map_index;
	char	*piece_index;
	t_list	*head;
	t_list	*tmp;

	head = ft_lstnew(NULL, sizeof(t_list));
	tmp = head;
	map_index = game->map->area;
	piece_index = ft_strchr(game->piece->area, '*');
	while ((map_index = ft_strchr(map_index, 'X')))
	{
		head->next = ft_lstnew((void *)coordinates(map_index, piece_index, game), sizeof(t_list));
		map_index++;
		head = head->next;
	}
	head = tmp;
	return (head);
}

int		traverse_linked_linked_list(t_list *head)
{
	t_list	*item;
	t_point		*a;
	
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
			a = (t_point *)item->content;
			ft_log("%d %d\n", a->x, a->y);
			item = item->next;
		}
		head = head->next;
	}
	return (1);
}

void	ft_lstadd_sorted(t_list **head, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (!(*head) || *(int *)(*head)->content > *(int *)new->content)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		tmp = *head;
		while (tmp->next != NULL && *(int *)tmp->next->content < *(int *)new->content)
			tmp = tmp->next;
		new->next = tmp->next;
		tmp->next = new;
	}
}

void	free_nested_list(void *content, size_t content_size)
{
	t_list	*list;
	t_list	*tmp;

	list = (t_list *)content;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->content);
		tmp->content = NULL;
		tmp->content_size = content_size;
		free(tmp);
		tmp = NULL;
	}
	free(list);
	list = NULL;
}

void	free_content(void *content, size_t content_size)
{
	free(content);
	content = NULL;
	content_size = 0;
}

void	get_opponent_coordinates(t_list **head, t_data *game)
{
	char	*map_i;
	int		index;

	map_i = game->map->area;
	while ((map_i = ft_strchr(map_i, 'O')))
	{
		index = map_i - game->map->area;
		ft_lstadd_sorted(head, ft_lstnew(&index, sizeof(int)));
		ft_log("Opponent crd: %d %d\n", index / game->map->y, index % game->map->y);
		map_i++;
	}
}

int		npimenof(t_data *game)
{
	t_list	*coordinates;
	t_list	*opponent_coordinates;
	int		crd;

	opponent_coordinates = NULL;
	coordinates = available_coordinates(game);
	crd = traverse_linked_linked_list(coordinates);
	get_opponent_coordinates(&opponent_coordinates, game);
	ft_lstdel(&coordinates, free_nested_list);
	ft_lstdel(&opponent_coordinates, free_content);
	return (0);
}


// ft_putnbr_fd(a / map->y, 1);
// ft_putchar_fd(' ', 1);
// ft_putnbr_fd(a % map->y, 1);
// ft_putchar_fd('\n', 1);
// return (1);