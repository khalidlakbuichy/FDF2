/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:52:14 by khalid            #+#    #+#             */
/*   Updated: 2024/01/13 10:08:44 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"


int main (int ac, char **av)
{
    fdf* data;
    
    
    if (ac != 2)
    {
        perror("enter enter only one parametr to the progtam !");
        return (EXIT_FAILURE);
    }
    data = (fdf *)malloc(sizeof(fdf));
    read_map(av[1], data);

    data->mlx.mlx_ptr = mlx_init();
    data->mlx.win = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT, "my FDF");
    data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr, &data->mlx.img.bpp, &data->mlx.img.line_length, &data->mlx.img.endian);
    data->zoom = 15;
    data->shift_x = WIDTH / 2;
    data->shift_y = HEIGHT / 2;
    data->tita = 0;
    data->meta = 0;
    data->beta = 0;
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win, data->mlx.img.img_ptr, 0, 0);
    mlx_string_put(data->mlx.mlx_ptr, data->mlx.win, 100, 100, 0xffffffff, "Hello from BTS");
    mlx_key_hook(data->mlx.win, deal_key, data);
    mlx_loop(data->mlx.mlx_ptr);
}
