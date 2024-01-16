/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:46:19 by khalid            #+#    #+#             */
/*   Updated: 2024/01/16 17:42:38 by klakbuic         ###   ########.fr       */
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

typedef enum e_projection
{
	ISO,
	PARALLEL
}					t_projection;

typedef struct s_fdf
{
	unsigned int	width;
	unsigned int	heigth;
	t_point			**z_matrix;
	t_projection	view;
	double			zoom;
	int				shift_x;
	int				shift_y;
	float			tita;
	float			beta;
	float			meta;
	t_mlx			mlx;
}					t_fdf ;

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
void				read_map(const char *filename, t_fdf *data);
void				my_mlx_pixel_put(t_img *img, int x, int y, int color);
void				draw_map(t_fdf *data);
void				draw_line(t_fdf *data, t_line line);
void				x_rotation(int *y, int *z, float *tita);
void				y_rotation(int *x, int *z, float *beta);
void				z_rotation(int *x, int *y, float *meta);
void				isometric(int *x, int *y, int z);
int					ft_max(int a, int b);
void				ft_rotation(t_fdf *data, t_line *line);
void				ft_zoom(t_fdf *data, t_line *line);
void				ft_isometric(t_line *line);
void				ft_transalation(t_fdf *data, t_line *line);
void				rotation_x_y_z(t_fdf *data, int key);
void				shift_x_y(t_fdf *data, int key);
void				rotation_x_y_z(t_fdf *data, int key);
long int			ft_atoi_hex(const char *hex);
int					deal_key(int key, t_fdf *data);
void				upper_lower_z(t_fdf *data, int key);
void				zoom_in_out(t_fdf *data, int key);
void				ft_init(t_fdf *data);
int					deal_mouse(int button, int x, int y, t_fdf *data);
void				ft_render(t_fdf *data);
void				ft_init_data(t_fdf *data);
void				isometric_centering(t_fdf *data);
void				projection_iso_para(t_fdf *data, int key);
void				ft_centering(t_fdf *data);
int					ft_isnbr(const char *str);
void				print_menu(t_fdf *data);
void				ft_mlx_destroy(t_fdf *data);
void				free_all_exit(t_fdf *data, const char *str);
void				free_all_ressources(t_fdf *data);
void				free_matrix(t_point **z_matrix);
void				ft_mlx_destroy(t_fdf *data);
int					ft_ishex(const char *str);
int					free_double_ptr(char **memory);
void				ft_init_zoom(t_fdf *data);

#endif