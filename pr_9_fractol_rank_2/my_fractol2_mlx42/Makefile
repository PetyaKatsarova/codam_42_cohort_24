# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pekatsar <pekatsar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/02/04 11:27:44 by pekatsar      #+#    #+#                  #
#    Updated: 2025/02/06 12:29:02 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME     := fract-ol
CC       := cc
CFLAGS   := -Wextra -Wall -Werror -Wunreachable-code -Ofast -g

# Paths to MLX42 and libft
LIBMLX   := lib/MLX42
LIBFT    := lib/LIBFT

# Include paths
HEADERS  := -I ./include -I $(LIBMLX)/include -I $(LIBFT)

# Libraries to link
LIBS     := -L$(LIBMLX)/build -lmlx42 -L$(LIBFT) -lft -ldl -lglfw -pthread -lm

# Source and Object directories
SRCS     := $(shell find ./src -iname "*.c")
OBJDIR   := obj
OBJS     := $(patsubst ./src/%.c, $(OBJDIR)/%.o, $(SRCS))

all: libmlx libft $(NAME)

# Build libft
libft:
	@make -C $(LIBFT)

# Build MLX42
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
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "✅ Build successful!"

# Clean object files
clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT) clean

# Full cleanup
fclean: clean
	@rm -rf $(NAME) $(LIBMLX)/build
	@make -C $(LIBFT) fclean

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re libmlx libft
