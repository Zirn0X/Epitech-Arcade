/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Snake
*/

#ifndef SNAKE_HPP
#define SNAKE_HPP
#include <string>
#include <random>
#include "IGames.hpp"
#include "Object/Tile.hpp"
#include "Object/Text.hpp"
#include "Object/Sound.hpp"

    #define MAP_WIDTH 25
    #define MAP_HEIGHT 25
    #define GRID_SIZE 1

namespace arcade {
    class Snake : public IGames {
        public:
            enum class Direction {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };
            Snake();
            ~Snake();
            std::vector<std::shared_ptr<arcade::IObject>> loop(arcade::Input input);
            void restart();
            std::shared_ptr<arcade::ITile> createTile();
            std::shared_ptr<arcade::ISound> createSound();
            std::shared_ptr<arcade::IText> createText();
            arcade::Input event(arcade::Input input);
            class SnakeGame {
                public:
                    SnakeGame();
                    ~SnakeGame();
                    std::vector<std::pair<std::size_t, std::size_t>> getSnake() const;
                    void setDir(Direction dir);
                    arcade::Snake::Direction getDir() const;
                    bool Move(std::pair<std::size_t, std::size_t> posFood);
                    void restart();
                private:
                    bool moveBody(std::pair<std::size_t, std::size_t>);
                    std::vector<std::pair<std::size_t, std::size_t>> _snake;
                    Direction _dir = Direction::UP;
            };
        private:
            SnakeGame _snakeBody;
            void createSnake();
            void createMap();
            void createFood(std::pair<std::size_t , std::size_t> pos);
            void setText(std::pair<std::size_t , std::size_t> pos, std::string txt);
            void setMap(std::pair<std::size_t, std::size_t> pos);
            void execInput(arcade::Input input);
            void checkCollision();
            std::vector<std::shared_ptr<arcade::IObject>> _obj;
            std::pair<std::size_t, std::size_t> _map;
            std::pair<std::size_t, std::size_t> _food;
            std::pair<std::size_t, std::size_t> _text;
            std::pair<std::size_t, std::size_t> _scoreText;
            std::pair<std::size_t, std::size_t> _scorePoint;
            std::size_t _score;
    };
}

extern "C" arcade::Snake *entryPoint();

#endif
