# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pekatsar <pekatsar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/02/04 11:27:44 by pekatsar      #+#    #+#                  #
#    Updated: 2025/02/04 16:26:29 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	:= fract-ol
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= lib/MLX42

# Correct MLX42 header path
HEADERS	:= -I ./include -I $(LIBMLX)/includes

# Correct MLX42 library path
LIBS	:= -L$(LIBMLX)/build -lmlx42 -ldl -lglfw -pthread -lm

# Source and Object directories
SRCS	:= $(shell find ./src -iname "*.c")
OBJDIR	:= obj
OBJS	:= $(patsubst ./src/%.c, $(OBJDIR)/%.o, $(SRCS))

all: libmlx $(NAME)

# Build MLX42 Library
libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then echo "Error: MLX42 not found at $(LIBMLX)"; exit 1; fi
	@cmake -B $(LIBMLX)/build -S $(LIBMLX) && make -C $(LIBMLX)/build -j4

# Compile object files
$(OBJDIR)/%.o: ./src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)\n"

# Create obj directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Build final executable
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

# Clean object files
clean:
	@rm -rf $(OBJDIR)

# Full cleanup
fclean: clean
	@rm -rf $(NAME) $(LIBMLX)/build

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re libmlx
