/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** SFMLDisplay
*/

#ifndef SFMLDISPLAY_HPP
#define SFMLDISPLAY_HPP
    #include <SFML/Graphics.hpp>
    #include <map>
    #include "IObject.hpp"
    #include "IGraphics.hpp"
    #include "Object/Tile.hpp"
    #include "Object/Text.hpp"
    #include "Object/Sound.hpp"
    #include "Exception.hpp"

namespace arcade {
    class SFMLDisplay : public arcade::IGraphics {
        public:
            SFMLDisplay();
            ~SFMLDisplay();
            void display() override;
            void clear() override;
            void draw(std::shared_ptr<arcade::IObject> object) override;
            arcade::Input event() override;
        protected:
        private:
            sf::RenderWindow window;
            sf::Font font;
            void drawSprite(arcade::ITile *tile);
            void drawText(arcade::IText *text);
            sf::Color getColor(arcade::Color aracdeColor);
            std::map<arcade::Color, sf::Color> colorsMap = {
                {arcade::Color::RED, sf::Color::Red},
                {arcade::Color::BLUE, sf::Color::Blue},
                {arcade::Color::GREEN, sf::Color::Green},
                {arcade::Color::DARK, sf::Color::Black},
                {arcade::Color::YELLOW, sf::Color::Yellow},
                {arcade::Color::WHITE, sf::Color::White}
            };
            std::map<std::string, std::shared_ptr<sf::Texture>> textures;
    };
}


extern "C" arcade::SFMLDisplay *entryPoint();

#endif
