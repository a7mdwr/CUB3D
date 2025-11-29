NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx
MLX         = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SRCDIR      = src
SRC_EXE     = $(SRCDIR)/execution
SRC_PARC    = $(SRCDIR)/parsing

SRCS =	main.c error.c \
		$(SRC_EXE)/configur_mlx.c \
		$(SRC_EXE)/utils.c \
		$(SRC_EXE)/game_loop.c \
		$(SRC_EXE)/configur_player.c \
		$(SRC_EXE)/render_scene.c \
		$(SRC_EXE)/exec.c \
		$(SRC_EXE)/render_helper.c \
		$(SRC_PARC)/parse.c \
		$(SRC_PARC)/check_map.c \
		$(SRC_PARC)/fill_info.c \
		$(SRC_PARC)/parsing_utils.c \
		$(SRC_PARC)/normalize.c \
		$(SRC_PARC)/check_files.c \
		$(SRC_PARC)/color_parsing.c\
		$(SRC_PARC)/parsing_utils2.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) mlx $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX) -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all