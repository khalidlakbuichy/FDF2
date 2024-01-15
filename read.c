/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:18:52 by khalid            #+#    #+#             */
/*   Updated: 2024/01/15 11:07:39 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "fdf.h"

void	free_mem(char **memory)
{
	int	i;

	i = 0;
	if (NULL != memory)
	{
		while (NULL != memory[i])
			free(memory[i++]);
		free(memory);
	}
}

void	set_width_height(fdf *data, const char *filename)
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
	while (NULL != splited_line[width])
		width++;
	free_mem(splited_line);
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

void	fill_matrix(t_point *z_line, char *line)
{
	int		i;
	char	**splited_line;
	char	**splited_values;

	i = 0;
	splited_line = ft_split(line, ' ');
	while (NULL != splited_line[i])
	{
		z_line[i].z = ft_atoi(splited_line[i]);
		if (NULL != ft_strchr(splited_line[i], ','))
		{
			splited_values = ft_split(splited_line[i], ',');
			if (!ft_isnbr(splited_values[0]))
			{
				perror("Wrong file format !!");
				exit(EXIT_FAILURE);
			}
			z_line[i].color = ft_atoi_hex(splited_values[1]);
			free_mem(splited_values);
		}
		else
		{
			if (!ft_isnbr(splited_line[0]))
			{
				perror("Wrong file format !!");
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
	free_mem(splited_line);
	return (z_line);
}

void	read_map(const char *filename, fdf *data)
{
	ssize_t	fd;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (-1 == fd)
	{
		perror(ERR_OPEN);
		exit(EXIT_FAILURE);
	}
	set_width_height(data, filename);
	data->z_matrix = (t_point **)malloc(sizeof(t_point *) * (data->heigth + 1));
	i = -1;
	while (++i <= data->heigth)
		data->z_matrix[i] = (t_point *)malloc(sizeof(t_point) * (data->width));
	line = get_next_line(fd);
	i = 0;
	while (NULL != line)
	{
		fill_matrix(data->z_matrix[i],line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->z_matrix[i] = NULL;
	close(fd);
}
