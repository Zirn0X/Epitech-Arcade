/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** SFMLDisplay
*/

#include "../includes/SFMLDisplay.hpp"

arcade::SFMLDisplay::SFMLDisplay() {
    this->window.create(sf::VideoMode(1600, 1200), "Arcade - SFML");
    this->window.setFramerateLimit(5);
    if (!this->font.loadFromFile("assets/arcade.TTF"))
        throw Error("Failed to load font.");
}

arcade::SFMLDisplay::~SFMLDisplay() {
    this->window.close();
    colorsMap.clear();
    textures.clear();
}

void arcade::SFMLDisplay::SFMLDisplay::display() {
    this->window.display();
    this->clear();
}

void arcade::SFMLDisplay::SFMLDisplay::clear() {
    this->window.clear();
}

arcade::Input arcade::SFMLDisplay::SFMLDisplay::event() {
    arcade::Input event = arcade::Input::UNDEFINED;
    sf::Event sEvent;

    while (this->window.pollEvent(sEvent)) {
        if (sEvent.type == sf::Event::Closed)
            event = arcade::EXIT;
        if (sEvent.type == sf::Event::KeyPressed) {
            if (sEvent.key.code == sf::Keyboard::Left)
                event = arcade::LEFT;
            if (sEvent.key.code == sf::Keyboard::Right)
                event = arcade::RIGHT;
            if (sEvent.key.code == sf::Keyboard::Up)
                event = arcade::UP;
            if (sEvent.key.code == sf::Keyboard::Down)
                event = arcade::DOWN;
            if (sEvent.key.code == sf::Keyboard::Escape)
                event = arcade::EXIT;
            if (sEvent.key.code == sf::Keyboard::G)
                event = arcade::PREVIOUSGRAPH;
            if (sEvent.key.code == sf::Keyboard::H)
                event = arcade::NEXTGRAPH;
            if (sEvent.key.code == sf::Keyboard::B)
                event = arcade::PREVIOUSGAME;
            if (sEvent.key.code == sf::Keyboard::N)
                event = arcade::NEXTGAME;
            if (sEvent.key.code == sf::Keyboard::Space)
                event = arcade::ACTION1;
            if (sEvent.key.code == sf::Keyboard::R)
                event = arcade::RESTART;
            if (sEvent.key.code == sf::Keyboard::M)
                event = arcade::MENU;
        }
    }
    return event;
}

void arcade::SFMLDisplay::SFMLDisplay::draw(std::shared_ptr<arcade::IObject> object) {
    if (dynamic_cast<arcade::ITile *>(object.get()) != nullptr)
        drawSprite(dynamic_cast<arcade::ITile *>(object.get()));
    if (dynamic_cast<arcade::IText *>(object.get()) != nullptr)
        drawText(dynamic_cast<arcade::IText *>(object.get()));
}

void arcade::SFMLDisplay::SFMLDisplay::drawSprite(arcade::ITile *tile) {
    sf::RectangleShape rect;

    rect.setFillColor(this->colorsMap[tile->getColor()]);
    rect.setPosition(sf::Vector2f(tile->getPosition().first * 35, tile->getPosition().second * 35));
    rect.setRotation(0);
    rect.setScale(2, 2);
    rect.setSize(sf::Vector2f(10, 10));
    this->window.draw(rect);
}

void arcade::SFMLDisplay::SFMLDisplay::drawText(arcade::IText *text) {
    sf::Text t;

    t.setString(text->getText());
    t.setPosition(sf::Vector2f(text->getPosition().first * 50, text->getPosition().second * 50));
    t.setCharacterSize(50);
    t.setFont(this->font);
    t.setFillColor(this->colorsMap[text->getColorText()]);
    this->window.draw(t);
}

extern "C" arcade::SFMLDisplay *entryPoint() {
    return new(arcade::SFMLDisplay);
}
