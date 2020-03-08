/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:32:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/03/08 13:32:53 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list **head)
{
	t_list	*tmp;

	tmp = *head;
	*head = tmp->next;
	ft_lstdelone(&tmp, ft_del_lstcontent);
}
