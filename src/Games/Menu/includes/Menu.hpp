/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <unordered_map>
#include "IGames.hpp"
#include "Object/Tile.hpp"
#include "Object/Text.hpp"
#include "Object/Sound.hpp"
#include "Exception.hpp"
#include <fstream>
#include <iostream>

namespace arcade {
    class Menu : public arcade::IGames {
        public:
            enum class GameState {
                SNAKE,
                PACMAN,
                NIBBLER,
            };
            enum class LibState {
                SFML,
                SDL,
                NCURSE
            };
            Menu();
            ~Menu();
            std::vector<std::shared_ptr<arcade::IObject>> loop(arcade::Input input);
            void restart();
            std::shared_ptr<arcade::ITile> createTile();
            std::shared_ptr<arcade::ISound> createSound();
            std::shared_ptr<arcade::IText> createText();
            void setText(std::pair<std::size_t , std::size_t> pos, std::string txt);
            void selectedGameAndLib(std::shared_ptr<arcade::IText> text);
            void chooseGameAndLib(arcade::Input input);
            void currentCursorColor(std::shared_ptr<arcade::IText> text);
            void sendGameAndLib();
            arcade::Input event(arcade::Input input);
            void readPseudo();
        protected:
        private:
            std::vector<std::shared_ptr<arcade::IObject>> _obj;
            std::pair<std::size_t, std::size_t> _title;
            std::pair<std::size_t, std::size_t> _game;
            std::pair<std::size_t, std::size_t> _snakeButton;
            std::pair<std::size_t, std::size_t> _pacmanButton;
            std::pair<std::size_t, std::size_t> _nibblerButton;
            std::pair<std::size_t, std::size_t> _lib;
            std::pair<std::size_t, std::size_t> _sfml;
            std::pair<std::size_t, std::size_t> _sdl;
            std::pair<std::size_t, std::size_t> _ncurse;
            std::pair<std::size_t, std::size_t> _username;
            std::pair<std::size_t, std::size_t> _usernameSet;
            std::string _pseudo;
            arcade::Menu::GameState _gameState;
            arcade::Menu::LibState _libState;
            std::pair<std::size_t, std::size_t> _posCursor;
    };
    extern "C" Menu *entryPoint();
}

#endif /* !MENU_HPP_ */
