CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address 

# Source files
SRCS = mandatory/cub3d.c mandatory/mlx_init.c mandatory/mlx_events.c mandatory/mlx_events1.c mandatory/mlx_events2.c mandatory/map_drawing.c mandatory/init_player.c \
       mandatory/init_player2.c mandatory/ft_free.c mandatory/parse_cub.c \
       get_next_line/get_next_line.c mandatory/textures.c mandatory/raycasting_utils.c\
       get_next_line/get_next_line_utils.c mandatory/raycasting_utils1.c mandatory/raycasting_utils2.c \
	   mandatory/raycasting_utils3.c mandatory/map_drawing2.c mandatory/parsing_utils00.c \
	   mandatory/parsing_utils01.c  mandatory/parsing_utils03.c mandatory/parsing_utils02.c \
	   mandatory/parsing_utils05.c mandatory/parsing_utils04.c mandatory/parsing_utils06.c \
	   mandatory/parsing_utils07.c  mandatory/parsing_utils08.c mandatory/parsing_utils09.c \

SRCS_BONUS = bonus/cub3d_bonus.c bonus/mlx_init_bonus.c bonus/mlx_events_bonus.c bonus/mlx_events1_bonus.c bonus/mlx_events2_bonus.c bonus/map_drawing_bonus.c bonus/init_player_bonus.c \
       bonus/init_player2_bonus.c bonus/ft_free_bonus.c bonus/parse_cub_bonus.c bonus/minimap_bonus.c bonus/minimap2_bonus.c \
       get_next_line/get_next_line.c bonus/textures_bonus.c bonus/raycasting_utils_bonus.c bonus/door_handler_bonus.c\
       get_next_line/get_next_line_utils.c bonus/raycasting_utils1_bonus.c bonus/raycasting_utils2_bonus.c \
	   bonus/ft_malloc_bonus.c bonus/animation_bonus.c bonus/raycasting_utils3_bonus.c bonus/animation_bonus1.c \
	   bonus/animation_bonus2.c bonus/map_drawing1_bonus.c bonus/mlx_events4_bonus.c bonus/mlx_events3_bonus.c bonus/raycasting_utils4_bonus.c \
	   bonus/parsing_utils03.c bonus/parsing_utils00.c  bonus/parsing_utils01.c bonus/parsing_utils02.c \
	   bonus/parsing_utils04.c  bonus/parsing_utils05.c bonus/parsing_utils06.c  bonus/parsing_utils07.c  \
	   bonus/parsing_utils08.c  bonus/parsing_utils09.c 
	     

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
# Header file that all .o files depend on
HEADER = mandatory/cub3d.h
HEADER_B = bonus/cub3d_bonus.h

# Target executable
NAME = cub3d
NAME_BONUS = cub3d_bonus

# Library paths and flags
LIBFT = ./LIBFT/
LIBFT_NAME = LIBFT/libft.a
MlXFLAGS = -Lmlx -lmlx -L/usr/local/lib -Imlx -lXext -lX11 -lm
CUB3D_DEP_OBJS = $(OBJS)
CUB3D_DEP_OBJS_B = $(OBJS_BONUS)
# Default target
all: $(NAME)

bonus : $(NAME_BONUS)

# Rule to build the final executable
$(NAME): $(OBJS)
	@make -s -C $(LIBFT) && make clean -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_NAME) $(MlXFLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS)
	@make -s -C $(LIBFT) && make clean -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT_NAME) $(MlXFLAGS) -o $(NAME_BONUS)

# Rule to compile .c files into .o files
# All .o files depend on the header file
$(CUB3D_DEP_OBJS): $(HEADER)
$(CUB3D_DEP_OBJS_B) : $(HEADER_B) 
# Clean up build files
clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)

# Clean up everything
fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)

# Rebuild the project
re: fclean all

re_bonus: fclean bonus

.SECONDARY : $(OBJS)

.PHONY: all fclean clean re