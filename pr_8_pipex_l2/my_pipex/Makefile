NAME = pipex
LIBFT = libft.a
LIBFT_PATH = ./libft

CC = cc
# valgrind --leak-check=full ./pipex lucky.txt "ls -l" 2 2
# valgrind --leak-check=full --track-origins=yes ./pipex lucky.txt "ls -l" 2 2

CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
LIB = ar rcs

SOURCES = main.c \
		parsing_path.c \
		helpers.c \
		file_and_pipe.c \
		parse_quotes.c \

OBJDIR = objects
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

# Rule to compile source files into the objects directory
$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_PATH)

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_PATH)/$(LIBFT)

clean:
	@make clean -C $(LIBFT_PATH)
	$(RM) $(OBJECTS)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
# TODO: MAKE always runs gcc even if already all built and no changes..

test1: pipex scripts/my_tests1.sh
	@chmod +x scripts/my_tests1.sh
	@./scripts/my_tests1.sh

test: pipex scripts/script.sh
	@chmod +x scripts/script.sh
	@./scripts/script.sh

test_memory:
	# @valgrind --leak-check=full --track-origins=yes ./pipex texts/test_input.txt "grep a" "wc -w" output_file.txt
	@valgrind --leak-check=full --track-origins=yes ./pipex texts/test_input.txt "grep a" "head -n 3" output_file.txt
