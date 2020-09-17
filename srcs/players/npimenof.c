/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npimenof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:46:06 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/08 16:29:31 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

int		get_min_distance(t_list **opponent, t_point *player)
{
	int		distance;
	int		min_distance;
	t_list	*tmp;

	if (!*opponent)
		return (1);
	min_distance = point_distance((t_point *)(*opponent)->content, player);
	tmp = (*opponent)->next;
	while (tmp)
	{
		distance = point_distance((t_point *)tmp->content, player);
		if (distance < min_distance)
		{
			min_distance = distance;
			tmp = *opponent;
		}
		tmp = tmp->next;
	}
	return (min_distance);
}

int		compare_distance(t_list **opponent, t_point *a, t_point *b)
{
	static int		i;
	static t_point	tested;
	static int		result;

	if (tested.x != a->x && tested.y != a->y)
		i = 0;
	if (!i)
	{
		result = get_min_distance(opponent, a);
		tested.x = a->x;
		tested.y = a->y;
		i = 1;
	}
	if (get_min_distance(opponent, b) < result)
		return (1);
	return (0);
}

void	lstadd_point_sorted(t_list **head, t_list **opponent, t_list *new)
{
	t_list	*tmp1;
	t_list	*tmp2;

	while (new)
	{
		tmp2 = new;
		if (!(*head) ||
			compare_distance(opponent, (*head)->content, new->content))
		{
			new = new->next;
			tmp2->next = *head;
			*head = tmp2;
		}
		else
		{
			tmp1 = *head;
			while (tmp1->next &&
					compare_distance(opponent, tmp1->content, new->content))
				tmp1 = tmp1->next;
			new = new->next;
			tmp2->next = tmp1->next;
			tmp1->next = tmp2;
		}
	}
}

t_list	*traverse_nested_list(t_list *head, t_list **opponent)
{
	t_list	*result;
	t_list	*item;
	t_list	*tmp;

	result = NULL;
	while (head)
	{
		item = (t_list *)head->content;
		lstadd_point_sorted(&result, opponent, item);
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
	if (!result)
		return (head);
	return (result);
}

int		map_indx(t_point *p, t_grid *map)
{
	return (p->x * map->y + p->y);
}

int		check_point(t_point *p, t_grid *map)
{
	int		dist;
	int		i;
	int		j;
	int		count;
	t_point	ref;

	if (map->x > 20)
		dist = 6;
	else
		dist = 3;
	i = dist;
	ref.x = ft_ignore_neg(p->x - (dist / 2));
	count = 0;
	while (ref.x < map->x && i--)
	{
		ref.y = ft_ignore_neg(p->y - (dist / 2));
		j = dist;
		while (ref.y < map->y && j--)
		{
			if (map->area[map_indx(&ref, map)] == '.')
				count++;
			ref.y++;
		}
		ref.x++;
	}
	if (count > 1)
		return (0);
	return (1);
}

int		check_oppo_c(t_list **opponent, t_grid *map)
{
	t_list	*current;
	t_list	*prev;
	t_list	*nxt;
	t_point	*data;

	prev = NULL;
	nxt = NULL;
	current = *opponent;
	while (current)
	{
		data = POINT(current);
		if (check_point(data, map) && !prev)
		{
			*opponent = (*opponent)->next;
			current = *opponent;
			prev = NULL;
		}
		else if (check_point(data, map))
		{
			prev->next = current->next;
			current = current->next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (1);
}

int		npimenof(t_data *game)
{
	t_list	*coordinates;
	t_list	*opponent_coordinates;
	t_list	*sorted;

	coordinates = available_coordinates(game);
	opponent_coordinates = opponent_coords(game);
	check_oppo_c(&opponent_coordinates, game->map);
	sorted = traverse_nested_list(coordinates, &opponent_coordinates);
	if (sorted)
	{
		ft_putnbr_fd(((t_point *)sorted->content)->x, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(((t_point *)sorted->content)->y, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		write(1, "0 0\n", 4);
		return (0);
	}
	ft_lstdel(&sorted, ft_del_lstcontent);
	ft_lstdel(&opponent_coordinates, ft_del_lstcontent);
	return (1);
}
