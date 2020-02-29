/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npimenof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:46:06 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/29 18:38:46 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

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

int		get_min_distance(t_list **opponent, t_point *player)
{
	int		distance;
	int		min_distance;
	t_list	*tmp;

	min_distance = point_distance((t_point *)(*opponent)->content, player);
	tmp = (*opponent)->next;
	while (tmp)
	{
		// ft_log("FAIL HERE\n");
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

	if (!new)
		return ;
	while (new)
	{
		tmp2 = new;
		if (!(*head) || compare_distance(opponent, (*head)->content, new->content))
		{
			new = new->next;
			tmp2->next = *head;
			*head = tmp2;
		}
		else
		{
			tmp1 = *head;
			while (tmp1->next && compare_distance(opponent, tmp1->content, new->content))
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

	while (head)
	{
		item = (t_list *)head->content;
		lstadd_point_sorted(&result, opponent, item);
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
	return (result);
}

int		npimenof(t_data *game)
{
	t_list	*coordinates;
	t_list	*opponent_coordinates;
	t_list	*sorted;

	opponent_coordinates = NULL;
	coordinates = available_coordinates(game);
	get_opponent_coordinates(&opponent_coordinates, game);
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
