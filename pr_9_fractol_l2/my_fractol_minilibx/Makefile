# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pekatsar <pekatsar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/02/04 11:27:44 by pekatsar      #+#    #+#                  #
#    Updated: 2025/02/15 15:55:52 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME     := fract-ol
CC       := cc
CFLAGS   := -Wextra -Wall -Werror -Wunreachable-code -g
#CFLAGS   := -Wextra -Wall -Werror -Wunreachable-code -Ofast -g

LIBMLX   := lib/minilibx-linux
LIBFT    := lib/LIBFT

# Include paths
HEADERS  := -I ./include -I $(LIBMLX)/include -I $(LIBFT)

LIBS     := -L$(LIBMLX) -lmlx -L$(LIBFT) -lft -lXext -lX11 -lm -pthread

SRCS     := src/hooks.c \
			src/init.c \
			src/input_checks.c \
			src/input_utils.c \
			src/mandel.c \
			src/julia.c \
			src/tricorn.c \
			src/phoenix.c \
			src/utils.c \
			src/main.c

OBJDIR   := obj
OBJS     := $(patsubst ./src/%.c, $(OBJDIR)/%.o, $(SRCS))

all: libmlx libft $(NAME)

libft:
	@make -C $(LIBFT)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then echo "Error: minilibx not found at $(LIBMLX)"; exit 1; fi
	@make -C $(LIBMLX)

$(OBJDIR)/%.o: ./src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)\n"

# Create obj dir if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Build successful!"

test_valgrind_mandel:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fract-ol mandelbrot

test_valgrind_juls:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fract-ol julia
	
clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME) $(LIBMLX)/build
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
