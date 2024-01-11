/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:03:28 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/11 11:34:38 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom_in_out(fdf *data, int key)
{
	if (key == 112)
		data->zoom *= exp(0.02);
	if (key == 109)
		data->zoom *= exp(-0.02);
}

void	shift_x_y(fdf *data, int key)
{
	if (key == 65362)
		data->shift_y -= 10;
	if (key == 65364)
		data->shift_y += 10;
	if (key == 65363)
		data->shift_x += 10;
	if (key == 65361)
		data->shift_x -= 10;
}

void	rotation_x_y_z(fdf *data, int key)
{
	if (key == 121)
		data->beta += 0.25;
	if (key == 122)
		data->meta += 0.25;
	if (key == 120)
		data->tita += 0.25;
}