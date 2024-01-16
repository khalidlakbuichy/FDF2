/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:01:06 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/16 14:44:32 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

int	deal_mouse(int button, int x, int y, fdf *data)
{
	float	factor;

	factor = 0.5;
	if (button == 4)
	{
		data->zoom = lerp(data->zoom, data->zoom * 1.1, factor);
		ft_centering(data);
	}
	else if (button == 5)
	{
		data->zoom = lerp(data->zoom, data->zoom / 1.1, factor);
		ft_centering(data);
	}
	ft_render(data);
	return (0);
}
