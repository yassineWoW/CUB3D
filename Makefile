CC = cc
CFLAGS = -Wall -Wextra -Werror -I/usr/local/include -fsanitize=address -g3
CFILES = 	cub3d.c mlx_init.c mlx_events.c map_initialization.c get_next_line.c get_next_line_utils.c \
			map_drawing.c init_player.c utils_2d.c utils_2d_1.c\

OFILES = ${CFILES:.c=.o}
NAME = cub3d
LIBFT = ./LIBFT/
LIBFT_NAME = LIBFT/libft.a
MlXFLAGS = -Lmlx -lmlx -L/usr/local/lib  -Imlx -lXext -lX11 -lm -lz

all: $(NAME)

${NAME} : ${OFILES}
	@ make -s -C $(LIBFT) && make clean -C  $(LIBFT)
	@ ${CC}	${CFLAGS}	${OFILES} $(LIBFT_NAME)	${MlXFLAGS} -o ${NAME}	

clean:
	@rm -rf ${OFILES}

fclean:
	@rm -rf $(NAME)
	@rm -rf ${OFILES}

re: fclean all

.PHONY:
	all fclean clean re

.SECONDARY : $(OFILES)