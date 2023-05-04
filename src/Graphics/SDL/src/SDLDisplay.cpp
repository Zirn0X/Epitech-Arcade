/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** SDLDisplay
*/

#include "../includes/SDLDisplay.hpp"

extern "C" arcade::SDLDisplay *entryPoint() {
    return new arcade::SDLDisplay;
}

arcade::SDLDisplay::SDLDisplay() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw Error("SDL : Can't initialize SDL\n");
    if (TTF_Init() != 0)
        throw Error("SDL : Can't initialize TTF\n");

    _window = SDL_CreateWindow("Arcade - SDL",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_WIDTH, WINDOW_HEIGHT,
                            SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (_window == NULL)
        throw Error("SDL : Window can't be created\n");

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
        throw Error("SDL : Renderer can't be created\n");

    _font = TTF_OpenFont("assets/arcade.TTF", 24);
    if (_font == NULL)
        throw Error("SDL : Font can't be created\n");
    initColor();
}

arcade::SDLDisplay::~SDLDisplay() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    TTF_CloseFont(_font);
    TTF_Quit();
    SDL_Quit();
}

void arcade::SDLDisplay::initColor() {
    _color[RED] = { 255, 0, 0, 255 };
    _color[BLUE] = { 0, 0, 255, 255 };
    _color[GREEN] = { 0, 255, 0, 255 };
    _color[DARK] = { 100, 100, 100, 255 };
    _color[YELLOW] = { 255, 255, 0, 255 };
    _color[WHITE] = { 255, 255, 255, 255 };
}

SDL_Renderer *arcade::SDLDisplay::getRenderer() const {
    return _renderer;
}

SDL_Window *arcade::SDLDisplay::getWindow() const {
    return _window;
}

arcade::Input arcade::SDLDisplay::event() {
    SDL_Event event;
    arcade::Input input = UNDEFINED;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT)
            input = EXIT;
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE)
                input = EXIT;
            else if (event.key.keysym.sym == SDLK_LEFT)
                input = LEFT;
            else if (event.key.keysym.sym == SDLK_RIGHT)
                input = RIGHT;
            else if (event.key.keysym.sym == SDLK_UP)
                input = UP;
            else if (event.key.keysym.sym == SDLK_DOWN)
                input = DOWN;
            else if (event.key.keysym.sym == SDLK_r)
                input = RESTART;
            else if (event.key.keysym.sym == SDLK_m)
                input = MENU;
            else if (event.key.keysym.sym == SDLK_g)
                input = PREVIOUSGRAPH;
            else if (event.key.keysym.sym == SDLK_h)
                input = NEXTGRAPH;
            else if (event.key.keysym.sym == SDLK_b)
                input = PREVIOUSGAME;
            else if (event.key.keysym.sym == SDLK_n)
                input = NEXTGAME;
            else if (event.key.keysym.sym == SDLK_SPACE)
                input = ACTION1;
            else if (event.key.keysym.sym == SDLK_m)
                input = MENU;
        }
    }
    return input;
}

void arcade::SDLDisplay::clear() {
    SDL_RenderClear(this->getRenderer());
}

void arcade::SDLDisplay::draw(std::shared_ptr<arcade::IObject> object) {
    if (dynamic_cast<arcade::ITile*>(object.get()) != nullptr)
        drawTile(dynamic_cast<arcade::Tile *>(object.get()));
    else if (dynamic_cast<arcade::IText*>(object.get()) != nullptr)
        drawText(dynamic_cast<arcade::Text *>(object.get()));
    else if (dynamic_cast<arcade::ISound*>(object.get()) != nullptr)
        playSound(dynamic_cast<arcade::Sound*>(object.get()));
}

void arcade::SDLDisplay::drawTile(arcade::ITile *tile) {
    SDL_SetRenderDrawColor(_renderer, _color[tile->getColor()].r, _color[tile->getColor()].g, _color[tile->getColor()].b, _color[tile->getColor()].a);
    SDL_Rect rect = {static_cast<int>(tile->getPosition().first * 35), static_cast<int>(tile->getPosition().second * 35), 35, 35};
    SDL_RenderFillRect(_renderer, &rect);
    SDL_SetRenderDrawColor(_renderer, _color[arcade::Color::DARK].r, _color[arcade::Color::DARK].g, _color[arcade::Color::DARK].b, _color[arcade::Color::DARK].a);
}

void arcade::SDLDisplay::drawText(arcade::IText *text) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(_font, text->getText().c_str(), _color[text->getColorText()]);
    SDL_Texture *message = SDL_CreateTextureFromSurface(_renderer, textSurface);
    SDL_Rect Message_rect;

    Message_rect.x = text->getPosition().first * 50;
    Message_rect.y = text->getPosition().second * 50;
    Message_rect.w = 50 * text->getText().size();
    Message_rect.h = 50;
    SDL_RenderCopy(_renderer, message, NULL, &Message_rect);
}

void arcade::SDLDisplay::playSound(arcade::ISound *sound) {
    (void) sound;
}

void arcade::SDLDisplay::display() {
    SDL_RenderPresent(_renderer);
    SDL_Delay(_speed);
}