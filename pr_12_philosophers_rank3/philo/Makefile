
NAME    := philo
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -pthread -O3

ifdef DEBUGMEM
	CFLAGS += -g -fsanitize=address
endif
ifdef DEBUGTTHREAD
	CFLAGS += -g -fsanitize=thread
endif

HEADERS := -I ./include
SRCS    := main.c \
			ft_atoi.c \
			initiation.c \
			philo_routine.c \
			philo_routine_helper.c \
			monitor_routine.c \
			cleanup_all.c \
			utils.c \
			print_write.c \

OBJDIR  := objs
OBJS    := $(SRCS:.c=.o)
OBJS    := $(addprefix $(OBJDIR)/, $(notdir $(OBJS)))

all: $(NAME)

debugmem:
	$(MAKE) fclean
	$(MAKE) DEBUGMEM=1

debugthread:
	$(MAKE) fclean
	$(MAKE) DEBUGTTHREAD=1


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

mem_check:
	$(MAKE) fclean
	$(MAKE) CFLAGS="-Wall -Wextra -Werror -pthread -g -fsanitize=address" all
	ASAN_OPTIONS=detect_leaks=1 ./$(NAME) 5 800 200 200 7

.PHONY: all clean fclean re

