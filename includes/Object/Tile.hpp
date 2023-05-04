/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Tile Class
*/

#ifndef TILE_HPP
    #define TILE_HPP
    #include "../IObject.hpp"

namespace arcade {
    class Tile : public arcade::ITile {
        public:
            Tile() {};
            ~Tile() {};

            std::string getTexture() const override {
                return this->pathTexture;
            };

            std::pair<std::size_t, std::size_t> getPosition() const override {
                return this->position;
            };

            char getCharacter() const override {
                return symbol;
            };

            arcade::Color getColor() const override {
                return color;
            };

            std::pair<float, float> getScale() const override {
                return scale;
            };

            float getRotation() const override {
                return rotation;
            };

            void setTexture(std::string path) override {
                this->pathTexture = path;
            };

            void setPosition(std::pair<std::size_t, std::size_t> pos) override {
                this->position = pos;
            };

            void setCharacter(char c) override {
                this->symbol = c;
            };

            void setColor(arcade::Color color) override {
                this->color = color;
            };

            void setScale(std::pair<float, float> scale) override {
                this->scale = scale;
            };

            void setRotation(float rotation) override {
                this->rotation = rotation;
            };
            std::pair<float, float> getOriginScale() override {
                return scale;
            };
            std::pair<std::size_t, std::size_t> getOriginPosition() override {
                return scale;
            };
            void setOriginScale(std::pair<float, float> scale) override {
                (void)scale;
            };
            void setOriginPosition(std::pair<std::size_t, std::size_t> position) override {
                (void)position;
            };
            void setEvent(arcade::Input event) override {
                (void)event;
            };
            arcade::Input getEvent() const override {
                return UNDEFINED;
            };
            void setName(std::string name) override {
                (void)name;
            };
            std::string getName() const override {
                return "";
            };
        protected:
        private:
            std::string pathTexture = "";
            std::pair<float, float> position = std::make_pair(0.0, 0.0);
            char symbol = 'x';
            arcade::Color color = arcade::Color::DARK;
            std::pair<float, float> scale = std::make_pair(1.0, 1.0);
            float rotation = 0.0;
    };
}

#endif /* !TILE_HPP */
