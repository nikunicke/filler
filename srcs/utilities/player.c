/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:32:25 by npimenof          #+#    #+#             */
/*   Updated: 2020/03/08 13:57:39 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

static int	get_player_id(void)
{
	static int	num;
	char		*line;
	int			i;

	if (num)
		return (num == 1 ? 2 : 1);
	i = 0;
	while (i++ < 1 && ft_get_next_line(fde, &line) > 0)
	{
		if (ft_strstr(line, "$$$ exec p"))
		{
			num = ft_atoi(&line[ft_strcspn(line, "12")]);
			ft_strdel(&line);
			return (num);
		}
		ft_strdel(&line);
	}
	return (0);
}

t_player	*new_player(void)
{
	t_player	*player;
	int			player_id;

	if (!(player_id = get_player_id()))
		return (NULL);
	if (player_id != 1 && player_id != 2)
		return (NULL);
	if (!(player = malloc(sizeof(t_player))))
		return (NULL);
	player->id = player_id;
	if (player_id == 1)
		player->mark = 'O';
	else
		player->mark = 'X';
	player->points = 0;
	player->algorithm = NULL;
	return (player);
}
