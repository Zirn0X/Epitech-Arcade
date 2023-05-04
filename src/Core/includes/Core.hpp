/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Core
*/

#ifndef CORE_HPP
    #define CORE_HPP
    #include <map>
    #include "IObject.hpp"
    #include "IGraphics.hpp"
    #include "IGames.hpp"
    #include "DLLoader.hpp"

namespace arcade {
    class Core {
        public:
            Core(int ac, char *argv[]);
            ~Core() {
                try {
                    std::remove("./assets/pseudo.txt");
                } catch (Error &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            void run();
        private:
            bool getAllLibraryAvailable();
            void getCurrentLibrayToDisplay(std::string);
            void changeGameLibrary(arcade::Input);
            void changeGraphicLibrary(arcade::Input);
            bool gameLoop();
            void getMenuSelector(arcade::IText *tile);
            void getPseudo();
            std::map<std::string, std::string> gameSelector = {
                {"Game_Snake", "./lib/arcade_snake.so"},
                {"Game_Pacman", "./lib/arcade_pacman.so"},
                {"Game_Nibbler", "./lib/arcade_nibbler.so"},
            };

            std::map<std::string, std::string> graphicSelector = {
                {"Lib_Sfml", "./lib/arcade_sfml.so"},
                {"Lib_Sdl", "./lib/arcade_sdl2.so"},
                {"Lib_Ncurse", "./lib/arcade_ncurses.so"},
            };
        protected:
            DLLoader<arcade::IGames> game_lib;
            DLLoader<arcade::IGraphics> graphic_lib;
            std::vector<std::string> games_lib;
            std::vector<std::string> graphics_libs;
            int current_game = 0;
            int current_graphics = 0;
            bool isMenu = true;
    };
} // namespace arcad
 

#endif
