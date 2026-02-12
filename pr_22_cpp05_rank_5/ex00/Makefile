NAME = Bureacrat
SRC = main.cpp Bureacrat.cpp

OBJ = $(SRC:.cpp=.o)
CXX = c++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
