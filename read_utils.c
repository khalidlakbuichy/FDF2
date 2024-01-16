/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:15:36 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/16 12:03:19 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_destroy(fdf *data)
{
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img.img_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx_ptr);
}

void	free_matrix(t_point **z_matrix)
{
	int	i;

	i = -1;
	if (NULL != z_matrix)
	{
		while (NULL != z_matrix[++i])
			free(z_matrix[i]);
		free(z_matrix);
	}
}

void	free_all_ressources(fdf *data)
{
	ft_mlx_destroy(data);
	free_matrix(data->z_matrix);
	free(data);
}

void	free_all_exit(fdf *data, const char *str)
{
	free_all_ressources(data);
	perror(str);
	exit(EXIT_FAILURE);
}