/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:03:28 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/17 18:13:21 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "controls.h"
#define MAX_Z 500

void	projection_iso_para(t_fdf *data, int key)
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

void	zoom_in_out(t_fdf *data, int key)
{
	int	factor;

	factor = 0.5;
	if ((KEY_PLUS == key || KEY_LP == key) && data->zoom <= MAX_ZOOM_IN)
	{
		data->zoom = lerp(data->zoom, data->zoom * 1.1, factor);
		ft_centering(data);
	}
	factor = 0.5;
	if ((KEY_MINUS == key || KEY_LM == key) && data->zoom > 2)
	{
		data->zoom = lerp(data->zoom, data->zoom * 1.1, factor);
		ft_centering(data);
	}
}

void	shift_x_y(t_fdf *data, int key)
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

void	rotation_x_y_z(t_fdf *data, int key)
{
	if (KEY_LX == key)
		data->beta += 0.25;
	if (KEY_LY == key)
		data->meta += 0.25;
	if (KEY_LZ == key)
		data->tita += 0.25;
}

void	upper_z(t_fdf *data)
{
	int	x;
	int	y;
	int	factor;

	factor = 10;
	y = -1;
	while (++y < data->heigth)
	{
		x = -1;
		while (++x < data->width)
		{
			if (0 != data->z_matrix[y][x].z && data->z_matrix[y][x].z <= MAX_Z)
			{
				if (0 == data->z_matrix[y][x].z + factor)
					data->z_matrix[y][x].z += (factor + 1);
				else
					data->z_matrix[y][x].z += factor;
			}
		}
	}
}

void	lower_z(t_fdf *data)
{
	int x;
	int y;
	int factor;

	factor = 10;
	y = -1;
	while (++y < data->heigth)
	{
		x = -1;
		while (++x < data->width)
		{
			if (0 != data->z_matrix[y][x].z && data->z_matrix[y][x].z >= -MAX_Z)
			{
				if (0 == data->z_matrix[y][x].z - factor)
					data->z_matrix[y][x].z -= (factor + 1);
				else
					data->z_matrix[y][x].z -= factor;
			}
		}
	}
}