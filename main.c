/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:52:14 by khalid            #+#    #+#             */
/*   Updated: 2024/01/07 15:29:31 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int deal_key(int key, fdf *data)
{
    printf("%d\n", key);
    if (key == 65307)
        exit(0);
    if (key == 65451)
        data->zoom += 10;
    if (key == 65453)
        data->zoom -= 10;
    if (key == 65362)
        data->shift_y -= 10;
    if (key == 65364)
        data->shift_y += 10;
    if (key == 65363)
        data->shift_x += 10;
    if (key == 65361)
        data->shift_x -= 10;
    mlx_destroy_image(data->mlx_ptr, data->img->img);
    data->img->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bpp, &data->img->line_length, &data->img->endian);
    draw_map(data, data->img);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
    return (0);
}

int main (int ac, char **av)
{
    fdf* data;
    
    
    if (ac != 2)
    {
        return (1);
        // error
    }
    data = malloc(sizeof(fdf));
    data->img = malloc(sizeof(t_img));
    read_map(av[1], data);

    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "my FDF");

	data->img->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img, &data->img->bpp, &data->img->line_length, &data->img->endian);
    data->zoom = 20;
    data->shift_x = 150;
    data->shift_y = 150;
    draw_map(data, data->img);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img->img, 0, 0);
    mlx_key_hook(data->win_ptr, deal_key, data);
    mlx_loop(data->mlx_ptr);
}