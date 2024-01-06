/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:50:44 by khalid            #+#    #+#             */
/*   Updated: 2024/01/06 09:35:00 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_heigth(const char *file_name)
{
	ssize_t	fd;
	size_t	heigth;
	char	*line;

	fd = open(file_name, O_RDONLY);
	heigth = 0;
	line = get_next_line(fd);
	while (NULL != line)
	{
		heigth++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (heigth);
}

ssize_t	get_width(const char *file_name)
{
	ssize_t	fd;
	size_t	width;
	char	*line;
	char	**splited_line;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	splited_line = ft_split(line, ' ');
	width = 0;
	while (NULL != splited_line[width])
	{
		free(splited_line[width]);
		width++;
	}
	free(line);
	free(splited_line);
	close(fd);
	return (width);
}

void	fill_matrix(int *z_line, char *line)
{
	int		i;
	char	**splited_line;

	i = 0;
	splited_line = ft_split(line, ' ');
	while (NULL != splited_line[i])
	{
		z_line[i] = ft_atoi(splited_line[i]);
		free(splited_line[i]);
		i++;
	}
	free(splited_line);
}

void	read_map(const char *file_name, fdf *data)
{
	int fd;
	int i;
	char *line;

	data->width = get_width(file_name);
	data->heigth = get_heigth(file_name);
	data->z_matrix = (int **)malloc(sizeof(int *) * (data->heigth + 1));
	i = 0;
	while (i <= data->heigth)
		data->z_matrix[i++] = (int *)malloc(sizeof(int) * (data->width + 1));
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (NULL != line)
	{
		fill_matrix(data->z_matrix[i], line);
		free(line);
        line = get_next_line(fd);
		i++;
	}
    close(fd);
    data->z_matrix[i] = NULL;
}
