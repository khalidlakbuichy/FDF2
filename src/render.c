/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:30:05 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:17:59 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"
#include "../inc/draw.h"

void	print_menu(t_fdf *data)
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
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "Parallel: t key");
	mlx_string_put(mlx, win, 57, y += 25, 0xffffffff, "one point view: o Key");
	mlx_string_put(mlx, win, 15, y += 30, 0xffffffff, "Reset: r Key");
}

void	ft_render(t_fdf *data)
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
