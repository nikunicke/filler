/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opponent_coordinates.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 09:41:10 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/29 19:00:52 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	get_opponent_coordinates(t_list **head, t_data *game)
{
	char	*map_i;
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
}
