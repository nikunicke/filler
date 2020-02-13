/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:07:50 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/13 17:53:15 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

typedef struct	s_data
{
	int			x;
	int			y;
	char		*map;
}				t_data;

int		update_data(t_data *data)
{
	return (0); // this func should work for both the piece and the map
}

int		read_input()
{
	int		index;
	char	*line;
	t_data	*map;
	t_data	*piece;

	// init map and piece or just set to NULL???
	while (ft_get_next_line(1, &line) > 0)
	{
		if (ft_strstr(line, "Plateau"))
			update_data(map);
		else if (ft_strstr(line, "Piece"))
			update_data(piece);
		ft_strdel(&line);
	}
	return (0);
}

int		main(void)
{
	char	*line;
	char	*dim;
	char	*map;
	char	**xy;
	int		index;
	int		buf_size;

	dim = NULL;
	while (ft_get_next_line(1, &line) > 0)
	{
		if (ft_strstr(line, "Plateau"))
		{
			index = ft_strcspn(line, "0123456789");
			dim = ft_strsub(line, index, ft_strcspn(line + index, ":"));
			printf("Plateau dimensions: %s\n", dim);
			xy = ft_strsplit(dim, ' ');
			while (ft_atoi(xy[0]) > 0 && ft_get_next_line(1, &line) > 0)
			{
				buf_size = ft_atoi(xy[0]) * ft_atoi(xy[1]); // Consider including space for newlines here. GNL does not return them though
				map = ft_strnew(buf_size);
				
			}
		}
		if (ft_strstr(line, "Piece"))
		{
			index = ft_strcspn(line, "0123456789");
			dim = ft_strsub(line, index, ft_strcspn(line + index,  ":"));
			printf("Piece dimensions: %s\n", dim);
		}
		free(dim);
		free(line);
		dim = NULL;
		line = NULL; // Consider fixin ft_del_args for this. Addresses not being set to NULL in this scope
	}
	system("leaks a.out");
	return (0);
}
