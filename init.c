/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:44:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/13 14:41:11 by klakbuic         ###   ########.fr       */
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
	mlx_string_put(mlx, win, 65, y += 20, 0xffffffff, "How to Use");
	mlx_string_put(mlx, win, 15, y += 35, 0xffffffff, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Flatten: </>");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "X-Axis - 2/8");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "Y-Axis - 4/6");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "Z-Axis - 1(3)/7(9)");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Projection");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "ISO: I Key");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "Parallel: P Key");
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

void	ft_init_data(fdf *data)
{
	data->zoom = 10;
	data->shift_x = (WIDTH / 2) - (data->width / 2);
	data->shift_y = (HEIGHT / 2) - (data->heigth / 2);
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
