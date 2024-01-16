/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:03:28 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/16 16:41:56 by klakbuic         ###   ########.fr       */
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
	if (KEY_PLUS == key && data->zoom <= 50)
	{
		data->zoom *= exp(0.02);
		ft_centering(data);
	}
	if (KEY_MINUS == key && data->zoom > 2)
	{
		if (data->zoom > 2)
			data->zoom *= exp(-0.02);
		ft_centering(data);
	}
}

void	shift_x_y(fdf *data, int key)
{
	if (KEY_ARR_UP == key)
		data->shift_y -= 20;
	if (KEY_ARR_DOWN == key)
		data->shift_y += 20;
	if (KEY_ARR_RIGHT == key)
		data->shift_x += 20;
	if (KEY_ARR_LEFT == key)
		data->shift_x -= 20;
}

void	rotation_x_y_z(fdf *data, int key)
{
	if (KEY_LX == key)
		data->beta += 0.25;
	if (KEY_LY == key)
		data->meta += 0.25;
	if (KEY_LZ == key)
		data->tita += 0.25;
}

void	upper_lower_z(fdf *data, int key)
{
	unsigned int	x;
	unsigned int	y;

	if (KEY_LU == key)
	{
		y = -1;
		while (++y < data->heigth)
		{
			x = -1;
			while (++x < data->width)
			{
				printf("z: %d\n", data->z_matrix[y][x].z);
				if (data->z_matrix[y][x].z > 0 && data->z_matrix[y][x].z <= 500)
					data->z_matrix[y][x].z += 5;
			}
		}
	}
	if (KEY_LL == key)
	{
		y = -1;
		while (++y < data->heigth)
		{
			x = -1;
			while (++x < data->width)
				if (data->z_matrix[y][x].z > 5)
					data->z_matrix[y][x].z -= 5;
		}
	}
}
