/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:18:52 by khalid            #+#    #+#             */
/*   Updated: 2024/01/18 10:18:59 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/deallocation.h"
#include "../inc/errors.h"
#include "../inc/fdf.h"
#include "../inc/utils.h"
#include "../inc/draw.h"

static void	set_width_height(t_fdf *data, const char *filename)
{
	ssize_t	fd;
	size_t	heigth;
	size_t	width;
	char	*line;
	char	**splited_line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	splited_line = ft_split(line, ' ');
	width = 0;
	while (NULL != splited_line[width] && '\n' != splited_line[width][0])
		width++;
	free_double_ptr(splited_line);
	heigth = 0;
	while (NULL != line)
	{
		heigth++;
		free(line);
		line = get_next_line(fd);
	}
	data->width = width;
	data->heigth = heigth;
	close(fd);
}

static int	fill_matrix_color(t_point *z_line, char *splited_line)
{
	char	**splited_values;

	if (NULL != ft_strchr(splited_line, ','))
	{
		splited_values = ft_split(splited_line, ',');
		if (NULL == splited_values)
			return (-1);
		z_line->color = ft_atoi_hex(splited_values[1]);
		if (!ft_isnbr(splited_values[0]) || !ft_ishex(splited_values[1]))
			return (free_double_ptr(splited_values), -1);
		free_double_ptr(splited_values);
	}
	else
	{
		if (!ft_isnbr(splited_line))
			return (-1);
		z_line->color = 0xffffffff;
		if (0 != z_line->z)
			z_line->color = 0xffda012d;
	}
	return (1);
}

static int	fill_matrix(t_point *z_line, char *line)
{
	int		i;
	char	**splited_line;

	splited_line = ft_split(line, ' ');
	if (NULL == splited_line)
		return (-1);
	i = 0;
	while (NULL != splited_line[i] && '\n' != splited_line[i][0])
	{
		z_line[i].z = ft_atoi(splited_line[i]);
		if (-1 == fill_matrix_color(&z_line[i], splited_line[i]))
		{
			free_double_ptr(splited_line);
			return (-1);
		}
		i++;
	}
	free_double_ptr(splited_line);
	return (1);
}

static void	matrix_allocation(t_fdf *data, ssize_t fd)
{
	int		i;
	char	*line;

	i = -1;
	while (++i < data->heigth)
	{
		data->z_matrix[i] = (t_point *)malloc(sizeof(t_point) * (data->width));
		if (NULL == data->z_matrix[i])
			free_all_exit(data, ERR_MEM);
	}
	line = get_next_line(fd);
	i = 0;
	while (NULL != line)
	{
		if (-1 == fill_matrix(data->z_matrix[i], line))
		{
			free(line);
			free_all_exit(data, ERR_FILE);
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->z_matrix[i] = NULL;
}

void	read_map(const char *filename, t_fdf *data)
{
	ssize_t	fd;

	fd = open(filename, O_RDONLY);
	if (-1 == fd)
		free_all_exit(data, ERR_OPEN);
	set_width_height(data, filename);
	ft_init_zoom(data);
	ft_centering(data);
	if (0 == data->heigth)
		free_all_exit(data, ERR_FILE);
	data->z_matrix = (t_point **)malloc(sizeof(t_point *) * (data->heigth + 1));
	if (NULL == data->z_matrix)
		free_all_exit(data, ERR_MEM);
	ft_bzero(data->z_matrix, (sizeof(t_point *) * (data->heigth + 1)));
	matrix_allocation(data, fd);
	close(fd);
}
