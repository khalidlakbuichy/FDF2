CC = cc
CFLAGS = -Werror -Wextra -Wall -Lminilibx_linux -Lmlx_linux -lX11 -lXext
NAME = graphics
SRCS = $(wildcard src/*.c) #Be carful
OBJDIR = obj
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))
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