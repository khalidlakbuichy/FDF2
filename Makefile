# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 10:42:54 by klakbuic          #+#    #+#              #
#    Updated: 2024/01/18 10:42:55 by klakbuic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = action.c color.c draw_line.c fdf.c ft_ftoi.c map_parsing.c map_utils.c projection.c projection_utils.c \
      reset.c utils.c help.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
NAME = fdf
CC = cc
RM = rm -rf
LIB = libft.a

all: $(NAME)

$(NAME): $(OBJ)
    make -C libft/
    $(CC) $(CFLAGS) $(OBJ) $(MLX) libft/$(LIB) -o fdf

.c.o:
    $(CC) $(CFLAGS) -c $<

clean:
    $(RM) $(OBJ)
    make -C libft/ clean

fclean: clean
    $(RM) $(NAME)
    make -C libft/ fclean

re: fclean all