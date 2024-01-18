/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:44:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:11:14 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/draw.h"
#include "../inc/errors.h"
#include "../inc/fdf.h"

void	ft_init_zoom(t_fdf *data)
{
	if (0 == data->width)
		return ;
	if (data->width < 20)
		data->zoom = 50;
	else if (data->width < 50)
		data->zoom = 40;
	else if (data->width < 100)
		data->zoom = 30;
	else
		data->zoom = 2;
}

static void	mlx_fail(t_fdf *data)
{
	free(data);
	ft_putendl_fd(ERR_MLX, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	ft_init_data(t_fdf *data)
{
	data->view = ISO;
	data->tita = 0;
	data->meta = 0;
	data->beta = 0;
	ft_init_zoom(data);
	ft_centering(data);
}

void	ft_init(t_fdf *data)
{
	ft_bzero(data, sizeof(t_fdf));
	data->mlx.mlx_ptr = mlx_init();
	if (NULL == data->mlx.mlx_ptr)
		mlx_fail(data);
	data->mlx.win = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT,
			"wireframe model (fdf)");
	if (NULL == data->mlx.win)
	{
		mlx_destroy_display(data->mlx.mlx_ptr);
		mlx_fail(data);
	}
	data->mlx.img.img_ptr = mlx_new_image(data->mlx.mlx_ptr, WIDTH, HEIGHT);
	if (NULL == data->mlx.img.img_ptr)
	{
		mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win);
		mlx_destroy_display(data->mlx.mlx_ptr);
		mlx_fail(data);
	}
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img_ptr,
			&data->mlx.img.bpp, &data->mlx.img.line_length,
			&data->mlx.img.endian);
	ft_init_data(data);
}
