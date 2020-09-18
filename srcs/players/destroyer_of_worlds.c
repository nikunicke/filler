/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer_of_worlds.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 16:13:35 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/18 14:05:06 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

static int		get_value(int *heatmap, t_point point, t_data *game)
{
	char	*ptr;
	t_point	p;
	int		value;

	value = 0;
	ptr = game->piece->area;
	while ((ptr = ft_strchr(ptr, '*')))
	{
		p = i_to_point(ptr - game->piece->area, game->piece);
		p.x += point.x;
		p.y += point.y;
		value += heatmap[to_index(p, game->map->y)];
		ptr++;
	}
	return (value);
}

static t_point	*most_valuable_point(t_data *game, int *heatmap, t_list *coords)
{
	t_point *result;
	t_list	*p;
	int		value;
	int		max;

	result = NULL;
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

static t_point	*best_option(t_data *game, t_list *coords)
{
	int		*heatmap;
	t_point *result;

	result = NULL;
	heatmap = create_heatmap(game);
	result = most_valuable_point(game, heatmap, coords);
	free(heatmap);
	return (result);
}

static void		del_nested(void *content, size_t size)
{
	t_list	*c;

	c = (t_list *)content;
	if (c)
		c->content_size -= size;
	ft_lstdel(&c, ft_del_lstcontent);
}

int				destroyer_of_worlds(t_data *game)
{
	t_list	*coords;
	t_point *result;
	int		n;

	coords = available_coordinates(game);
	result = best_option(game, coords);
	n = write_point(result);
	ft_lstdel(&coords, del_nested);
	return (n);
}
