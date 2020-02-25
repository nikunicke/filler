/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:20:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/25 18:51:36 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "filler.h"

t_point		*new_point(int x, int y)
{
	t_point	*point;

	if (!(point = malloc(sizeof(t_point))))
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

t_point		set_point(int x, int y)
{
	static t_point	point;

	point.x = x;
	point.y = y;
	return (point);
}

int			point_to_index(t_point point, t_grid *map)
{
	int		index;

	index = (point.x * map->y) + point.y;
	return (index);
}

t_point		point_addition(t_point *a, t_point *b)
{
	static t_point	sum;
	
	sum.x = a->x + b->x;
	sum.y = a->y + b->y;
	return (sum);
}
