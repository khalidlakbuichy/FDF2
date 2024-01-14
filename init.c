/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:44:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/14 17:55:51 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_menu(fdf *data)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = data->mlx.mlx_ptr;
	win = data->mlx.win;
	mlx_string_put(mlx, win, 65, y += 20, 0xffffffff, "How to Use ?");
	mlx_string_put(mlx, win, 15, y += 35, 0xffffffff, "Zoom:");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Move:");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "Arrows key");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "x: for X-Axis");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "y: for Y-Axis");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "z: fro Z-Axis");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Projection");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "Isometric: i key");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "one point view: o Key");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Reset: r Key");
}

void	ft_render(fdf *data)
{
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img.img_ptr);
	data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr,
			&data->mlx.img.bpp, &data->mlx.img.line_length,
			&data->mlx.img.endian);
	draw_map(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win,
		data->mlx.img.img_ptr, 0, 0);
	print_menu(data);
}

void	isometric_centering(fdf *data)
{
	int	center_x;
	int	center_y;
	int	center_z;

	center_x = (data->width * data->zoom) / 2;
	center_y = (data->heigth * data->zoom)  / 2;
	center_z = 0;
	isometric(&center_x, &center_y, center_z);
	data->shift_x = (WIDTH / 2) - center_x;
	data->shift_y = (HEIGHT / 2)- center_y;
}

void	ft_init_data(fdf *data)
{
	if (data->width < 20)
		data->zoom = 30;
	else
		data->zoom = 1;
	data->view = ISO;
	isometric_centering(data);
	data->tita = 0;
	data->meta = 0;
	data->beta = 0;
}

void	ft_init(fdf *data)
{
	data->mlx.mlx_ptr = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT,
			"wireframe model");
	data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr,
			&data->mlx.img.bpp, &data->mlx.img.line_length,
			&data->mlx.img.endian);
	ft_init_data(data);
}
