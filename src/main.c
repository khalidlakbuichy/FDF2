/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:52:14 by khalid            #+#    #+#             */
/*   Updated: 2024/01/18 10:17:17 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/controls.h"
#include "../inc/fdf.h"
#include "../inc/deallocation.h"
#include "../inc/errors.h"
#include "../inc/draw.h"

int	ft_close(t_fdf *data)
{
	free_all_ressources(data);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_fdf	*data;

	if (ac != 2)
	{
		ft_putendl_fd(ERR_ARGS, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	data = (t_fdf *)malloc(sizeof(t_fdf));
	if (NULL == data)
	{
		ft_putendl_fd(ERR_MEM, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_init(data);
	read_map(av[1], data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win,
		data->mlx.img.img_ptr, 0, 0);
	print_menu(data);
	mlx_key_hook(data->mlx.win, deal_key, data);
	mlx_mouse_hook(data->mlx.win, deal_mouse, data);
	mlx_hook(data->mlx.win, 17, 0, ft_close, data);
	mlx_loop(data->mlx.mlx_ptr);
}
