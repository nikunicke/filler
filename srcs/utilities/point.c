/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:20:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/18 14:04:23 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_point		i_to_point(int index, t_grid *map)
{
	t_point point;

	point.x = index / map->y;
	point.y = index % map->y;
	return (point);
}

int			to_index(t_point p, int w)
{
	return ((p.x * w) + p.y);
}

int			write_point(t_point *point)
{
	if (point)
	{
		ft_putnbr_fd(point->x, 1);
		ft_putchar_fd(' ', 1);
		ft_putnbr_fd(point->y, 1);
		ft_putchar_fd('\n', 1);
	}
	else
	{
		write(1, "0 0\n", 4);
		return (0);
	}
	return (1);
}
