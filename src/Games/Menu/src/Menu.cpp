/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Menu
*/

#include "../includes/Menu.hpp"

arcade::Menu::Menu() {
    _title = std::make_pair(14, 1);
    _snakeButton = std::make_pair(4, 5);
    _pacmanButton = std::make_pair(14, 5);;
    _nibblerButton = std::make_pair(24, 5);
    _lib = std::make_pair(14, 11);
    _sfml = std::make_pair(4, 15);
    _sdl = std::make_pair(14, 15);
    _ncurse = std::make_pair(24, 15);
    _username = std::make_pair(13, 20);
    _usernameSet = std::make_pair(16, 20);
    _pseudo = "";
    _gameState = arcade::Menu::GameState::SNAKE;
    _libState = arcade::Menu::LibState::SFML;
    _posCursor = {0, 0};
}

arcade::Menu::~Menu() {
}

std::shared_ptr<arcade::ITile> arcade::Menu::createTile() {
    return std::make_shared<arcade::Tile>();
}

std::shared_ptr<arcade::ISound> arcade::Menu::createSound() {
    return std::make_shared<arcade::Sound>();
}

std::shared_ptr<arcade::IText> arcade::Menu::createText() {
    return std::make_shared<arcade::Text>();
}

void arcade::Menu::restart() {}

void arcade::Menu::readPseudo() {
    std::ifstream file("./assets/pseudo.txt");
    try {
        std::string line;
        while (std::getline(file, line)) {
            _pseudo = line;
        }
    } catch (Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

std::vector<std::shared_ptr<arcade::IObject>> arcade::Menu::loop(arcade::Input input) {
    if (_pseudo.empty())
        this->readPseudo();
    setText(_title, "ARCADE");
    setText(_snakeButton, "Snake");
    setText(_pacmanButton, "Pacman");
    setText(_nibblerButton, "Nibbler");
    setText(_lib, "Library");
    setText(_sfml, "SFML");
    setText(_sdl, "SDL");
    setText(_ncurse, "NCURSE");
    setText(_username, "User :");
    setText(_usernameSet, _pseudo);
    this->chooseGameAndLib(input);
    return _obj;
}

void arcade::Menu::setText(std::pair<std::size_t , std::size_t> pos, std::string txt) {
    auto text = createText();
    text.get()->setPosition(pos);
    text.get()->setText(txt);
    text.get()->setColorText(arcade::WHITE);
    this->selectedGameAndLib(text);
    _obj.push_back(text);
}

void arcade::Menu::sendGameAndLib() {
    auto game = createText();
    auto lib = createText();

    switch (_gameState) {
    case arcade::Menu::GameState::SNAKE:
        game.get()->setText("Game_Snake");
        break;
    case arcade::Menu::GameState::PACMAN:
        game.get()->setText("Game_Pacman");
        break;
    case arcade::Menu::GameState::NIBBLER:
        game.get()->setText("Game_Nibbler");
        break;
    default:
        break;
    }
    switch (_libState) {
    case arcade::Menu::LibState::SFML:
        lib.get()->setText("Lib_Sfml");
        break;
    case arcade::Menu::LibState::SDL:
        lib.get()->setText("Lib_Sdl");
        break;
    case arcade::Menu::LibState::NCURSE:
        lib.get()->setText("Lib_Ncurse");
        break;
    default:
        break;
    }
    _obj.push_back(game);
    _obj.push_back(lib);
}


void arcade::Menu::currentCursorColor(std::shared_ptr<arcade::IText> text) {
    if (_posCursor.first == 0 && _posCursor.second == 0 && text.get()->getText() == "Snake")
        text.get()->setColorText(arcade::GREEN);
    if (_posCursor.first == 0 && _posCursor.second == 1 && text.get()->getText() == "Pacman")
        text.get()->setColorText(arcade::GREEN);
    if (_posCursor.first == 0 && _posCursor.second == 2 && text.get()->getText() == "Nibbler")
        text.get()->setColorText(arcade::GREEN);
    if (_posCursor.first == 1 && _posCursor.second == 0 && text.get()->getText() == "SFML")
        text.get()->setColorText(arcade::GREEN);
    if (_posCursor.first == 1 && _posCursor.second == 1 && text.get()->getText() == "SDL")
        text.get()->setColorText(arcade::GREEN);
    if (_posCursor.first == 1 && _posCursor.second == 2 && text.get()->getText() == "NCURSE")
        text.get()->setColorText(arcade::GREEN);
    if (_posCursor.first == 2 && text.get()->getText() == "User :")
        text.get()->setColorText(arcade::GREEN);
}


void arcade::Menu::selectedGameAndLib(std::shared_ptr<arcade::IText> text) {
    switch (_gameState) {
    case arcade::Menu::GameState::SNAKE:
        if (text.get()->getText() == "Snake") {
            text.get()->setColorText(arcade::RED);
        }
        break;
    case arcade::Menu::GameState::PACMAN:
        if (text.get()->getText() == "Pacman") {
            text.get()->setColorText(arcade::RED);
        }
        break;
    case arcade::Menu::GameState::NIBBLER:
        if (text.get()->getText() == "Nibbler") {
            text.get()->setColorText(arcade::RED);
        }
        break;
    default:
        text.get()->setColorText(arcade::WHITE);
        break;
    }

    switch (_libState) {
    case arcade::Menu::LibState::SFML:
        if (text.get()->getText() == "SFML") {
            text.get()->setColorText(arcade::RED);
        }
        break;
    case arcade::Menu::LibState::SDL:
        if (text.get()->getText() == "SDL") {
            text.get()->setColorText(arcade::RED);
        }
        break;
    case arcade::Menu::LibState::NCURSE:
        if (text.get()->getText() == "NCURSE") {
            text.get()->setColorText(arcade::RED);
        }
        break;
    default:
        text.get()->setColorText(arcade::WHITE);
        break;
    }
    this->currentCursorColor(text);
}

void arcade::Menu::chooseGameAndLib(arcade::Input input) {
    switch (input) {
        case UP:
            if (_posCursor.first > 0) {
                _posCursor.first--;
            }
            break;
        case DOWN:
            if (_posCursor.first < 2) {
                _posCursor.first++;
            }
            break;
        case LEFT:
            if (_posCursor.second > 0) {
                _posCursor.second--;
            }
            break;
        case RIGHT:
            if (_posCursor.second < 2) {
                _posCursor.second++;
            }
            break;
        case ACTION1:
            if (_posCursor.first == 0)
                _gameState = static_cast<arcade::Menu::GameState>(_posCursor.second);
            if (_posCursor.first == 1)
                _libState = static_cast<arcade::Menu::LibState>(_posCursor.second);
            break;
        case NEXTGRAPH:
            _obj.clear();
            sendGameAndLib();
        default:
            break;
    }
}

arcade::Input arcade::Menu::event(arcade::Input input) {
    (void)input;
    return UNDEFINED;
}

extern "C" arcade::Menu *entryPoint() {
    return new arcade::Menu;
}
