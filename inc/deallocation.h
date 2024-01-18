/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deallocation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:17:29 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:18:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEALLOCATION_H
# define DEALLOCATION_H

# include "fdf.h"

int		free_double_ptr(char **memory);
void	ft_mlx_destroy(t_fdf *data);
void	free_matrix(t_point **z_matrix);
void	free_all_ressources(t_fdf *data);
void	free_all_exit(t_fdf *data, char *str);

#endif