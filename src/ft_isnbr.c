/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:45:33 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:09:45 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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

	if (NULL == str || '\0' == *str)
		return (0);
	i = 0;
	while (is_white(str[i]) && 0 != str[i])
		i++;
	if ('-' == str[i])
		i++;
	if (is_white(str[i]))
		return (0);
	while (0 != str[i])
	{
		if (is_white(str[i]))
			break ;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	ft_ishexdigit(char c)
{
	char	h;

	h = ft_tolower(c);
	return (ft_isdigit(h) || (h >= 'a' && h <= 'f'));
}

int	ft_ishex(const char *str)
{
	int	i;

	if (NULL == str || '\0' == *str)
		return (0);
	i = 0;
	if (ft_strlen(str) > 10)
		return (0);
	while (is_white(str[i]) && 0 != str[i])
		i++;
	if (!ft_strnstr(&str[i], "0x", 2))
		return (0);
	i += 2;
	if (0 == str[i])
		return (0);
	while (0 != str[i] && '\n' != str[i])
	{
		if (!ft_ishexdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
