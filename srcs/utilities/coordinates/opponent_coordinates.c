/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opponent_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:41:10 by npimenof          #+#    #+#             */
/*   Updated: 2020/03/07 19:15:11 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		orientation(t_point p, t_point q, t_point r)
{
	int		val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	return (val);
}

void	ft_lstpop(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	*head = tmp->next;
	// ft_lstdelone(&tmp, ft_del_lstcontent);
}

int		ft_lstlen(t_list *lst)
{
	t_list	*tmp;
	size_t	i;

	tmp = lst;
	i = 0;
	while (tmp && ++i)
	{
		tmp = tmp->next;
	}
	return (i);
}

void	ft_lstrev(t_list **head)
{
	t_list	*current;
	t_list	*nxt;
	t_list	*prev;

	nxt = NULL;
	prev = NULL;
	current = *head;
	while (current)
	{
		nxt = current->next;
		current->next = prev;
		prev = current;
		current = nxt;
	}
	*head = prev;
}

t_list	*grahams_scan(t_list *points)
{
	static t_list	*hull;
	t_list			*tmp1;
	t_list			*tmp2;
	// int				i;
	int				len1;

	if ((len1 = ft_lstlen(points)) < 4)
		return NULL;
	hull = NULL;
	tmp1 = points;
	ft_lstadd(&hull, ft_lstnew(tmp1->content, sizeof(tmp1->content)));
	ft_lstadd(&hull, ft_lstnew(tmp1->next->content, sizeof(tmp1->content)));
	tmp1 = points->next->next;
	while (tmp1)
	{
		tmp2 = tmp1;
		while (ft_lstlen(hull) >= 2 && orientation(*(t_point *)tmp1->content, *(t_point *)hull->content, *(t_point *)hull->next->content) <= 0)
			ft_lstpop(&hull);
		ft_lstadd(&hull, ft_lstnew(tmp1->content, sizeof(tmp1->content)));
		tmp1 = tmp1->next;
	}
	ft_lstrev(&points);
	len1 = ft_lstlen(hull);
	tmp1 = points->next->next;
	while (tmp1->next)
	{
		while (ft_lstlen(hull) >= len1 && orientation(*(t_point *)tmp1->content, *(t_point *)hull->content, *(t_point *)hull->next->content) <= 0)
			ft_lstpop(&hull);
		ft_lstadd(&hull, ft_lstnew(tmp1->content, sizeof(tmp1->content)));
		tmp1 = tmp1->next;
	}
	return (hull);
}

void	get_opponent_coordinates(t_list **head, t_data *game)
{
	char	*map_i;
	t_list	*convex_hull;
	int		index;
	t_point	point;

	map_i = game->map->area;
	while ((map_i = ft_strchr(map_i, game->opponent->mark)))
	{
		index = map_i - game->map->area;
		point.x = index / game->map->y;
		point.y = index % game->map->y;
		ft_lstadd_sorted(head, ft_lstnew(&point, sizeof(t_point)));
		map_i++;
	}
	if ((convex_hull = grahams_scan(*head)))
	{
		ft_lstdel(head, ft_del_lstcontent);
		*head = convex_hull;
	}
}
