/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:46:19 by khalid            #+#    #+#             */
/*   Updated: 2024/01/10 09:02:19 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080

# include "libs/libft/libft.h"
# include "libs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win;
	t_img			img;
}					t_mlx;

typedef struct s_point
{
	unsigned int	z;
	unsigned int	color;
}					t_point;

typedef struct s_fdf
{
	unsigned int	width;
	unsigned int	heigth;
	t_point			**z_matrix;
	int				zoom;
	int				color;
	int				shift_x;
	int				shift_y;

	t_mlx			mlx;
}					fdf;

char				*get_next_line(int fd);
void				read_map(const char *filename, fdf *data);
void				draw_line(fdf *data, float x, float y, float x1, float y1);
void				my_mlx_pixel_put(t_img *img, long x, long y, int color);
void				draw_map(fdf *data);
void				DDA(fdf *data, unsigned int color, int X0, int Y0, int X1,
						int Y1);
long int			ft_atoi_hex(const char *hex);
#endif