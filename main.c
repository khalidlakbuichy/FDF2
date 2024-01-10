/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:52:14 by khalid            #+#    #+#             */
/*   Updated: 2024/01/10 15:40:04 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int deal_key(int key, fdf *data)
{
    printf("%d\n", key);
    if (key == 65307)
        exit(0);
    if (key == 117)
    {
        unsigned x;
        unsigned y;
        y = 0;
        while (y < data->heigth)
        {
            x = 0;
            while (x < data->width)
            {
                if (data->z_matrix[y][x].z != 0)
                    data->z_matrix[y][x].z += 10;
                x++;
            }
            y++;
        }
    }
    if (key == 121)
        data->beta += 0.25;
    if (key == 122)
        data->meta += 0.25;
    if (key == 120)
        data->tita += 0.25;
    if (key == 65451)
        data->zoom += 2;
    if (key == 65453)
        data->zoom -= 2;
    if (key == 65362)
        data->shift_y -= 10;
    if (key == 65364)
        data->shift_y += 10;
    if (key == 65363)
        data->shift_x += 10;
    if (key == 65361)
        data->shift_x -= 10;
    mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img.img_ptr);
    data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr, &data->mlx.img.bpp, &data->mlx.img.line_length, &data->mlx.img.endian);
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win, data->mlx.img.img_ptr, 0, 0);
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
    data = (fdf *)malloc(sizeof(fdf));
    read_map(av[1], data);

    data->mlx.mlx_ptr = mlx_init();
    data->mlx.win = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT, "my FDF");
    data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr, &data->mlx.img.bpp, &data->mlx.img.line_length, &data->mlx.img.endian);
    data->zoom = 1;
    data->shift_x = 0;
    data->shift_y = 0;
    data->tita = 0;
    data->meta = 0;
    data->beta = 0;

    draw_map(data);
    my_mlx_pixel_put(&data->mlx.img, 1000 + (WIDTH /2), 1000 + (HEIGHT /2), 0xffffffff);
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win, data->mlx.img.img_ptr, 0, 0);
    mlx_key_hook(data->mlx.win, deal_key, data);
    mlx_loop(data->mlx.mlx_ptr);
}