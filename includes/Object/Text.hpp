/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Text Class
*/

#ifndef TEXT_HPP
    #define TEXT_HPP
    #include "IObject.hpp"

namespace arcade {
    class Text : public IText {
        public:
            Text() {};
            ~Text() {};

            std::string getText() const override {
                return this->text;
            };

            arcade::Color getColorText() const override {
                return this->color;
            };

            std::pair<std::size_t, std::size_t> getPosition() const override {
                return this->position;
            };

            void setText(std::string text) override {
                this->text = text;
            };

            void setColorText(arcade::Color color) override {
                this->color = color;
            };

            void setPosition(std::pair<std::size_t, std::size_t> position) override {
                this->position = position;
            };
            void setRotation(float rotation) override {
                (void)rotation;
            };
            std::pair<float, float> getOriginScale() override {
                return std::make_pair(0.0, 0.0);
            };
            std::pair<std::size_t, std::size_t> getOriginPosition() override {
                return std::make_pair(0, 0);
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
            std::pair<float, float> getScale() const override {
                return position;
            };
            void setScale(std::pair<float, float> scale) override {
                (void)scale;
            };
        protected:
        private:
            std::string text = "";
            arcade::Color color = arcade::Color::WHITE;
            std::pair<std::size_t, std::size_t> position = std::make_pair(0.0, 0.0);
    };
}

#endif /* !TEXT_HPP */
