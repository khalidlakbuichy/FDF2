/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:44:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/13 18:17:57 by klakbuic         ###   ########.fr       */
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

	// Calculate the center of the object in the isometrically transformed space
	center_x = data->width / 2;
	center_y = data->heigth / 2;
	int center_z = 0; // Assuming the object is centered along the z-axis
	// Apply isometric projection to the center
	isometric(&center_x, &center_y, center_z);
	// Calculate the centering shift values
	data->shift_x = (WIDTH - center_x) / 2;
	data->shift_y = (HEIGHT - center_y) / 2;
}

void	ft_init_data(fdf *data)
{
	data->zoom = 1;
	isometric_centering(data);
    data->shift_x = (WIDTH - data->width) / 2;
	data->shift_y = (HEIGHT - data->heigth) / 2;
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
