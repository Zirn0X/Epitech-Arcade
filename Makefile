##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Core Makefile
##

SRC_CORE =	src/Core

SRC_SFML =	src/Graphics/SFML

SRC_NCURSES =	src/Graphics/NCurses

SRC_SDL =	src/Graphics/SDL

SRC_SNAKE =	src/Games/Snake

SRC_PACMAN =	src/Games/Pacman

SRC_NIBBLER	=	src/Games/Nibbler
SRC_MENU	=	src/Games/Menu

OBJ = 	$(SRC:.cpp=.o)

all:
	make re -C $(SRC_CORE)
	make re -C $(SRC_SFML)
	make re -C $(SRC_NCURSES)
	make re -C $(SRC_SDL)
	make re -C $(SRC_SNAKE)
	make re -C $(SRC_PACMAN)
	make re -C $(SRC_NIBBLER)
	make re -C $(SRC_MENU)

core:
	make re -C $(SRC_CORE)

games:
		make re -C $(SRC_SNAKE)
		make re -C $(SRC_PACMAN)
		make re -C $(SRC_NIBBLER)
		make re -C $(SRC_MENU)

graphicals:
			make re -C $(SRC_SFML)
			make re -C $(SRC_NCURSES)
			make re -C $(SRC_SDL)

clean:
		make clean -C $(SRC_CORE)
		make clean -C $(SRC_SFML)
		make clean -C $(SRC_NCURSES)
		make clean -C $(SRC_SDL)
		make clean -C $(SRC_SNAKE)
		make clean -C $(SRC_PACMAN)
		make clean -C $(SRC_NIBBLER)
		make clean -C $(SRC_MENU)

fclean:	clean
		make fclean -C $(SRC_CORE)
		make fclean -C $(SRC_SFML)
		make fclean -C $(SRC_NCURSES)
		make fclean -C $(SRC_SDL)
		make fclean -C $(SRC_SNAKE)
		make fclean -C $(SRC_PACMAN)
		make fclean -C $(SRC_NIBBLER)
		make fclean -C $(SRC_MENU)

re: fclean all

.PHONY: all clean fclean re
