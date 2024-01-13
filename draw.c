/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:42:50 by khalid            #+#    #+#             */
/*   Updated: 2024/01/13 18:21:59 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if ((x >= WIDTH || x < 0) || (y >= HEIGHT || y < 0))
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(fdf *data, t_line line)
{
	t_dda	dda;
	int		i;

	line.z = data->z_matrix[line.y][line.x].z;
	line.z1 = data->z_matrix[line.y1][line.x1].z;
	ft_rotation(data, &line);
	ft_zoom(data, &line);
	ft_isometric(&line);
	
	ft_transalation(data, &line);
	dda.dx = line.x1 - line.x;
	dda.dy = line.y1 - line.y;
	dda.steps = ft_max(abs(dda.dx), abs(dda.dy));
	dda.xinc = (line.x1 - line.x) / (float)dda.steps;
	dda.yinc = (line.y1 - line.y) / (float)dda.steps;
	dda.x = line.x;
	dda.y = line.y;
	i = 0;
	while (i <= dda.steps)
	{
		my_mlx_pixel_put(&data->mlx.img, round(dda.x), round(dda.y),
			line.color);
		dda.x += dda.xinc;
		dda.y += dda.yinc;
		i++;
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
			line.x1 = line.x;
			line.y1 = line.y;
			line.color = data->z_matrix[line.y][line.x].color;
			if (line.x < data->width - 1)
			{
				line.x1++;
				draw_line(data, line);
				line.x1--;
			}
			if (line.y < data->heigth - 1)
			{
				line.y1++;
				draw_line(data, line);
			}
			line.x++;
		}
		line.y++;
	}
}
