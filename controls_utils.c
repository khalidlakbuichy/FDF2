/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 10:07:09 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/15 08:36:17 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keys.h"

int	deal_key(int key, fdf *data)
{
	printf("%d\n", key);
	if (key == 65307)
		exit(0);
	if (KEY_LU == key || KEY_LL == key)
		upper_lower_z(data, key);
	if (KEY_LX == key || KEY_LY == key || KEY_LZ == key)
		rotation_x_y_z(data, key);
	if (KEY_PLUS == key || KEY_MINUS == key || KEY_LM == key)
		zoom_in_out(data, key);
	if (KEY_ARR_UP == key || KEY_ARR_DOWN == key || KEY_ARR_RIGHT == key
		|| KEY_ARR_LEFT == key)
		shift_x_y(data, key);
	if (KEY_LR == key)
		ft_init_data(data);
	if (KEY_LC == key)
		isometric_centering(data);
	if (KEY_LT == key)
		data->view = PARALLEL;
	if (KEY_LO == key)
		data->view = ISO;
	ft_render(data);
	return (0);
}
