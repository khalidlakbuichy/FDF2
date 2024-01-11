all:
	cc *.c libs/minilibx-linux/libmlx_Linux.a libs/libft/libft.a -lX11 -lXext -lm -lz
	
push:
	git add *
	git commit -m "automatic commit"
	git push