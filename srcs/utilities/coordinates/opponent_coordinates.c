/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opponent_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:41:10 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/08 16:28:04 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		orientation(t_point p, t_point q, t_point r)
{
	int		val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	return (val);
}

void	find_hull(t_list **hull, t_list *points, size_t min_l)
{
	while (points)
	{
		while (ft_lstlen(*hull) >= min_l &&
				orientation(*(t_point *)points->content,
							*(t_point *)(*hull)->content,
							*(t_point *)(*hull)->next->content) <= 0)
			ft_lstpop(hull);
		ft_lstadd(hull, ft_lstnew(points->content, sizeof(points->content)));
		points = points->next;
	}
}

t_list	*grahams_scan(t_list *points)
{
	t_list			*hull;
	t_list			*tmp1;
	size_t			len1;

	if ((len1 = ft_lstlen(points)) < 4)
		return (NULL);
	hull = NULL;
	tmp1 = points;
	ft_lstadd(&hull, ft_lstnew(tmp1->content, sizeof(tmp1->content)));
	ft_lstadd(&hull, ft_lstnew(tmp1->next->content, sizeof(tmp1->content)));
	tmp1 = points->next->next;
	find_hull(&hull, tmp1, 2);
	ft_lstrev(&points);
	ft_lstadd(&hull, ft_lstnew(points->next->content, sizeof(points->content)));
	len1 = ft_lstlen(hull);
	tmp1 = points->next->next;
	find_hull(&hull, tmp1, len1);
	ft_lstdel(&points, ft_del_lstcontent);
	return (hull);
}

t_list	*opponent_coords(t_data *game)
{
	char	*map_i;
	t_list	*convex_hull;
	t_list	*head;
	int		index;
	t_point	point;

	head = NULL;
	map_i = game->map->area;
	while ((map_i = ft_strchr(map_i, game->opponent->mark)))
	{
		index = map_i - game->map->area;
		point.x = index / game->map->y;
		point.y = index % game->map->y;
		ft_lstadd_sorted(&head, ft_lstnew(&point, sizeof(t_point)));
		map_i++;
	}
	if ((convex_hull = grahams_scan(head)))
		head = convex_hull;
	return (head);
}

t_list	*opponent_coors2(t_data *game)
{
	char	*map_i;
	int		index;
	t_point	point;
	t_list	*head;

	head = NULL;
	map_i = game->map->area;
	while ((map_i = ft_strchr(map_i, game->opponent->mark)))
	{
		index = map_i - game->map->area;
		point.x = index / game->map->y;
		point.y = index % game->map->y;
		ft_lstadd_sorted(&head, ft_lstnew(&point, sizeof(t_point)));
		map_i++;
	}
	return (head);
}
