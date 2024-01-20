# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 10:42:54 by klakbuic          #+#    #+#              #
#    Updated: 2024/01/18 14:50:32 by klakbuic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/draw.c src/ft_isnbr.c src/init.c \
	  src/draw_utils.c src/get_next_line.c src/projections.c src/main.c \
	  src/roration.c src/deallocation.c src/ft_atoi_hex.c src/get_next_line_utils.c src/math.c src/read.c
OBJ = ${SRC:.c=.o}

SRCB = src/controls_bonus.c src/controls_utils_bonus.c src/mouse_bonus.c src/render_bonus.c src/main_bonus.c \
		src/draw.c src/ft_isnbr.c src/init.c \
	  src/draw_utils.c src/get_next_line.c src/projections.c \
	  src/roration.c src/deallocation.c src/ft_atoi_hex.c src/get_next_line_utils.c src/math.c src/read.c
OBJB = ${SRCB:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm
NAME = fdf
NAME_B = fdf_b
RM = rm -rf
LIBDIR = libs/libft/
LIB = $(LIBDIR)libft.a

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBDIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

bonus: $(NAME_B)

$(NAME_B): $(OBJB)
	make -C $(LIBDIR)
	$(CC) $(CFLAGS) $(OBJB) $(MLX) $(LIB) -o $(NAME_B)
clean:
	$(RM) $(OBJ) $(OBJB)
	make -C $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBDIR) fclean

re: fclean all
