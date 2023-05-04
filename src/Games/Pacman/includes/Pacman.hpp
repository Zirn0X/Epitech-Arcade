/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Snake
*/

#ifndef PACMAN_HPP
#define PACMAN_HPP
#include <memory>
#include <vector>
#include <fstream>
#include "IGames.hpp"
#include "Object/Tile.hpp"
#include "Object/Text.hpp"
#include "Object/Sound.hpp"
#include "Exception.hpp"

#define GRID_SIZE 1

namespace arcade {
    class Pacman : public arcade::IGames {
        public:
            Pacman();
            ~Pacman();
            std::vector<std::shared_ptr<arcade::IObject>> loop(arcade::Input input);
            void restart();
            std::shared_ptr<arcade::ITile> createTile();
            std::shared_ptr<arcade::ISound> createSound();
            std::shared_ptr<arcade::IText> createText();
            arcade::Input event(arcade::Input input);
            class PacmanGame {
                public:
                    PacmanGame();
                    ~PacmanGame();
                    std::pair<std::size_t, std::size_t> getPacman() const;
                    std::vector<std::string> getMap() const;
                    std::vector<std::pair<std::size_t, std::size_t>> getEnemies() const;
                    int getTick () const;
                    int getScore () const;
                    std::vector<arcade::Input> getEnemiesDir() const;
                    bool getEatingMod() const;
                    void setMap(std::pair<std::size_t, std::size_t> pos, char c);
                    void setDir(arcade::Input input);
                    void resetFood();
                    void Move(std::pair<std::size_t, std::size_t> pos);
                    void enemyMove(arcade::Input input, int id);
                    void enemyOut();
                    bool enemyPos();
                    bool foodEaten();
                    void restart();
                private:
                    void initMap();
                    void findPacmanPos(std::string str, std::size_t i);
                    void findEnemiesPos(std::string str, std::size_t i);
                    void clear();
                    std::pair<std::size_t, std::size_t> _pacmanGame;
                    std::vector<std::string> _mapGame;
                    std::vector<std::string> _mapSave;
                    std::vector<std::pair<std::size_t, std::size_t>> _enemiesGame;
                    std::vector<arcade::Input> _enemiesDir;
                    arcade::Input _input = arcade::Input::RIGHT;
                    int _score = 0;
                    int _tick = 0;
                    int _tickSave = 0;
                    bool _canEat = false;
                    bool _eatingMod = false;
            };
        protected:
        private:
            PacmanGame _pacGame;
            void createEntity();
            void setWall(std::pair<std::size_t, std::size_t> pos);
            void setFloor(std::pair<std::size_t, std::size_t> pos);
            void setFood(std::pair<std::size_t, std::size_t> pos, char c);
            void setText(std::pair<std::size_t , std::size_t> pos, std::string txt);
            void createWall();
            void createFloor();
            void createFood();
            void execInput(arcade::Input input, std::pair<std::size_t, std::size_t> pos);
            std::vector<std::shared_ptr<arcade::IObject>> _obj;
            std::pair<std::size_t, std::size_t> _pacman;
            std::vector<std::pair<std::size_t, std::size_t>> _enemies;
            std::pair<std::size_t, std::size_t> _text;
            std::pair<std::size_t, std::size_t> _scoreText;
            std::pair<std::size_t, std::size_t> _scorePoint;
    };

    extern "C" Pacman *entryPoint();
}

#endif
