NAME = ScalarConverter
SRC = main.cpp ValidationHelper.cpp ScalarConverter.cpp

OBJ = $(SRC:.cpp=.o)
CXX = c++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
