##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Pacman Makefile
##a

NAME	=	arcade_nibbler.so

CPPFLAGS	=	-iquote ./includes/

CFLAGS	=	-std=c++17 -Wall -Wextra -fPIC -shared -I ../../../includes/

SRC = 	src/Nibbler.cpp	\

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
