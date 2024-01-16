/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:44:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/16 09:13:14 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "fdf.h"

void	mlx_fail(fdf *data)
{
	free(data);
	perror(ERR_MLX);
	exit(EXIT_FAILURE);
}
void	ft_init_data(fdf *data)
{
	/* the zoom condition need an improvemnt !*/
	if (data->width < 20)
		data->zoom = 30;
	else
		data->zoom = 1;
	data->view = ISO;
	ft_centering(data);
	data->tita = 0;
	data->meta = 0;
	data->beta = 0;
}

void	ft_init(fdf *data)
{
	ft_bzero(data, sizeof(fdf));
	data->mlx.mlx_ptr = mlx_init();
	if (NULL == data->mlx.mlx_ptr)
		mlx_fail(data);
	data->mlx.win = mlx_new_window(data->mlx.mlx_ptr, WIDTH, HEIGHT,
			"wireframe model (FDF)");
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
