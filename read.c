/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:18:52 by khalid            #+#    #+#             */
/*   Updated: 2024/01/07 17:53:34 by khalid           ###   ########.fr       */
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

ssize_t	get_width(char *line)
{
	size_t	width;
	char	**splited_line;

	splited_line = ft_split(line, ' ');
	width = 0;
	while (NULL != splited_line[width])
	{
		free(splited_line[width]);
		width++;
	}
	free(splited_line);
	return (width);
}

void	fill_matrix(t_point *z_line, char *line)
{
	int		i;
	char	**splited_line;
	char	**splited_values;
	char	*comma;

	i = 0;
	splited_line = ft_split(line, ' ');
	z_line = (t_point *)malloc(sizeof(t_point) * get_width(line) + 1);
	while (NULL != splited_line[i])
	{
        if (ft_strchr(splited_line[i], ','))
        {
            splited_values = ft_split(splited_line[i], ',');
            z_line->z = ft_atoi(splited_values[0]);
            z_line->color = ft_atoi_hex(splited_values[1]);
            free(splited_values[0]);
            free(splited_values[1]);
            free(splited_values);
        }
        else
        {
            z_line->z = ft_atoi(splited_values[0]);
            if (z_line->z !=0)
                z_line->color = 0x00d21f3c;
            z_line->color = 0xffffffff;
        }
		free(splited_line[i]);
		i++;
	}
	free(splited_line);
}

void	read_map(const char *file_name, fdf *data)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (-1 == fd)
		exit(1);
	data->heigth = get_heigth(file_name);
	data->z_matrix = (t_point **)malloc(sizeof(t_point *) * (data->heigth + 1));
	line = get_next_line(fd);
	i = 0;
	while (NULL != line)
	{
		fill_matrix(data->z_matrix[i], line);
	}
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

int main (int ac, char **av)
{
    return (0);
}