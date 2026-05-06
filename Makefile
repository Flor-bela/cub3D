NAME = cub3D

SOURCES = \
		main.c\
		parsing_map.c\
		free_all_gnl.c\
		get_next_line.c\



OBJ_DIR = obj
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -Wall -Werror -Wextra -g
CC = cc

all: $(NAME)

$(LIBFT):
		make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re