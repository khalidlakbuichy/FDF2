/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:52:14 by khalid            #+#    #+#             */
/*   Updated: 2024/01/11 11:33:05 by klakbuic         ###   ########.fr       */
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
    if (key == 108)
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
                    data->z_matrix[y][x].z -= 10;
                x++;
            }
            y++;
        } 
    }
    if (121 == key || 122 == key || 120 == key)
        rotation_x_y_z(data, key);
    if (112 == key || 109 == key)
        zoom_in_out(data, key);
    if (65362 == key || 65364 == key || 65363 == key || 65361 == key)
        shift_x_y(data, key);
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
        perror("enter enter only one parametr to the progtam !");
        return (EXIT_FAILURE);
    }
    data = (fdf *)malloc(sizeof(fdf));
    read_map(av[1], data);

    data->mlx.mlx_ptr = mlx_init();
    data->mlx.win = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT, "my FDF");
    data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr, &data->mlx.img.bpp, &data->mlx.img.line_length, &data->mlx.img.endian);
    data->zoom = 1.05;
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
