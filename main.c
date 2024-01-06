/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:52:14 by khalid            #+#    #+#             */
/*   Updated: 2024/01/06 11:19:14 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int deal_key(int key, fdf *data)
{
    printf("%d\n", key);
    if (key = 65362)
        data->shift_y += 10;
    if (key = 65364)
        data->shift_y -= 10;
    if (key = 65363)
        data->shift_x += 10;
    if (key = 65361)
        data->shift_x -= 10;
    draw_map(data, NULL);
    return (0);
}

int main (int ac, char **av)
{
    fdf* data;
    t_data *img;
    
    if (ac != 2)
    {
        return (1);
        // error
    }
    data = malloc(sizeof(data));
    img = malloc(sizeof(img));
    read_map(av[1], data);

    data->mlx_ptr = mlx_init();
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "my FDF");

	// img->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	// img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
    data->zoom = 20;
    data->shift_x = 0;
    data->shift_y = 0;
    draw_map(data, NULL);
    mlx_key_hook(data->win_ptr, deal_key, data);
    mlx_loop(data->mlx_ptr);
}