/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 09:51:51 by khalid            #+#    #+#             */
/*   Updated: 2024/01/18 10:09:39 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	hex_to_int(char nb, const char *hex_base)
{
	int	i;

	i = 0;
	while (hex_base[i] != '\0')
	{
		if (hex_base[i] == ft_tolower(nb))
			return (i);
		i++;
	}
	return (-1);
}

long int	ft_atoi_hex(const char *hex)
{
	int			i;
	int			tmp;
	long int	hex_nbr;
	const char	*hex_base;

	if (NULL == hex || '\0' == *hex)
		return (0);
	if (NULL == ft_strnstr(hex, "0x", 2))
		return (0);
	if (ft_strlen(hex) > 10)
		return (0);
	i = 2;
	hex_nbr = 0;
	hex_base = "0123456789abcdef";
	while (hex[i] != '\0')
	{
		tmp = hex_to_int(hex[i], hex_base);
		if (tmp == -1)
			return (-1);
		hex_nbr = (hex_nbr * 16) + tmp;
		i++;
	}
	return (hex_nbr);
}
