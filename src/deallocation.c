/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:15:36 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:05:57 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	free_double_ptr(char **memory)
{
	int	i;

	i = 0;
	if (NULL != memory)
	{
		while (NULL != memory[i])
			free(memory[i++]);
		free(memory);
	}
	return (1);
}

void	ft_mlx_destroy(t_fdf *data)
{
	mlx_destroy_image(data->mlx.mlx_ptr, data->mlx.img.img_ptr);
	mlx_destroy_window(data->mlx.mlx_ptr, data->mlx.win);
	mlx_destroy_display(data->mlx.mlx_ptr);
	free(data->mlx.mlx_ptr);
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

void	free_all_ressources(t_fdf *data)
{
	ft_mlx_destroy(data);
	free_matrix(data->z_matrix);
	free(data);
}

void	free_all_exit(t_fdf *data, char *str)
{
	free_all_ressources(data);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
