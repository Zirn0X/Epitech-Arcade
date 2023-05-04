##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Snake Makefile
##

NAME	=	arcade_snake.so

CPPFLAGS	=	-iquote ./includes/

CFLAGS	=	-std=c++17 -Wall -Wextra -fPIC -shared -I ../../../includes/

SRC = 	src/Snake.cpp	\

OBJ = 	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): 
			$(CXX) $(SRC) -o $(NAME) -shared -fPIC $(CFLAGS) $(SDLFLAGS) -fno-gnu-unique
			mv $(NAME) ../../../lib

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)
		$(RM) ../../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
