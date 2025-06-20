# Makefile for zombieHorde project

NAME      = zombieHorde
SRC       = main.cpp Zombie.cpp ZombieHorde.cpp
OBJ       = $(SRC:.cpp=.o)
CXX       = c++
CXXFLAGS  = -Wall -Wextra -Werror -g

.PHONY: all memory clean fclean re

all: $(NAME)

# Link step: rebuild when .o or Makefile changes (Makefile is order-only)
$(NAME): $(OBJ) | Makefile
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp to .o, and recompile when Makefile changes
%.o: %.cpp Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run under Valgrind for memory checks
memory: $(NAME)
	@valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
