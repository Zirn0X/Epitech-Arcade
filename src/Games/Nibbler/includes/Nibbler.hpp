/*
** EPITECH PROJECT, 2023
** arcarde
** File description:
** Nibbler
*/

#pragma once
#include <string>
#include <random>
#include "IGames.hpp"
#include "Object/Tile.hpp"
#include "Object/Text.hpp"
#include "Object/Sound.hpp"
#include <fstream>
#include "Exception.hpp"

    #define MAP_WIDTH 20
    #define MAP_HEIGHT 23
    #define GRID_SIZE 1

namespace arcade {
    class Nibbler : public IGames {
        public:
            enum class Direction {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };
            Nibbler();
            ~Nibbler();
            std::vector<std::shared_ptr<arcade::IObject>> loop(arcade::Input input);
            void restart();
            std::shared_ptr<arcade::ITile> createTile();
            std::shared_ptr<arcade::ISound> createSound(){return std::make_shared<arcade::Sound>();}
            std::shared_ptr<arcade::IText> createText();
            arcade::Input event(arcade::Input input);
            class SnakeGame {
                public:
                    SnakeGame();
                    ~SnakeGame();
                    std::vector<std::pair<std::size_t, std::size_t>> getSnake() const;
                    void setDir(Direction dir);
                    arcade::Nibbler::Direction getDir() const;
                    bool Move(std::pair<std::size_t, std::size_t> posFood, std::pair<std::size_t, std::size_t> pos);
                    void restart();
                    void initMap();
                    std::vector<std::string> getMap() const;
                    void clear();
                private:
                    void findSnakePos(std::string str, std::size_t i);
                    bool moveBody(std::pair<std::size_t, std::size_t>);
                    std::vector<std::pair<std::size_t, std::size_t>> _snakeGame;
                    Direction _dir = Direction::RIGHT;
                    std::vector<std::string> _mapGame;
                    std::vector<std::string> _mapSave;
            };
        protected:
        private:
            SnakeGame _snakeBody;
            void createSnake();
            void createMap();
            void createFood(std::pair<std::size_t , std::size_t> pos);
            void setText(std::pair<std::size_t , std::size_t> pos, std::string txt);
            void setMap(std::pair<std::size_t, std::size_t> pos);
            void execInput(arcade::Input input, std::pair<std::size_t, std::size_t> pos);
            void createWall();
            void setWall(std::pair<std::size_t, std::size_t> pos);
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