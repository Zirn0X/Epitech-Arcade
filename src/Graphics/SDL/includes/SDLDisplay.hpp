/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** SDLDisplay
*/

#ifndef SDLDISPLAY_HPP
    #define SDLDISPLAY_HPP
    #include <unordered_map>
    #include "IObject.hpp"
    #include "IGraphics.hpp"
    #include "Exception.hpp"
    #include "Object/Tile.hpp"
    #include "Object/Text.hpp"
    #include "Object/Sound.hpp"
    #include "SDL2/SDL.h"
    #include "SDL2/SDL_ttf.h"

    #define WINDOW_WIDTH 1000
    #define WINDOW_HEIGHT 1000
    #define GRID_SIZE 15
    #define NUM_ROWS WINDOW_HEIGHT / GRID_SIZE
    #define NUM_COLS WINDOW_WIDTH / GRID_SIZE

namespace arcade {
    class SDLDisplay : public IGraphics {
        public:
            struct Colors {
                SDL_Color red = { 255, 0, 0, 255 };
                SDL_Color blue = { 0, 0, 255, 255 };
                SDL_Color green = { 0, 255, 0, 255 };
                SDL_Color dark = { 100, 100, 100, 255 };
                SDL_Color yellow = { 255, 255, 0, 255 };
                SDL_Color white = { 255, 255, 255, 255 };
            };
            SDLDisplay();
            ~SDLDisplay();
            void display();
            void clear();
            void draw(std::shared_ptr<arcade::IObject> object);
            arcade::Input event();
            void initColor();
        private:
            SDL_Renderer *getRenderer() const;
            SDL_Window *getWindow() const;
            SDL_Window *_window = NULL;
            SDL_Renderer *_renderer = NULL;
            TTF_Font *_font = NULL;
            std::size_t _speed = 150;
            void drawTile(arcade::ITile *tile);
            void drawText(arcade::IText *text);
            void playSound(arcade::ISound *sound);
            std::unordered_map<arcade::Color, SDL_Color> _color;
    };
}

extern "C" arcade::SDLDisplay *entryPoint();

#endif