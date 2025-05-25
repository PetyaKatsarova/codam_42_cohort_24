NAME    := philo
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -pthread -g -fsanitize=thread
HEADERS := -I ./include
SRCS    := main.c \
			ft_atoi.c \
			initiation.c \
			philo_routine.c \

OBJDIR  := objs
OBJS    := $(SRCS:.c=.o)
OBJS    := $(addprefix $(OBJDIR)/, $(notdir $(OBJS)))

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME) && echo "Build complete"

$(OBJDIR)/%.o: %.c Makefile | $(OBJDIR)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

bla: clean
