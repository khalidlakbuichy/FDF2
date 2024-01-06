/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:42:50 by khalid            #+#    #+#             */
/*   Updated: 2024/01/06 11:19:42 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MAX(a, b) (a > b ? a : b)
#define ABS(a) (a < 0 ? -a : a)

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
// void	drawLine(t_data *img, int x0, int y0, int x1, int y1)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = x0 < x1 ? 1 : -1;
// 	int sy = y0 < y1 ? 1 : -1;
// 	int err = (dx > dy ? dx : -dy) / 2;
// 	int e2;

// 	while (1)
// 	{
// 		my_mlx_pixel_put(img, x0, y0, create_trgb(0, 255, 0, 0));

// 		if (x0 == x1 && y0 == y1)
// 			break ;

// 		e2 = err;
// 		if (e2 > -dx)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dy)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

void	isometric(float *x, float *y, int z)
{
	*x =  (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}
void	draw_line(fdf *data, float x, float y, float x1, float y1)
{
	float	x_step;
	float	y_step;
	int		max;
	int		z;
	int		z1;
	
	z = data->z_matrix[(int)y][(int)x];
	z1 = data->z_matrix[(int)y1][(int)x1];
	
	/* zoom */
	x *= data->zoom;
	x1 *= data->zoom;
	y *= data->zoom;
	y1 *= data->zoom;
	
	/* color*/
	data->color = (z || z1) ? 0xe80c0c : 0xffffffff;

	/* 3D */
	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);

	/* shift */
	x += 150;
	x1 += 150;
	y += 150;
	y1 += 150;
	
	x_step = x1 - x;
	y_step = y1 - y;
	max = MAX(ABS(x_step), ABS(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
		x += x_step;
		y += y_step;
	}
}

void	draw_map(fdf *data, t_data *img)
{
	int x;
	int y;

	y = 0;
	while (y < data->heigth)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				draw_line(data, x, y, x + 1, y);
			if (y < data->heigth - 1)
				draw_line(data, x, y, x, y + 1);
			x++;
		}
		y++;
	}
}