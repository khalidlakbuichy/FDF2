/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:00:59 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/11 14:48:07 by klakbuic         ###   ########.fr       */
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
	int vanishing_point_x = WIDTH / 2;  // Adjust this value as needed
	int vanishing_point_y = HEIGHT / 2; // Adjust this value as needed
	float distance = 150;
	// Adjust this value for distance from the viewer
	if (z != 0)
	{
		*x = vanishing_point_x + ((*x - vanishing_point_x) * distance)
			/ (distance + z);
		*y = vanishing_point_y + ((*y - vanishing_point_y) * distance)
			/ (distance + z);
	}
}