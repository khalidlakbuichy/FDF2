/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:18:52 by khalid            #+#    #+#             */
/*   Updated: 2024/01/15 10:57:19 by klakbuic         ###   ########.fr       */
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

ssize_t	get_width(char **splited_line)
{
	size_t	width;

	width = 0;
	while (NULL != splited_line[width])
		width++;
	return (width);
}


t_point	*fill_matrix(char *line)
{
	int		i;
	char	**splited_line;
	char	**splited_values;
	t_point	*z_line;

	i = 0;
	splited_line = ft_split(line, ' ');
	z_line = (t_point *)malloc(sizeof(t_point) * get_width(splited_line));
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
			if (!ft_isnbr(splited_line[i]))
			{
				printf("this is the error |%s|\n", splited_line[i]);
				perror("Wrong file format !!");
				exit(EXIT_FAILURE);
			}
			if (z_line[i].z != 0)
				z_line[i].color = 0x00d21f3c;
			else
				z_line[i].color = 0xffffffff;
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
	line = get_next_line(fd);
	data->width = get_width(ft_split(line, ' '));
	i = 0;
	while (NULL != line)
	{
		data->z_matrix[i] = fill_matrix(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->z_matrix[i] = NULL;
	close(fd);
}
