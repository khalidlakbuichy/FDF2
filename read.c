/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:18:52 by khalid            #+#    #+#             */
/*   Updated: 2024/01/16 10:43:41 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "fdf.h"

int	free_mem(char **memory)
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

int	fill_matrix(t_point *z_line, char *line)
{
	int		i;
	char	**splited_line;
	char	**splited_values;

	i = 0;
	splited_line = ft_split(line, ' ');
	if (NULL == splited_line)
		return (-1);
	while (NULL != splited_line[i])
	{
		z_line[i].z = ft_atoi(splited_line[i]);
		if (NULL != ft_strchr(splited_line[i], ','))
		{
			splited_values = ft_split(splited_line[i], ',');
			if (NULL == splited_values)
			{
				free_mem(splited_line);
				return (-1);
			}
			z_line[i].color = ft_atoi_hex(splited_values[1]);
			printf("narii: %ld\n", splited_values[1]);
			printf("is nbr: %ld\n", ft_isnbr(splited_values[0]));
			printf("is hex: %ld\n", ft_ishex_nbr(splited_values[1]));
			if (!ft_isnbr(splited_values[0])
				|| !ft_ishex_nbr(splited_values[1]))
			{
				puts("khasni ndkhol hna");
				free_mem(splited_line);
				free_mem(splited_values);
				return (-1);
			}
		}
		else
		{
			z_line[i].color = 0xffffffff;
			if (!ft_isnbr(splited_line[i]))
			{
				free_mem(splited_line);
				return (-1);
			}
		}
		i++;
	}
	free_mem(splited_line);
	return (1);
}

void	read_map(const char *filename, fdf *data)
{
	ssize_t	fd;
	int		i;
	int		is_err;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (-1 == fd)
	{
		free_all_exit(data, ERR_OPEN);
		// ft_mlx_destroy(data);
		// free(data);
		// perror(ERR_OPEN);
		// exit(EXIT_FAILURE);
	}
	set_width_height(data, filename);
	if (0 == data->heigth)
	{
		free_all_exit(data, ERR_FILE);
		// ft_mlx_destroy(data);
		// free(data);
		// perror(ERR_FILE);
		// exit(EXIT_FAILURE);
	}
	data->z_matrix = (t_point **)malloc(sizeof(t_point *) * (data->heigth + 1));
	// printf("hei: %d\n", data->heigth);
	for (int i = 0; i < (data->heigth + 1); i++)
		printf( "addr: %p\n", *(data->z_matrix + i));
	if (NULL == data->z_matrix)
	{
		free_all_exit(data, ERR_MEM);
		// ft_mlx_destroy(data);
		// free(data);
		// perror(ERR_MEM);
		// exit(EXIT_FAILURE);
	}
	printf("matrix: %p\n", data->z_matrix[0]);
	ft_bzero(*(data->z_matrix), (sizeof(t_point *) * (data->heigth + 1)));
	printf("%ld   bytes:----------------------------------------\n", (sizeof(t_point *) * (data->heigth + 1)));
	// for (int i = 0; i < data->heigth; i++)
	// 	printf("matrix: %p\n", *(data->z_matrix)[i]);

	// printf("heigth: %d\n", data->heigth + 1);
	i = -1;
	while (++i <= data->heigth)
	{
		printf("i: %d\n", i);
		data->z_matrix[i] = (t_point *)malloc(sizeof(t_point) * (data->width));
		puts("test");
		if (NULL == data->z_matrix[i])
		{
			free_all_exit(data, ERR_MEM);
			// free_matrix(data->z_matrix, i);
			// ft_mlx_destroy(data);
			// free(data);
			// perror(ERR_MEM);
			// exit(EXIT_FAILURE);
		}
	}
	line = get_next_line(fd);
	i = -1;
	while (NULL != line)
	{
		if (-1 == fill_matrix(data->z_matrix[++i], line))
		{
			free(line);
			free_all_exit(data, ERR_FILE);
			// free_ressources(data);
			// perror(ERR_FILE);
			// exit(EXIT_FAILURE);
		}
		line = get_next_line(fd);
	}
	data->z_matrix[i] = NULL;
	close(fd);

	for (int y = 0; y < data->heigth; y++)
	{
		for (int x = 0; x < data->width; x++)
			printf("%3d", data->z_matrix[y][x]);
		puts("");
	}
}
