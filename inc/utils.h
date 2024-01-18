/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 09:47:12 by klakbuic          #+#    #+#             */
/*   Updated: 2024/01/18 10:03:33 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char		*get_next_line(int fd);
long int	ft_atoi_hex(const char *hex);
int			ft_isnbr(const char *str);
int			ft_ishex(const char *str);
int			ft_max(int a, int b);

#endif