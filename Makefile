# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: klakbuic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 10:21:40 by klakbuic          #+#    #+#              #
#    Updated: 2024/01/18 10:22:11 by klakbuic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Werror -Wextra -Wall -Lminilibx_linux -Lmlx_linux -lX11 -lXext -lm
NAME = fdf
SRCS = 
OBJDIR = obj
OBJS = 
LIBS = minilibx_linux/libmlx.a

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@make -C libft/ all
	@make -C minilibx_linux/ all
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	@make -C libft/ clean
	@make -C minilibx_linux/ clean
	rm -rf $(OBJDIR)

fclean: clean
	@make -C libft/ fclean
	@make -C minilibx_linux/ fclean
	rm -rf $(NAME)

re: fclean all