##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## NCurses Makefile
##

NAME	=	arcade_ncurses.so

CPPFLAGS	=	-iquote ./includes/

CFLAGS	=	-std=c++17 -Wall -Wextra -fPIC -shared -lncurses -I ../../../includes/

SRC = 	src/NCursesDisplay.cpp	\

all: $(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(SRC) -o $(NAME) -shared -fPIC $(CFLAGS) -fno-gnu-unique
			mv $(NAME) ../../../lib

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)
		$(RM) src/*.o
		$(RM) ../../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
