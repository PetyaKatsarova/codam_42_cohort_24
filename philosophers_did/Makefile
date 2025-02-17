NAME 	= philo

# Configuration
CFLAGS	= -Wall -Werror -Wextra -I ./include -pthread #-fsanitize=thread -g
RM		= rm -rf
SRCDIR	= src/
OBJDIR	= obj/
HEADER	= ./include/philo.h
PHILO = philo

# Colors
RESET = \033[0m
RED=\033[0;31m
PURPLE=\033[45m
CORAL=\033[38;2;255;127;80m

# Source Files
SRCFILES =	main.c \
			input_check.c input_init.c \
			table_setting.c dinner.c \
			utils_free.c utils_print.c utils_time.c \
			utils_locks.c utils_updates.c \
			monitor_death.c \

SRCOBJ	= $(SRCFILES:%.c=$(OBJDIR)%.o)

.PHONY: all clean fclean re

# Objectives
all: $(PHILO)

$(PHILO): $(SRCOBJ)
	cc $(CFLAGS) $(SRCOBJ) -o $(PHILO)
	@echo "\n$(PURPLE)✨ Compilation for Philosophers done ✨ $(RESET)\n"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p obj
	@cc -c $(CFLAGS) -o $@ $<

# Cleaning
clean:
	$(RM) $(SRCOBJ)
	$(RM) -r $(OBJDIR)
	@echo "\n$(CORAL)🧹    Removed all .o files and its directory   🧹$(RESET)"

fclean: clean
	@$(RM) $(PHILO)
	@echo "$(RED) 🗑️     Cleaned up remaining files   🗑️$(RESET)\n"

re: fclean all