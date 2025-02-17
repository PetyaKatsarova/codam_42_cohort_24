# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: diwalaku <diwalaku@codam.student.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/01/16 17:27:03 by diwalaku      #+#    #+#                  #
#    Updated: 2025/01/16 17:38:50 by diwalaku      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		= phonebook

# Configuration
CC			= c++
CPP_FLAGS	= -Wall -Werror -Wextra
CPP_FLAGS	+= -std=c++98
RM			= rm -rf
# Source Files
SRC			= main.cpp Contact.cpp PhoneBook.cpp

# Object Files and Directories
OBJDIR		= obj
OBJ			= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))

# Objectives
all:	$(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) $(CPP_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
		@mkdir -p $(OBJDIR)
		$(CC) $(CPP_FLAGS) -c -o $@ $^

# Cleaning
clean:
		$(RM) $(OBJDIR)

fclean: clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re