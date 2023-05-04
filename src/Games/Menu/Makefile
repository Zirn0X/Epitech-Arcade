##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Pacman Makefile
##a

NAME	=	arcade_menu.so

CFLAGS	=	-std=c++17 -Wall -Wextra -fPIC -shared -I ../../../includes/

CXXFLAGS = 	-g3 -fno-gnu-unique

SRC = 	src/Menu.cpp	\

OBJ = 	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME):
			$(CXX) $(SRC) -o $(NAME) -shared -fPIC $(CFLAGS) $(CXXFLAGS)
			mv $(NAME) ../../../lib

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)
		$(RM) ../../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
