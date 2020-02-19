/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:34:58 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/19 11:16:10 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static int	*grid_size(char *identifier)
{
	int				i;
	int				*xy;
	char			*line;

	if (!(xy = malloc(sizeof(int) * 2)))
		return (NULL);
	i = 0;
	while (i++ < 1 && ft_get_next_line(0, &line) > 0)
	{
		if (ft_strstr(line, identifier))
		{
			i = ft_strcspn(line, "0123456789");
			xy[0] = ft_atoi(&line[i]);
			xy[1] = ft_atoi(&line[i + ft_strspn(&line[i], "0123456789")]);
			ft_strdel(&line);
			return (xy);
		}
		ft_strdel(&line);
	}
	return (NULL);
}

void	update_area(t_grid *grid)
{
	char	*line;
	int		i;

	i = 0;
	while (i < grid->x && ft_get_next_line(0, &line) > 0)
	{
		if (ft_iswhitespace(*line) || ft_isalpha(*line))
		{
			ft_strdel(&line);
			continue ;
		}
		ft_strncpy(&grid->area[i * (grid->y)], &line[ft_strspn(line, " \t0123456789")], grid->y);
		ft_strdel(&line);
		i++;
	}
}

t_grid		*new_grid(char *identifier)
{
	t_grid		*grid;
	int			*dimensions;
	int			size;

	if (!(dimensions = grid_size(identifier)))
		return (NULL);
	size = dimensions[0] * dimensions[1];
	if (!(grid = malloc(sizeof(t_grid))))
		return (NULL);
	if (!(grid->area = ft_strnew(size)))
		return (NULL);
	grid->x = dimensions[0];
	grid->y = dimensions[1];
	update_area(grid);
	free(dimensions);
	dimensions = NULL;
	return (grid);
}
