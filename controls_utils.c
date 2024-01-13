/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:07:09 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/13 10:24:30 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

int	deal_key(int key, fdf *data)
{
	unsigned	x;
	unsigned	y;
	unsigned	x;
	unsigned	y;

	printf("%d\n", key);
	if (key == 65307)
		exit(0);
	if (KEY_LU == key || KEY_LL == key)
		upper_lower_z(data, key);
	if (KEY_LX == key || KEY_LY == key || KEY_LZ == key)
		rotation_x_y_z(data, key);
	if (KEY_PLUS == key || KEY_MINUS == key)
		zoom_in_out(data, key);
	if (KEY_ARR_UP == key || KEY_ARR_DOWN == key || KEY_ARR_RIGHT == key
		|| KEY_ARR_LEFT == key)
		shift_x_y(data, key);
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img.img_ptr);
	data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr,
			&data->mlx.img.bpp, &data->mlx.img.line_length,
			&data->mlx.img.endian);
	draw_map(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win,
		data->mlx.img.img_ptr, 0, 0);
	return (0);
}
