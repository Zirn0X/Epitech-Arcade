##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## SFMLDisplay Makefile
##

NAME	=	arcade_sfml.so

SFML_FLAGS	=	-lsfml-system -lsfml-graphics -lsfml-window -I/opt/homebrew/Cellar/sfml/2.5.1_2/include -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib

CFLAGS	=	-std=c++17 -Wall -Wextra -fPIC -shared -I ../../../includes/ -I /opt/homebrew/Cellar/sfml/2.5.1_2/include -L /opt/homebrew/Cellar/sfml/2.5.1_2/lib

SRC = 	src/SFMLDisplay.cpp	\

all: $(NAME)

$(NAME):
			$(CXX) $(SRC) -o $(NAME) -shared -fPIC $(SFML_FLAGS) $(CFLAGS) -fno-gnu-unique
			mv $(NAME) ../../../lib

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)
		$(RM) src/*.o
		$(RM) ../../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
