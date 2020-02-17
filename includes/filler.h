/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:37:49 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/17 14:23:59 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# define PLAYER npimenof_dummy

typedef struct	s_player 
{
	int			id;
	int			points;
	void		(*algorithm)();
}				t_player;

typedef struct	s_grid
{
	int			x;
	int			y;
	char		*area;
}				t_grid;

typedef struct	s_data
{
	t_player	*player;
	t_player	*opponent; 
	t_grid		*map;
	t_grid		*piece;
}				t_data;

#endif