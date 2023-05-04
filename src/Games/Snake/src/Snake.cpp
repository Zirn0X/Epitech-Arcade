/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Snake
*/

#include "../includes/Snake.hpp"

static std::pair<std::size_t, std::size_t> randPair() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 18);

    return std::make_pair(dis(gen), dis(gen));
}

// ----------------- Snake -----------------

arcade::Snake::Snake() {
    this->createSnake();
    _map = std::make_pair(MAP_HEIGHT, MAP_WIDTH);
    _food = randPair();
    _text = std::make_pair(20, 1);
    _scoreText = std::make_pair(20, 2);
    _scorePoint = std::make_pair(20, 3);
    _score = 0;
}
arcade::Snake::~Snake() {
    _obj.clear();
}

std::shared_ptr<arcade::ITile> arcade::Snake::createTile() {
    return std::make_shared<arcade::Tile>();
}

std::shared_ptr<arcade::IText> arcade::Snake::createText() {
    return std::make_shared<arcade::Text>();
}

std::shared_ptr<arcade::ISound> arcade::Snake::createSound() {
    return std::make_shared<arcade::Sound>();
}


void arcade::Snake::restart() {
    _score = 0;
    _food = randPair();
    _snakeBody.restart();
}

void arcade::Snake::createSnake() {
    auto snakebody = _snakeBody.getSnake();
    for (unsigned long i = 0; snakebody.size() != i; i++) {
        auto snake = createTile();
        snake.get()->setPosition({snakebody[i].first, snakebody[i].second});
        snake.get()->setColor(arcade::Color::YELLOW);
        _obj.push_back(snake);
    }
}

void arcade::Snake::setMap(std::pair<std::size_t , std::size_t> pos) {
    auto map = createTile();
    map.get()->setPosition({pos.first, pos.second});
    map.get()->setColor(arcade::Color::WHITE);
    _obj.push_back(map);
}

void arcade::Snake::createMap() {
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

void arcade::Snake::createFood(std::pair<std::size_t , std::size_t> pos) {
    auto food = createTile();
    food.get()->setPosition(pos);
    food.get()->setColor(arcade::Color::RED);
    _obj.push_back(food);
}

void arcade::Snake::setText(std::pair<std::size_t , std::size_t> pos, std::string txt) {
    auto text = createText();
    text.get()->setPosition(pos);
    text.get()->setText(txt);
    _obj.push_back(text);
}

std::vector<std::shared_ptr<arcade::IObject>> arcade::Snake::loop(arcade::Input input) {
    this->execInput(input);
    if (_snakeBody.Move(_food)) {
        _food = randPair();
        _score += 1;
    }
    this->checkCollision();
    _obj.clear();
    setText(_text, "Snake");
    setText(_scoreText, "Score");
    setText(_scorePoint, std::to_string(_score));
    createFood(_food);
    createSnake();
    createMap();
    return _obj;
}

void arcade::Snake::execInput(arcade::Input input) {
    switch (input) {
        case UP:
            if (_snakeBody.getDir() != Snake::Direction::DOWN)
                _snakeBody.setDir(Snake::Direction::UP);
            break;
        case DOWN:
            if (_snakeBody.getDir() != Snake::Direction::UP)
                _snakeBody.setDir(Snake::Direction::DOWN);
            break;
        case LEFT:
            if (_snakeBody.getDir() != Snake::Direction::RIGHT)
                _snakeBody.setDir(Snake::Direction::LEFT);
            break;
        case RIGHT:
            if (_snakeBody.getDir() != Snake::Direction::LEFT)
                _snakeBody.setDir(Snake::Direction::RIGHT);
            break;
        case RESTART:
            this->restart();
            break;
        default:
            break;
    }
}

void arcade::Snake::checkCollision() {
    if (_snakeBody.getSnake()[0].first == 0 || _snakeBody.getSnake()[0].first == MAP_HEIGHT - 1 || _snakeBody.getSnake()[0].second == 0 || _snakeBody.getSnake()[0].second == MAP_WIDTH - 1)
        this->restart();
    for (unsigned long i = 1; i != _snakeBody.getSnake().size(); i++) {
        if (_snakeBody.getSnake()[0] == _snakeBody.getSnake()[i]) {
            this->restart();
            break;
        }
    }
}

arcade::Input arcade::Snake::event(arcade::Input input) {
    (void)input;
    return UNDEFINED;
}

// ----------------- SnakeGame -----------------

arcade::Snake::SnakeGame::SnakeGame() {
    this->restart();
}

arcade::Snake::SnakeGame::~SnakeGame() {}

std::vector<std::pair<std::size_t, std::size_t>> arcade::Snake::SnakeGame::getSnake() const {
    return _snake;
}

bool arcade::Snake::SnakeGame::moveBody(std::pair<std::size_t, std::size_t> posFood) {
    bool eaten = false;
    if (_snake[0] == posFood) {
        posFood = randPair();
        _snake.push_back(_snake.back());
        eaten = true;
    }
    for (size_t i = _snake.size() - 1; i != 0; i--) {
        _snake[i] = _snake[i - 1];
    }
    return eaten;
}

bool arcade::Snake::SnakeGame::Move(std::pair<std::size_t, std::size_t> posFood) {
    bool eaten = this->moveBody(posFood);
    switch (_dir) {
        case Direction::UP:
            _snake[0].second -= GRID_SIZE;
            break;
        case Direction::DOWN:
            _snake[0].second += GRID_SIZE;
            break;
        case Direction::LEFT:
            _snake[0].first -= GRID_SIZE;
            break;
        case Direction::RIGHT:
            _snake[0].first += GRID_SIZE;
            break;
    }
    return eaten;
}

void arcade::Snake::SnakeGame::setDir(Direction dir) {
    _dir = dir;
}

arcade::Snake::Direction arcade::Snake::SnakeGame::getDir() const {
    return _dir;
}

void arcade::Snake::SnakeGame::restart() {
    _snake.clear();
    _snake.push_back({MAP_HEIGHT / 2, MAP_WIDTH / 2});
    _snake.push_back({MAP_HEIGHT / 2, MAP_WIDTH / 2});
    _snake.push_back({MAP_HEIGHT / 2, MAP_WIDTH / 2});
}

extern "C" arcade::Snake *entryPoint() {
    return new arcade::Snake;
}
