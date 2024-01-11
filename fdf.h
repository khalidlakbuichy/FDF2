/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:46:19 by khalid            #+#    #+#             */
/*   Updated: 2024/01/11 09:27:34 by klakbuic         ###   ########.fr       */
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

# define MAX(a, b) (a > b ? a : b)
# define ABS(a) (a < 0 ? -a : a)

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

typedef struct s_line
{
	int				x;
	int				x1;
	int				y;
	int				y1;
	unsigned int	color;
}					t_line;

typedef struct s_fdf
{
	unsigned int	width;
	unsigned int	heigth;
	t_point			**z_matrix;
	int				zoom;
	int				shift_x;
	int				shift_y;
	float			tita;
	float			beta;
	float			meta;
	t_mlx			mlx;
}					fdf;

char				*get_next_line(int fd);
void				read_map(const char *filename, fdf *data);
// void				draw_line(fdf *data, float x, float y, float x1, float y1);
void				my_mlx_pixel_put(t_img *img, long x, long y, int color);
void				draw_map(fdf *data);
void				draw_line(fdf *data, t_line line);
void				x_rotation(int *y, int *z, float *tita);
void				y_rotation(int *x, int *z, float *beta);
void				z_rotation(int *x, int *y, float *meta);
void				one_point_perspective(int *x, int *y, int z);
void				isometric(int *x, int *y, int z);

long int			ft_atoi_hex(const char *hex);
#endif