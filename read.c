/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:18:52 by khalid            #+#    #+#             */
/*   Updated: 2024/01/09 17:36:07 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	get_heigth(const char *filename)
{
	ssize_t	fd;
	size_t	heigth;
	char	*line;

	fd = open(filename, O_RDONLY);
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

ssize_t	get_width(char **splited_line)
{
	size_t	width;

	width = 0;
	while (NULL != splited_line[width])
		width++;
	return (width);
}

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

t_point	*fill_matrix(char *line)
{
	int		i;
	char	**splited_line;
	char	**splited_values;
	t_point	*z_line;

	i = 0;
	splited_line = ft_split(line, ' ');
	z_line = (t_point *)malloc(sizeof(t_point) * (get_width(splited_line) + 1));
	while (NULL != splited_line[i])
	{
		z_line[i].z = ft_atoi(splited_line[i]);
		// printf("z: %d\n", z_line[i].z);
		if (NULL != ft_strchr(splited_line[i], ','))
		{
			splited_values = ft_split(splited_line[i], ',');
			z_line[i].color = ft_atoi_hex(splited_values[1]);
			// free(splited_values[0]);
			// free(splited_values[1]);
			// free(splited_values);
			free_mem(splited_values);
		}
		else
		{
			if (z_line[i].z != 0)
				z_line[i].color = 0x00d21f3c;
			z_line[i].color = 0xffffffff;
		}
		// printf("line[%d]: %d\n",i, z_line[i].z);
		// printf("z: %ld\n", z_line[i].color);
		// free(splited_line[i]);
		i++;
	}
	// int j = 0;
	// while (j < i)
	// {
	// 	puts("helo");
	// 	printf("z: %ld\n", z_line[j].color);
	// 	printf("z: %ld\n", z_line[j].z);
	// 	j++;
	// }
	// free(splited_line);
	// (z_line + i) = NULL;
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
		perror("Can't open the file"); /* of course I need to make it better */
		exit(1);
	}
	data->heigth = get_heigth(filename);
	// printf("height: %ld\n", data->heigth);
	data->z_matrix = (t_point **)malloc(sizeof(t_point *) * (data->heigth + 1));
	line = get_next_line(fd);
	data->width = get_width(ft_split(line, ' '));
	i = 0;
	while (NULL != line)
	{
		// printf("i: %d\n", i);
		data->z_matrix[i] = fill_matrix(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->z_matrix[i] = NULL;
	close(fd);
}
