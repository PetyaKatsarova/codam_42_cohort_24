
NAME      = brain
SRC       = main.cpp
OBJ       = $(SRC:.cpp=.o)
CXX       = c++
CXXFLAGS  = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJ) | Makefile
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

memory: $(NAME)
	@valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all memory clean fclean re
