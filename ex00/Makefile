NAME = a.out
CC = c++
CFLAGS = -Wall -Wextra -Werror
ADFLAG = -std=c++98
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
DBJ = $(SRC:.cpp=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(ADFLAG) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(ADFLAG) -c $< -o $@

clean:
	rm -f $(OBJ) $(DBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DBJ)

.PHONY: all clean fclean re