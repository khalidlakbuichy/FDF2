/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:46:19 by khalid            #+#    #+#             */
/*   Updated: 2024/01/15 08:34:44 by klakbuic         ###   ########.fr       */
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

typedef struct s_line
{
	int				x;
	int				x1;
	int				y;
	int				y1;
	int				z;
	int				z1;
	unsigned int	color;
}					t_line;

typedef enum
{
	ISO,
	PARALLEL
}					projection;

typedef struct s_fdf
{
	unsigned int	width;
	unsigned int	heigth;
	t_point			**z_matrix;
	projection		view;
	double			zoom;
	int				shift_x;
	int				shift_y;
	float			tita;
	float			beta;
	float			meta;
	t_mlx			mlx;
}					fdf;

typedef struct s_dda
{
	int				dx;
	int				dy;
	int				steps;
	float			xinc;
	float			yinc;
	float			x;
	float			y;
}					t_dda;

char				*get_next_line(int fd);
void				read_map(const char *filename, fdf *data);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				draw_map(fdf *data);
void				draw_line(fdf *data, t_line line);
void				x_rotation(int *y, int *z, float *tita);
void				y_rotation(int *x, int *z, float *beta);
void				z_rotation(int *x, int *y, float *meta);
void				one_point_perspective(int *x, int *y, int z);
void				isometric(int *x, int *y, int z);
int					ft_max(int a, int b);
void				ft_rotation(fdf *data, t_line *line);
void				ft_zoom(fdf *data, t_line *line);
void				ft_isometric(t_line *line);
void				ft_transalation(fdf *data, t_line *line);
void				rotation_x_y_z(fdf *data, int key);
void				shift_x_y(fdf *data, int key);
void				rotation_x_y_z(fdf *data, int key);
long int			ft_atoi_hex(const char *hex);
int					deal_key(int key, fdf *data);
void				upper_lower_z(fdf *data, int key);
void				zoom_in_out(fdf *data, int key);
void				ft_init(fdf *data);
int					deal_mouse(int button, int x, int y, fdf *data);
void				ft_render(fdf *data);
void				ft_init_data(fdf *data);
void				center_object(fdf *data);
void				ft_one_point_perspective(t_line *line);
void				isometric_centering(fdf *data);
void				cabinet(int *x, int *y, int z);
void				ft_cabinet(t_line *line);
void				ft_parallel(fdf *data, t_line *line);

#endif