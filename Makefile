NAME = cub3D

CC = cc
FLAGS =  -Wall -Wextra -Werror -g

MLX_DIR = minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX = $(MLX_DIR)/libmlx.a

LFT = libft/libft.a

INC = -I./libft -I./minilibx-linux

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SOURCES =	main.c \
			check_file.c \
			error_utils.c \
			read_file.c \
			init.c \
			utils.c \
			parse_color.c \
			parse_texture.c \
			parse_map.c \
			debug.c \
			start_game.c \
			handle_input.c \
			game_destroy.c \
			player_direction.c \
			

OBJ_DIR = obj
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(MLX) $(LFT) $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $^ $(LFT) $(MLX_FLAGS) -o $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

$(LFT):
	@echo " [ .. ] | Compiling libft.."
	@make -s -C libft
	@echo " [ OK ] | Libft ready!"

clean:
	rm -rf $(OBJ_DIR)
	@make -s clean -C libft
	@if [ -d "$(MLX_DIR)" ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean: clean
	rm -f $(NAME)
	@make -s fclean -C libft

re: fclean all

.PHONY: all clean fclean re