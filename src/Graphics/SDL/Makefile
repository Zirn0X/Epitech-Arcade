##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## SDLDisplay Makefile
##a

NAME	=	arcade_sdl2.so

SDLFLAGS	=	`sdl2-config --cflags --libs` -lSDL2_ttf

CPPFLAGS	=	-iquote ./includes/

CFLAGS	=	-std=c++17 -Wall -Wextra -fPIC -shared -I ../../../includes/ -I /opt/homebrew/Cellar/sdl2/2.26.4/include/ -L/opt/homebrew/Cellar/sdl2/2.26.4/lib/

SRC = 	src/SDLDisplay.cpp	\

all: $(NAME)

$(NAME):
			$(CXX) $(SRC) -o $(NAME) -shared -fPIC $(CFLAGS) $(SDLFLAGS) -g3 -fno-gnu-unique
			mv $(NAME) ../../../lib

clean:
		$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)
		$(RM) src/*.o
		$(RM) ../../../lib/$(NAME)

re: fclean all

.PHONY: all clean fclean re
