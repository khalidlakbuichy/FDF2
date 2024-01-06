/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:46:19 by khalid            #+#    #+#             */
/*   Updated: 2024/01/06 11:09:25 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 800
# define HEIGHT 800

# include "libs/libft/libft.h"
# include "libs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_fdf
{
	unsigned int	width;
	unsigned int	heigth;
	int				**z_matrix;
	int				zoom;
	int				color;
	int				shift_x;
	int				shift_y;

	void			*mlx_ptr;
	void			*win_ptr;
}					fdf;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_data;

char				*get_next_line(int fd);
void				read_map(const char *file_name, fdf *data);
void				drawLine(t_data *img, int x0, int y0, int x1, int y1);
void				my_mlx_pixel_put(t_data *img, int x, int y, int color);
void				draw_map(fdf *data, t_data *img);
#endif