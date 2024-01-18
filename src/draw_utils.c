/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 08:55:37 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:07:41 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/fdf.h"

void	ft_rotation(t_fdf *data, t_line *line)
{
	x_rotation(&line->y, &line->z, &data->tita);
	x_rotation(&line->y1, &line->z1, &data->tita);
	y_rotation(&line->x, &line->z, &data->beta);
	y_rotation(&line->x1, &line->z1, &data->beta);
	z_rotation(&line->x, &line->y, &data->meta);
	z_rotation(&line->x1, &line->y1, &data->meta);
}

void	ft_zoom(t_fdf *data, t_line *line)
{
	line->x *= data->zoom;
	line->y *= data->zoom;
	line->x1 *= data->zoom;
	line->y1 *= data->zoom;
}

void	ft_isometric(t_line *line)
{
	isometric(&line->x, &line->y, line->z);
	isometric(&line->x1, &line->y1, line->z1);
}

void	ft_transalation(t_fdf *data, t_line *line)
{
	line->x += data->shift_x;
	line->x1 += data->shift_x;
	line->y += data->shift_y;
	line->y1 += data->shift_y;
}
