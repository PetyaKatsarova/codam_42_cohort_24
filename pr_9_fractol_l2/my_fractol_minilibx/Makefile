# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pekatsar <pekatsar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/02/04 11:27:44 by pekatsar      #+#    #+#                  #
#    Updated: 2025/02/13 09:23:13 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME     := fract-ol
CC       := cc
CFLAGS   := -Wextra -Wall -Werror -Wunreachable-code -Ofast -g

LIBMLX   := lib/minilibx-linux
LIBFT    := lib/LIBFT

# Include paths
HEADERS  := -I ./include -I $(LIBMLX)/include -I $(LIBFT)

# Libraries to link
# LIBS = -L/path/to/minilibx -lmlx -lXext -lX11

LIBS     := -L$(LIBMLX) -lmlx -L$(LIBFT) -lft -lXext -lX11 -lm -pthread

# LIBS     := -L$(LIBMLX)/build -lmlx42 -L$(LIBFT) -lft -ldl -lglfw -pthread -lm 

SRCS     := $(shell find ./src -iname "*.c")
OBJDIR   := obj
OBJS     := $(patsubst ./src/%.c, $(OBJDIR)/%.o, $(SRCS))

all: libmlx libft $(NAME)

libft:
	@make -C $(LIBFT)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then echo "Error: minilibx not found at $(LIBMLX)"; exit 1; fi
	@make -C $(LIBMLX)


# Compile object files
$(OBJDIR)/%.o: ./src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && printf "Compiling: $(notdir $<)\n"

# Create obj directory if it doesn't exist
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Build successful!"

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME) $(LIBMLX)/build
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re libmlx libft
