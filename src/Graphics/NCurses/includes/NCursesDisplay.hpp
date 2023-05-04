/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** NCursesDisplay
*/

#ifndef NCURSESDISPLAY_HPP
    #define NCURSESDISPLAY_HPP
    #include "../../../../includes/IObject.hpp"
    #include "../../../../includes/IGraphics.hpp"
    #include <ncurses.h>

namespace arcade {
    class NCursesDisplay : public IGraphics {
        public:
            NCursesDisplay();
            ~NCursesDisplay();
            void display();
            void clear();
            void draw(std::shared_ptr<arcade::IObject> object);
            arcade::Input event();
            void whichColorTile(arcade::Color color);
            void whichColorText(arcade::Color color);
        private:
            int _key = 0;
            SCREEN *_screen;
    };
}
extern "C" arcade::NCursesDisplay *entryPoint();


#endif
