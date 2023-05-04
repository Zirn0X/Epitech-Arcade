##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Core Makefile
##

NAME	=	arcade

CFLAGS	=	-std=c++17 -Wall -Wextra -I ../../includes -I includes/

SRC = 	src/Main.cpp	\
		src/Core.cpp	\

all: $(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(SRC) -o $(NAME) $(CFLAGS) -ldl -fno-gnu-unique
			mv $(NAME) ../../

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)
		$(RM) src/*.o
		$(RM) ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
