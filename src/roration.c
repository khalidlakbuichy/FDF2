/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roration.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 08:57:06 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:12:14 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	x_rotation(int *y, int *z, float *tita)
{
	int	original_y;

	original_y = *y;
	*y = original_y * cos(*tita) + *z * sin(*tita);
	*z = -original_y * sin(*tita) + *z * cos(*tita);
}

void	y_rotation(int *x, int *z, float *beta)
{
	int	original_x;

	original_x = *x;
	*x = original_x * cos(*beta) + *z * sin(*beta);
	*z = -original_x * sin(*beta) + *z * cos(*beta);
}

void	z_rotation(int *x, int *y, float *meta)
{
	int	original_x;
	int	original_y;

	original_x = *x;
	original_y = *y;
	*x = original_x * cos(*meta) - original_y * sin(*meta);
	*y = original_x * sin(*meta) + original_y * cos(*meta);
}
