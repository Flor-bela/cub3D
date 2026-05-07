NAME = cub3D

CC = cc
FLAGS = -Wall -Werror -Wextra -g

LFT	= libft/libft.a
INC	= -I./libft
LIB	= -L./libft -lft

SOURCES =	main.c \
			check_file.c \
			error_utils.c \
			read_file.c
OBJ_DIR = obj
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

all: $(LFT) $(NAME)

$(NAME): $(OBJECTS) 
	$(CC) $(FLAGS)  $^ -o $@ $(LIB)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(LFT):
	@make -C libft

clean:
	rm -rf $(OBJ_DIR)
	@make -s $@ -C libft

fclean: clean
	rm -f $(NAME)
	@make -s $@ -C libft

re: fclean all

.PHONY: all clean fclean re