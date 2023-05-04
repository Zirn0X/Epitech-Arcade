/*
** EPITECH PROJECT, 2023
** arcarde
** File description:
** Nibbler
*/

#include "../includes/Nibbler.hpp"

extern "C" arcade::Nibbler *entryPoint() {
    return new arcade::Nibbler;
}


static std::pair<std::size_t, std::size_t> randPair() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, MAP_WIDTH - 2);
    return std::make_pair(dis(gen), dis(gen));
}

arcade::Nibbler::Nibbler() {
    this->createSnake();
    _map = std::make_pair(MAP_HEIGHT, MAP_WIDTH);
    _food = randPair();
    while (_snakeBody.getMap()[_food.second][_food.first] != '.') {
        _food = randPair();
    }
    _text = std::make_pair(20, 1);
    _scoreText = std::make_pair(20, 2);
    _scorePoint = std::make_pair(20, 3);
    _score = 0;
}

arcade::Nibbler::~Nibbler() {
    _obj.clear();
}

std::shared_ptr<arcade::ITile> arcade::Nibbler::createTile(){
    return std::make_shared<arcade::Tile>();
}

std::shared_ptr<arcade::IText> arcade::Nibbler::createText(){
    return std::make_shared<arcade::Text>();
}

void arcade::Nibbler::restart() {
    _snakeBody.clear();
    _snakeBody.initMap();
    _score = 0;
    _food = randPair();
    while (_snakeBody.getMap()[_food.second][_food.first] != '.') {
        _food = randPair();
    }
}

void arcade::Nibbler::createSnake() {
    auto snakebody = _snakeBody.getSnake();
    for (unsigned long i = 0; snakebody.size() != i; i++) {
        auto snake = createTile();
        snake.get()->setPosition({snakebody[i].first, snakebody[i].second});
        snake.get()->setColor(arcade::Color::YELLOW);
        _obj.push_back(snake);
    }
}

void arcade::Nibbler::setMap(std::pair<std::size_t , std::size_t> pos) {
    auto map = createTile();
    map.get()->setPosition({pos.first, pos.second});
    map.get()->setColor(arcade::Color::WHITE);
    _obj.push_back(map);
}

void arcade::Nibbler::createMap() {
    std::size_t x = 0;
    std::size_t y = 0;
    int a = 0;
    int b = 0;

    for (; x != _map.first; x++)
        setMap(std::make_pair(x, y));
    y++;
    x--;
    for (; y != _map.second; y++)
        setMap(std::make_pair(x, y));
    y--;
    a = x;
    b = y;
    for (; a != -1; a--)
        setMap(std::make_pair(a, b));
    a++;
    for (; b != -1; b--)
        setMap(std::make_pair(a, b));
}

void arcade::Nibbler::createFood(std::pair<std::size_t , std::size_t> pos) {
    auto food = createTile();
    food.get()->setPosition(pos);
    food.get()->setColor(arcade::Color::RED);
    _obj.push_back(food);
}

void arcade::Nibbler::setText(std::pair<std::size_t , std::size_t> pos, std::string txt) {
    auto text = createText();
    text.get()->setPosition(pos);
    text.get()->setText(txt);
    _obj.push_back(text);
}

std::vector<std::shared_ptr<arcade::IObject>> arcade::Nibbler::loop(arcade::Input input) {
    this->execInput(input, _snakeBody.getSnake()[0]);
    if (_snakeBody.Move(_food, _snakeBody.getSnake()[0])) {
        _food = randPair();
        while (_snakeBody.getMap()[_food.second][_food.first] != '.') {
            _food = randPair();
        }
        _score += 1;
    }
    this->checkCollision();
    _obj.clear();
    setText(_text, "Nibbler");
    setText(_scoreText, "Score");
    setText(_scorePoint, std::to_string(_score));
    createFood(_food);
    createSnake();
    this->createWall();
    return _obj;
}

void arcade::Nibbler::execInput(arcade::Input input, std::pair<std::size_t, std::size_t> pos) {
    switch (input) {
        case UP:
            if (_snakeBody.getMap()[pos.second - 1][pos.first] != '#' && _snakeBody.getDir() != Nibbler::Direction::DOWN)
                _snakeBody.setDir(Nibbler::Direction::UP);
            break;
        case DOWN:
            if (_snakeBody.getMap()[pos.second + 1][pos.first] != '#' && _snakeBody.getDir() != Nibbler::Direction::UP)
                _snakeBody.setDir(Nibbler::Direction::DOWN);
            break;
        case LEFT:
            if (_snakeBody.getMap()[pos.second][pos.first - 1] != '#' && _snakeBody.getDir() != Nibbler::Direction::RIGHT)
                _snakeBody.setDir(Nibbler::Direction::LEFT);
            break;
        case RIGHT:
            if (_snakeBody.getMap()[pos.second][pos.first + 1] != '#' && _snakeBody.getDir() != Nibbler::Direction::LEFT)
                _snakeBody.setDir(Nibbler::Direction::RIGHT);
            break;
        case RESTART:
            this->restart();
            break;
        default:
            break;
    }
}

void arcade::Nibbler::setWall(std::pair<std::size_t, std::size_t> pos) {
    auto wall = createTile();
    wall.get()->setPosition(pos);
    wall.get()->setColor(arcade::Color::BLUE);
    _obj.push_back(wall);


}
void arcade::Nibbler::checkCollision() {
    for (unsigned long i = 1; i != _snakeBody.getSnake().size(); i++) {
        if (_snakeBody.getSnake()[0] == _snakeBody.getSnake()[i]) {
            this->restart();
            break;
        }
    }
}

void arcade::Nibbler::createWall() {
    int j;

    for (std::size_t i = 0; i < _snakeBody.getMap().size(); i++) {
        for (j = 0; _snakeBody.getMap()[i][j] != '\0'; j++) {
            if (_snakeBody.getMap()[i][j] == '#')
                this->setWall({j, i});
        }
    }
}

void arcade::Nibbler::SnakeGame::clear() {
    _mapGame.clear();
    _mapSave.clear();
    _snakeGame.clear();
}

arcade::Input arcade::Nibbler::event(arcade::Input input) {
    (void)input;
    return UNDEFINED;
}

// ----------------- SnakeGame -----------------

arcade::Nibbler::SnakeGame::SnakeGame() {
    this->restart();
    initMap();
}

arcade::Nibbler::SnakeGame::~SnakeGame() {}

std::vector<std::pair<std::size_t, std::size_t>> arcade::Nibbler::SnakeGame::getSnake() const {
    return _snakeGame;
}

void arcade::Nibbler::SnakeGame::findSnakePos(std::string str, std::size_t i) {
    for (std::size_t j = 0; str[j] != '\0'; j++) {
        if (str[j] == 'S') {
            _snakeGame.push_back({j, i});
            break;
        }
    }
}

std::vector<std::string> arcade::Nibbler::SnakeGame::getMap() const {
    return _mapGame;
}

void arcade::Nibbler::SnakeGame::initMap() {
    std::size_t i = 0;
    std::ifstream ifs("assets/nibbler_map.txt");
    std::string tmp = "";

    if (ifs.is_open()) {
        while (getline(ifs, tmp)) {
            this->findSnakePos(tmp, i);
            _mapGame.push_back(tmp);
            _mapSave.push_back(tmp);
            i++;
        }
    }
    ifs.close();
    if (_snakeGame[0].first == 0 && _snakeGame[0].second == 0)
        throw Error("Pacman : Pacman player not found\n");
}

bool arcade::Nibbler::SnakeGame::moveBody(std::pair<std::size_t, std::size_t> posFood) {
    bool eaten = false;
    if (_snakeGame[0] == posFood) {
        posFood = randPair();
        _snakeGame.push_back(_snakeGame.back());
        eaten = true;
    }
    for (size_t i = _snakeGame.size() - 1; i != 0; i--) {
        _snakeGame[i] = _snakeGame[i - 1];
    }
    return eaten;
}

bool arcade::Nibbler::SnakeGame::Move(std::pair<std::size_t, std::size_t> posFood, std::pair<std::size_t, std::size_t> pos) {
    bool eaten = false;
    switch (_dir) {
        case Direction::UP:
            if (_mapGame[pos.second - 1][pos.first] != '#') {
                eaten = this->moveBody(posFood);
                _snakeGame[0].second -= GRID_SIZE;
            }
            break;
        case Direction::DOWN:
            if (_mapGame[pos.second + 1][pos.first] != '#') {
                eaten = this->moveBody(posFood);
                _snakeGame[0].second += GRID_SIZE;
            }
            break;
        case Direction::LEFT:
            if (_mapGame[pos.second][pos.first - 1] != '#') {
                eaten = this->moveBody(posFood);
                _snakeGame[0].first -= GRID_SIZE;
            }
            break;
        case Direction::RIGHT:
            if (_mapGame[pos.second][pos.first + 1] != '#') {
                eaten = this->moveBody(posFood);
                _snakeGame[0].first += GRID_SIZE;
            }
            break;
    }
    return eaten;
}

void arcade::Nibbler::SnakeGame::setDir(Direction dir) {
    _dir = dir;
}

arcade::Nibbler::Direction arcade::Nibbler::SnakeGame::getDir() const {
    return _dir;
}

void arcade::Nibbler::SnakeGame::restart() {
    _snakeGame.clear();
    _snakeGame.push_back({MAP_WIDTH / 2, MAP_HEIGHT / 2});
    _snakeGame.push_back({MAP_WIDTH / 2, MAP_HEIGHT / 2});
    _snakeGame.push_back({MAP_WIDTH / 2, MAP_HEIGHT / 2});
}

