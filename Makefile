NAME = cub3D

CC = cc
FLAGS = -Wall -Wextra -Werror -g -O3

MLX_DIR = minilibx-linux
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX = $(MLX_DIR)/libmlx.a

LFT = libft/libft.a

INC = -I./libft -I./minilibx-linux

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SOURCES =	main.c \
			check_file.c \
			check_file_utils.c \
			error_utils.c \
			get_next_line.c \
			init.c \
			utils.c \
			parse_color.c \
			parse_texture.c \
			parse_map_chars.c \
			parse_map_walls.c \
			debug.c \
			frames_per_second.c \
			start_game.c \
			game_loop.c \
			game_loop_utils.c \
			game_destroy.c \
			player_direction.c \
			move_player.c \
			cast_ray.c \
			cast_ray_utils.c \
			move_player_utils.c
			
SOURCES_BONUS = bonus/minimap.c \
				bonus/minimap_utils.c\
				bonus/move_mouse.c

OBJ_DIR = obj
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

OBJECTS_BONUS = $(SOURCES_BONUS:%.c=$(OBJ_DIR)/%.o)

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

bonus: FLAGS += -DBONUS=1 -DPLAYER_RADIUS=10
bonus: fclean $(MLX) $(LFT) $(OBJECTS) $(OBJECTS_BONUS)
	$(CC) $(FLAGS) $(OBJECTS) $(OBJECTS_BONUS) $(LFT) $(MLX_FLAGS) -o $(NAME)

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

.PHONY: all bonus clean fclean re