# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pekatsar <pekatsar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2025/06/11 14:55:21 by pekatsar      #+#    #+#                  #
#    Updated: 2025/06/11 15:49:11 by pekatsar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME    := megaphone
SRC     := megaphone.cpp
CXX     := g++
CXXFLAGS:= -std=c++11 -Wall -Wextra -Werror -O2

all: $(NAME)

$(NAME): $(SRC) Makefile
	$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re

bla: clean