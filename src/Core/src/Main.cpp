/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Main 
*/

#include "Exception.hpp"
#include "Core.hpp"

int main(int ac, char **argv) {
    try {
        arcade::Core game(ac, argv);
        game.run();
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
