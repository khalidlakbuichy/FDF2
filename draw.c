/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:42:50 by khalid            #+#    #+#             */
/*   Updated: 2024/01/11 09:29:54 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	create_trgb(int t, int r, int g, int b)
// {
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

void	my_mlx_pixel_put(t_img *img, long x, long y, int color)
{
	char	*dst;

	if ((x >= WIDTH || x < 0) || (y >= HEIGHT || y < 0))
		return ;
	dst = img->addr + ABS((y * img->line_length + x * (img->bpp / 8)));
	*(unsigned int *)dst = color;
}
void	make_zoom(fdf *data)
{
}

void	draw_line(fdf *data, t_line line)
{
	int		dx;
	int		dy;
	int		steps;
	int		z;
	int		z1;
	float	Xinc;
	float	Yinc;
	float	X;
	float	Y;

	z = data->z_matrix[Y0][X0].z;
	z1 = data->z_matrix[Y1][X1].z;
	/* Rotation */
	x_rotation(&Y0, &z, &data->tita);
	x_rotation(&Y1, &z1, &data->tita);
	y_rotation(&X0, &z, &data->beta);
	y_rotation(&X1, &z1, &data->beta);
	z_rotation(&X0, &Y0, &data->meta);
	z_rotation(&X1, &Y1, &data->meta);
	/* zoom */
	X0 *= data->zoom;
	X1 *= data->zoom;
	Y0 *= data->zoom;
	Y1 *= data->zoom;
	/* projection */
	isometric(&X0, &Y0, z);
	isometric(&X1, &Y1, z1);
	/* transalation */
	X0 += data->shift_x;
	X1 += data->shift_x;
	Y0 += data->shift_y;
	Y1 += data->shift_y;
	dx = X1 - X0;
	dy = Y1 - Y0;
	steps = ABS(dx) > ABS(dy) ? ABS(dx) : ABS(dy);
	Xinc = dx / (float)steps;
	Yinc = dy / (float)steps;
	X = X0;
	Y = Y0;
	for (int i = 0; i <= steps; i++)
	{
		my_mlx_pixel_put(&data->mlx.img, (long)round(X), (long)round(Y), color);
		X += Xinc; // increment in x at each step
		Y += Yinc; // increment in y at each step
	}
}

void	draw_map(fdf *data)
{
	t_line	line;

	line.y = 0;
	while (line.y < data->heigth)
	{
		line.x = 0;
		while (line.x < data->width)
		{
			line.color = data->z_matrix[line.y][line.x].color;
			if (line.x < data->width - 1)
			{
				line.x1 = line.x + 1;
				DDA(data, line);
			}
			if (line.y < data->heigth - 1)
			{
				line.y1 = line.y + 1;
				DDA(data, line);
			}
			line.x++;
		}
		line.y++;
	}
}
