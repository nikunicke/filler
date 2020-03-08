/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:28:55 by npimenof          #+#    #+#             */
/*   Updated: 2020/02/24 13:12:45 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdarg.h>
#include <stdio.h>

int		ft_log(char *msg, ...)
{
	int			ret;
	va_list		args;
	FILE		*fp;

	fp = fopen("filler.log", "a+");
	va_start(args, msg);
	ret = vfprintf(fp, msg, args);
	va_end(args);
	fclose(fp);
	return (ret);
}
