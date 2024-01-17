/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:07:09 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/17 18:09:29 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "controls.h"

int	deal_key(int key, t_fdf *data)
{
	if (KEY_ESC == key)
	{
		free_all_ressources(data);
		exit(EXIT_SUCCESS);
	}
	if (KEY_LU == key)
		upper_z(data);
	else if (KEY_LL == key)
		lower_z(data);
	else if (KEY_LX == key || KEY_LY == key || KEY_LZ == key)
		rotation_x_y_z(data, key);
	else if (KEY_PLUS == key || KEY_MINUS == key || KEY_LM == key
		|| KEY_LP == key)
		zoom_in_out(data, key);
	else if (KEY_ARR_UP == key || KEY_ARR_DOWN == key || KEY_ARR_RIGHT == key
		|| KEY_ARR_LEFT == key)
		shift_x_y(data, key);
	else if (KEY_LR == key)
		ft_init_data(data);
	else if (KEY_LC == key)
		ft_centering(data);
	else if (KEY_LO == key || KEY_LT)
		projection_iso_para(data, key);
	ft_render(data);
	return (0);
}
