# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pekatsar <pekatsar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/01/25 18:02:36 by pekatsar      #+#    #+#                  #
#    Updated: 2025/01/25 18:02:36 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC = helpers.c \
		parse_path.c \
		parse_command.c \
		file_and_pipe.c \
		main.c \
		ft_split.c\
		ft_strjoin.c\
		ft_strlen.c\
		ft_strdup.c\
		ft_strnstr.c\
		ft_substr.c\
		ft_putstr_fd.c\
		ft_calloc.c\
		ft_strlcpy.c\
		ft_memset.c\
		ft_putendl_fd.c\

OBJ = $(SRC:.c=.o)
INC = -I ./includes/
NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re


test1: pipex scripts/my_tests1.sh
	@chmod +x scripts/my_tests1.sh
	@./scripts/my_tests1.sh

test: pipex scripts/script.sh
	@chmod +x scripts/script.sh
	@./scripts/script.sh

test_memory:
	# @valgrind --leak-check=full --track-origins=yes ./pipex texts/test_input.txt "grep a" "wc -w" output_file.txt
	@valgrind --leak-check=full --track-origins=yes ./pipex texts/test_input.txt "grep a" "head -n 3" output_file.txt
