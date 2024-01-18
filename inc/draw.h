/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:36:54 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:20:02 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "fdf.h"

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

void				ft_centering(t_fdf *data);
void				isometric(int *x, int *y, int z);
void				ft_rotation(t_fdf *data, t_line *line);
void				z_rotation(int *x, int *y, float *meta);
void				y_rotation(int *x, int *z, float *beta);
void				x_rotation(int *y, int *z, float *tita);
void				ft_zoom(t_fdf *data, t_line *line);
void				ft_isometric(t_line *line);
void				ft_transalation(t_fdf *data, t_line *line);
void				print_menu(t_fdf *data);
void				ft_render(t_fdf *data);
void				draw_map(t_fdf *data);

#endif