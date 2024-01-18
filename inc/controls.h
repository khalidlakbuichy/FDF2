/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:55:15 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:04:55 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "fdf.h"
# include "keys.h"
# define MAX_ZOOM_IN 100
# define MAX_ZOOM_OUT 1

void	projection_iso_para(t_fdf *data, int key);
void	zoom_in_out(t_fdf *data, int key);
void	shift_x_y(t_fdf *data, int key);
void	rotation_x_y_z(t_fdf *data, int key);
int		deal_key(int key, t_fdf *data);
int		deal_mouse(int button, int x, int y, t_fdf *data);
float	lerp(float a, float b, float t);

#endif
