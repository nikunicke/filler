/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:41:43 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/18 14:44:47 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "filler.h"

t_data		*new_game(t_player *(*new_player)(), t_grid *(*new_grid)())
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->player = new_player()))
		return (NULL);
	if (!(data->opponent = new_player()))
		return (NULL);
	if (!(data->map = new_grid("Plateau")))
		return (NULL); 
	data->piece = NULL;
	return (data);
}
