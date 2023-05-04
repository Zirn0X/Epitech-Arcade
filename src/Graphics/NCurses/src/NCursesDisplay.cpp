/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** NCursesDisplay
*/

#include "../includes/NCursesDisplay.hpp"
#include <chrono>
#include <thread>

arcade::NCursesDisplay::NCursesDisplay() {
    _screen = newterm(getenv("TERM"), stdout, stdin);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    noecho();
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_RED);
    init_pair(2, COLOR_BLUE, COLOR_BLUE);
    init_pair(3, COLOR_GREEN, COLOR_GREEN);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_WHITE);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_BLUE, COLOR_BLACK);
    init_pair(9, COLOR_GREEN, COLOR_BLACK);
    init_pair(10, COLOR_BLACK, COLOR_BLACK);
    init_pair(11, COLOR_YELLOW, COLOR_BLACK);
    init_pair(12, COLOR_WHITE, COLOR_BLACK);

}

arcade::NCursesDisplay::~NCursesDisplay() {
    endwin();
    delscreen(_screen);
}

void arcade::NCursesDisplay::display() {
}

void arcade::NCursesDisplay::clear() {
    wclear(stdscr);
}

void arcade::NCursesDisplay::whichColorTile(arcade::Color color) {
    switch (color)
    {
    case arcade::RED:
        attron(COLOR_PAIR (1));
        break;
    case arcade::BLUE:
        attron(COLOR_PAIR (2));
        break;
    case arcade::GREEN:
        attron(COLOR_PAIR (3));
        break;
    case arcade::DARK:
        attron(COLOR_PAIR (4));
        break;
    case arcade::YELLOW:
        attron(COLOR_PAIR (5));
        break;
    case arcade::WHITE:
        attron(COLOR_PAIR (6));
        break;
    default:
        break;
    }
}

void arcade::NCursesDisplay::whichColorText(arcade::Color color) {
    switch (color)
    {
    case arcade::RED:
        attron(COLOR_PAIR (7));
        break;
    case arcade::BLUE:
        attron(COLOR_PAIR (8));
        break;
    case arcade::GREEN:
        attron(COLOR_PAIR (9));
        break;
    case arcade::DARK:
        attron(COLOR_PAIR (10));
        break;
    case arcade::YELLOW:
        attron(COLOR_PAIR (11));
        break;
    case arcade::WHITE:
        attron(COLOR_PAIR (12));
        break;
    default:
        break;
    }
}

void arcade::NCursesDisplay::draw(std::shared_ptr<arcade::IObject> object) {
    char newChar;
    auto newTile = dynamic_cast<arcade::ITile*>(object.get());
    if (newTile != nullptr) {
        whichColorTile(newTile->getColor());
        newChar = newTile->getCharacter();
        mvprintw(newTile->getPosition().second, newTile->getPosition().first, "%c", newChar);
        attroff(newTile->getColor());
    }
    auto newText = dynamic_cast<arcade::IText*>(object.get());
    if (newText != nullptr) {
        whichColorText(newText->getColorText());
        mvprintw(newText->getPosition().second, newText->getPosition().first * 2, newText->getText().c_str());
        attroff(newText->getColorText());
    }
}

arcade::Input arcade::NCursesDisplay::event() {
    _key = getch();
    if (_key == 27)
        return EXIT;
    if (_key == 32)
        return ACTION1;
    if (_key == 260)
        return LEFT;
    if (_key == 261)
        return RIGHT;
    if (_key == 259)
        return UP;
    if (_key == 258)
        return DOWN;
    if (_key == 114)
        return RESTART;
    if (_key == 114)
        return MENU;
    if (_key == 103)
        return PREVIOUSGRAPH;
    if (_key == 104)
        return NEXTGRAPH;
    if (_key == 109)
        return MENU;
    if (_key == 103) {
        clear();
        endwin();
        delscreen(_screen);
        return PREVIOUSGRAPH;
    }
    if (_key == 104) {
        clear();
        endwin();
        delscreen(_screen);
        return NEXTGRAPH;
    }
    if (_key == 98)
        return PREVIOUSGAME;
    if (_key == 110)
        return NEXTGAME;
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
    return UNDEFINED;
}

extern "C" arcade::NCursesDisplay *entryPoint() {
    return new arcade::NCursesDisplay();
}
