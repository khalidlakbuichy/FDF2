/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:03:28 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/15 09:19:38 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

void	projection_iso_para(fdf *data, int key)
{
	if (KEY_LT == key)
	{
		data->view = PARALLEL;
		data->tita = -1.5708;
		data->beta = 0;
		data->meta = 0;
	}
	if (KEY_LO == key)
	{
		data->view = ISO;
		data->tita = 0;
		data->beta = 0;
		data->meta = 0;
	}
}

void	zoom_in_out(fdf *data, int key)
{
	if (KEY_PLUS == key || KEY_LM == key)
	{
		data->zoom *= exp(0.02);
		isometric_centering(data);
	}
	if (KEY_MINUS == key)
	{
		data->zoom *= exp(-0.02);
		isometric_centering(data);
	}
}

void	shift_x_y(fdf *data, int key)
{
	if (key == 65362)
		data->shift_y -= 20;
	if (key == 65364)
		data->shift_y += 20;
	if (key == 65363)
		data->shift_x += 20;
	if (key == 65361)
		data->shift_x -= 20;
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

void	upper_lower_z(fdf *data, int key)
{
	unsigned	x;
	unsigned	y;

	if (KEY_LU == key)
	{
		y = -1;
		while (++y < data->heigth)
		{
			x = -1;
			while (++x < data->width)
				if (data->z_matrix[y][x].z <= 65536)
					data->z_matrix[y][x].z *= 1.25;
		}
	}
	if (KEY_LL == key)
	{
		y = -1;
		while (++y < data->heigth)
		{
			x = -1;
			while (++x < data->width)
				if (data->z_matrix[y][x].z <= 65536)
					data->z_matrix[y][x].z /= 1.25;
		}
	}
}
