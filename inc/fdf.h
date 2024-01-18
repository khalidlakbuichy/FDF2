/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 08:46:19 by khalid            #+#    #+#             */
/*   Updated: 2024/01/18 10:19:24 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080

# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdlib.h>
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
	int				z;
	unsigned int	color;
}					t_point;

typedef enum e_projection
{
	ISO,
	PARALLEL
}					t_projection;

typedef struct s_fdf
{
	int				width;
	int				heigth;
	t_point			**z_matrix;
	t_projection	view;
	float			zoom;
	int				shift_x;
	int				shift_y;
	float			tita;
	float			beta;
	float			meta;
	t_mlx			mlx;
}					t_fdf;

void				ft_init_zoom(t_fdf *data);
void				ft_init_data(t_fdf *data);
void				ft_init(t_fdf *data);
void				read_map(const char *filename, t_fdf *data);

#endif