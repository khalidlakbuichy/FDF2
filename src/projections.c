/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:00:59 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:16:09 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	isometric(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	ft_centering(t_fdf *data)
{
	int	center_x;
	int	center_y;
	int	center_z;

	center_x = (data->width * data->zoom) / 2;
	center_y = (data->heigth) / 2;
	center_z = 0;
	if (ISO == data->view)
	{
		center_y = (data->heigth * data->zoom) / 2;
		isometric(&center_x, &center_y, center_z);
	}
	data->shift_x = (WIDTH / 2) - center_x;
	data->shift_y = (HEIGHT / 2) - center_y;
}
