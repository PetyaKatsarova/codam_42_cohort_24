NAME = fractol

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
SEGFAULT_FLAG = -fsanitize=address
RM = rm -rf

SRC_PATH = src/
OBJ_PATH = objs/
SRC =  $(wildcard $(SRC_PATH)*.c)
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

BREW = "/Users/$(USER)/.brew/opt/glfw/lib/"
INC = -I includes/libft -I ./includes -I ./includes/MLX42/include/MLX42
MLX = includes/MLX42/libmlx42.a
LIBFT = includes/libft/libft.a
LDFLAGS=-L/usr/lib -lglfw -lm

#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

all: mlx libft $(NAME)

$(NAME): $(OBJ)
	@ gcc $(FLAGS) $(OBJ) $(LIBFT) $(MLX) -lglfw -L $(BREW) -o $(NAME) $(LDFLAGS)
	@ echo "\n\t\t$(GREEN)$(BOLD)----Fract'ol compiled----\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@ mkdir -p  $(OBJ_PATH)
	@ $(CC) $(FLAGS) $(INC) -c $< -o $@

libft:
	@ make -C includes/libft/

mlx:
	@make -C includes/MLX42/

re: fclean all

clean:
	@ $(RM) -r $(OBJ_PATH)
	@ make -C includes/libft/ clean
	@ echo "\n\t\t\t$(RED)$(BOLD)Cleaning...\n"

fclean: clean
	@ $(RM) $(NAME)
	@ make -C includes/libft/ fclean
	@ make -C includes/MLX42/ fclean

.PHONY: all libft mlx re clean fclean