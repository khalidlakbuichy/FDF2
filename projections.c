/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:00:59 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/13 19:28:30 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	isometric(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void	one_point_perspective(int *x, int *y, int z)
{
	int		van_point_x;
	int		van_point_y;
	float	distance;

	van_point_x = (WIDTH / 2);
	van_point_y = (HEIGHT / 2);
	distance = 150;
	if (z != 0)
	{
		*x = van_point_x + ((*x - van_point_x) * distance) / (distance + z);
		*y = van_point_y + ((*y - van_point_y) * distance) / (distance + z);
	}
}
