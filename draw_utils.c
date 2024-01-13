/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 08:55:37 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/13 18:39:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_rotation(fdf *data, t_line *line)
{
	x_rotation(&line->y, &line->z, &data->tita);
	x_rotation(&line->y1, &line->z1, &data->tita);
	y_rotation(&line->x, &line->z, &data->beta);
	y_rotation(&line->x1, &line->z1, &data->beta);
	z_rotation(&line->x, &line->y, &data->meta);
	z_rotation(&line->x1, &line->y1, &data->meta);
}

void	ft_zoom(fdf *data, t_line *line)
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

void ft_one_point_perspective(t_line *line)
{
	one_point_perspective(&line->x, &line->y, line->z);
	one_point_perspective(&line->x1, &line->y1, line->z1);
}
void isometric_centering(fdf *data) 
{
    // Calculate the center of the object in the isometrically transformed space
    int center_x = data->width / 2;
    int center_y = data->heigth / 2;
    int center_z = 0;  // Assuming the object is centered along the z-axis

    // Apply isometric projection to the center
    isometric(&center_x, &center_y, center_z);

    // Calculate the centering shift values
    data->shift_x = (WIDTH - center_x * 2) / 2;
    data->shift_y = (HEIGHT - center_y * 2) / 2;
}

void	ft_transalation(fdf *data, t_line *line)
{
	// isometric_centering(data);
	printf("shift_x: %u\n", data->shift_x);
	printf("shift_y: %u\n", data->shift_y);
	line->x += data->shift_x;
	line->x1 += data->shift_x;
	line->y += data->shift_y;
	line->y1 += data->shift_y;
}
