/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 11:01:06 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:16:31 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../inc/controls.h"
#include "../inc/draw.h"

float	lerp(float a, float b, float t)
{
	return (a + t * (b - a));
}

int	deal_mouse(int button, int x, int y, t_fdf *data)
{
	float	factor;

	(void)x;
	(void)y;
	factor = 0.5;
	if (4 == button && data->zoom <= MAX_ZOOM_IN)
	{
		data->zoom = lerp(data->zoom, data->zoom * 1.1, factor);
		ft_centering(data);
	}
	else if (5 == button && data->zoom > MAX_ZOOM_OUT)
	{
		data->zoom = lerp(data->zoom, data->zoom / 1.1, factor);
		ft_centering(data);
	}
	ft_render(data);
	return (0);
}
