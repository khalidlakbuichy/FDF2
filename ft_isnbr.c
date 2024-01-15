/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:45:33 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/15 10:11:10 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_white(int c)
{
	if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v'
		|| c == '\f')
		return (1);
	return (0);
}

int	ft_isnbr(const char *str)
{
	int	i;

	i = 0;
	while (is_white(str[i]) && 0 != str[i])
		i++;
	if ('-' == str[i])
		i++;
	while (0 != str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (is_white(str[i]))
			break ;
		i++;
	}
	return (1);
}
