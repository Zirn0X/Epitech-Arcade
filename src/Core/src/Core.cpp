/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Core Core
*/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Core.hpp"
#include "Object/Text.hpp"

arcade::Core::Core(int ac, char *argv[]) {
    if (ac != 2)
        throw Error("Error: Not enough arguments. Try: ./arcade <lib.so>");
    getAllLibraryAvailable();
    getCurrentLibrayToDisplay(argv[1]);
    graphic_lib.setInstance(graphics_libs[current_graphics]);
    game_lib.setInstance(games_lib[current_game]);
}

void arcade::Core::getPseudo() {
    std::string input = "";

    while (input.empty()) {
        std::cout << "Username : ";
        std::getline(std::cin, input);
    }
    std::ofstream myfile;
    try {
        myfile.open ("./assets/pseudo.txt");
        myfile << input;
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
    }
    myfile.close();
}

void arcade::Core::run() {
    this->getPseudo();
    if (!this->gameLoop()) {
        graphic_lib.unload();
        game_lib.unload();
    }
}

bool arcade::Core::gameLoop() {
    while (true) {
        arcade::Input graphic_input = graphic_lib.getInstance()->event();
        auto objects = game_lib.getInstance()->loop(graphic_input);
        if (graphic_input == arcade::Input::EXIT)
            break;
        if ((graphic_input == arcade::Input::NEXTGRAPH || graphic_input == arcade::Input::PREVIOUSGRAPH) && !isMenu) {
            objects.clear();
            this->changeGraphicLibrary(graphic_input);
        }
        if ((graphic_input == arcade::Input::NEXTGAME || graphic_input == arcade::Input::PREVIOUSGAME) && !isMenu) {
            objects.clear();
            this->changeGameLibrary(graphic_input);
        }

        if (graphic_input == arcade::Input::NEXTGRAPH && objects.size() == 2 && isMenu) {
            for (auto object : objects) {
                if (dynamic_cast<arcade::IText *>(object.get()) != nullptr)
                    getMenuSelector(dynamic_cast<arcade::IText *>(object.get()));
            }
            objects.clear();
            this->graphic_lib.unload();
            this->graphic_lib.setInstance(graphics_libs[this->current_graphics]);
            this->game_lib.unload();
            this->game_lib.setInstance(games_lib[this->current_game]);
            isMenu = false;
        }

        if (graphic_input == arcade::Input::MENU && !isMenu) {
            objects.clear();
            this->current_game = 0;
            this->game_lib.unload();
            this->game_lib.setInstance(games_lib[this->current_game]);
            isMenu = true;
        }

        graphic_lib.getInstance()->clear();
        if (!objects.empty()) {
            for (auto object : objects) {
                graphic_lib.getInstance()->draw(object);
            }
        }
        graphic_lib.getInstance()->display();
    }
    graphic_lib.unload();
    game_lib.unload();
    return true;
}

void arcade::Core::getMenuSelector(arcade::IText *text) {
    std::string lib = text->getText();

    if (gameSelector.find(lib) != gameSelector.end()) {
        std::string game = gameSelector[lib];
        auto it = std::find(games_lib.begin(), games_lib.end(), game);
        int i = std::distance(games_lib.begin(), it);
        this->current_game = i;
    }
    if (graphicSelector.find(lib) != graphicSelector.end()) {
        std::string graphic = graphicSelector[lib];
        auto it = std::find(graphics_libs.begin(), graphics_libs.end(), graphic);
        int i = std::distance(graphics_libs.begin(), it);
        this->current_graphics = i;
    }
}

bool arcade::Core::getAllLibraryAvailable() {
    /*
        All graphics library that can exists in our arcade
    */
    std::vector <std::string> graphicsLibs = {
        "./lib/arcade_ncurses.so",
        "./lib/arcade_sfml.so",
        "./lib/arcade_sdl2.so",
        "./lib/arcade_ndk++.so",
        "./lib/arcade_aalib.so",
        "./lib/arcade_libcaca.so",
        "./lib/arcade_allegro5.so",
        "./lib/arcade_xlib.so",
        "./lib/arcade_gtk+.so",
        "./lib/arcade_irrlicht.so",
        "./lib/arcade_opengl.so",
        "./lib/arcade_vulkan.so",
        "./lib/(arcade_qt5.so"
    };
    /*
        All games library that can exists in our arcade
    */
    std::vector <std::string> gamesLibs = {
        "./lib/arcade_menu.so",
        "./lib/arcade_snake.so",
        "./lib/arcade_pacman.so",
        "./lib/arcade_qix.so",
        "./lib/arcade_centipede.so",
        "./lib/arcade_solarfox.so",
        "./lib/arcade_nibbler.so",
    };

    /*
        We open the lib folder and we find all library exist to store the string into the correct vector
    */
    for (auto entry : std::filesystem::directory_iterator("./lib")) {
        for (auto graphicLib : graphicsLibs) {
            if (entry.path() == graphicLib) {
                this->graphics_libs.push_back(graphicLib);
            }
        }
        for (auto gameLib : gamesLibs) {
            if (entry.path() == gameLib) {
                this->games_lib.push_back(gameLib);
            }
        }
    }

    /*
        Check if games_lib vector or graphics_lib have a least 1 lib to start the game
    */
    if (this->games_lib.empty())
        throw Error("No found one games library");
    if (this->graphics_libs.empty())
        throw Error("No found one graphic library");

    auto it = std::find(games_lib.begin(), games_lib.end(), "./lib/arcade_menu.so");
    if (it != games_lib.end()) {
        std::rotate(games_lib.begin(), it, it + 1);
    }
    return true;
}

void arcade::Core::getCurrentLibrayToDisplay(std::string argv) {
   auto t = std::find(graphics_libs.begin(), graphics_libs.end(), "./" + argv);
   if (t != graphics_libs.end()) { // Si la chaîne de caractères est trouvée dans le vecteur
        current_graphics = distance(graphics_libs.begin(), t); // Calculer la position de la chaîne de caractères dans le vecteur
    } else { // Si la chaîne de caractères n'est pas trouvée dans le vecteur
        throw Error("Library not found !");
    }
}

void arcade::Core::changeGameLibrary(arcade::Input input) {
    if (input == arcade::Input::PREVIOUSGAME) {
        if (this->current_game == 1)
            this->current_game = 3;
        else
            this->current_game -= 1;
        game_lib.unload();
        game_lib.setInstance(games_lib[this->current_game]);
    }
    if (input == arcade::Input::NEXTGAME) {
        if (this->current_game == 3)
            this->current_game = 1;
        else
            this->current_game++;
        game_lib.unload();
        game_lib.setInstance(games_lib[this->current_game]);
    }
}

void arcade::Core::changeGraphicLibrary(arcade::Input input) {
    if (input == arcade::Input::PREVIOUSGRAPH) {
        if (this->current_graphics == 0)
            this->current_graphics = 2;
        else
            this->current_graphics -= 1;
        graphic_lib.unload();
        graphic_lib.setInstance(graphics_libs[this->current_graphics]);
    }
    if (input == arcade::Input::NEXTGRAPH) {
        if (this->current_graphics == 2)
            this->current_graphics = 0;
        else
            this->current_graphics++;
        graphic_lib.unload();
        graphic_lib.setInstance(graphics_libs[this->current_graphics]);
    }
}
