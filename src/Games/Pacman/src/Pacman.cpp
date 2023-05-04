/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-antony.jin
** File description:
** Pacman
*/

#include "../includes/Pacman.hpp"

arcade::Pacman::Pacman() {
    _text = std::make_pair(20, 1);
    _scoreText = std::make_pair(20, 2);
    _scorePoint = std::make_pair(20, 3);
    _pacman = {0, 0};
    for (int i = 0; i < 4; i++)
        _enemies.push_back({0, 0});
}

arcade::Pacman::~Pacman() {
    _obj.clear();
    _enemies.clear();
}

std::vector<std::shared_ptr<arcade::IObject>> arcade::Pacman::Pacman::loop(arcade::Input input) {
    _obj.clear();
    setText(_text, "Pacman");
    setText(_scoreText, "Score");
    setText(_scorePoint, std::to_string(_pacGame.getScore()));
    this->execInput(input, _pacGame.getPacman());
    _pacGame.Move(_pacGame.getPacman());
    for (int i = 0; i < 4; i++)
        _pacGame.enemyMove(_pacGame.getEnemiesDir()[i], i);
    this->createWall();
    this->createFloor();
    this->createFood();
    this->createEntity();
    return _obj;
}

void arcade::Pacman::Pacman::restart() {
    _pacGame.restart();
}

std::shared_ptr<arcade::ITile> arcade::Pacman::Pacman::createTile() {
    return std::make_shared<arcade::Tile>();
}

std::shared_ptr<arcade::ISound> arcade::Pacman::Pacman::createSound() {
    return std::make_shared<arcade::Sound>();
}

std::shared_ptr<arcade::IText> arcade::Pacman::Pacman::createText() {
    return std::make_shared<arcade::Text>();
}

void arcade::Pacman::createWall() {
    int j;

    for (std::size_t i = 0; i < _pacGame.getMap().size(); i++) {
        for (j = 0; _pacGame.getMap()[i][j] != '\0'; j++) {
            if (_pacGame.getMap()[i][j] == '#')
                this->setWall({j, i});
        }
    }
}

void arcade::Pacman::createFloor() {
     int j;

    for (std::size_t i = 0; i < _pacGame.getMap().size(); i++) {
        for (j = 0; _pacGame.getMap()[i][j] != '\0'; j++) {
            if (_pacGame.getMap()[i][j] == ' ')
                this->setFloor({j, i});
        }
    }
}

void arcade::Pacman::createFood() {
    int j;

    for (std::size_t i = 0; i < _pacGame.getMap().size(); i++) {
        for (j = 0; _pacGame.getMap()[i][j] != '\0'; j++) {
            if (_pacGame.getMap()[i][j] == '.' || _pacGame.getMap()[i][j] == 'o')
                this->setFood({j, i}, _pacGame.getMap()[i][j]);
        }
    }
}

void arcade::Pacman::createEntity() {
    auto pacman = _pacGame.getPacman();
    auto entity = this->createTile();
    entity.get()->setPosition(pacman);
    entity.get()->setColor(arcade::Color::GREEN);
    _obj.push_back(entity);
    for (int i = 0; i < 4; i++) {
        auto enemy = this->createTile();
        enemy.get()->setPosition(_pacGame.getEnemies()[i]);
        if (_pacGame.getEatingMod()) {
            enemy.get()->setColor(arcade::Color::GREEN);
        } else
            enemy.get()->setColor(arcade::Color::RED);
        _obj.push_back(enemy);
    }
}

void arcade::Pacman::setWall(std::pair<std::size_t, std::size_t> pos) {
    auto wall = createTile();
    wall.get()->setPosition(pos);
    wall.get()->setColor(arcade::Color::BLUE);
    _obj.push_back(wall);
}

void arcade::Pacman::setFloor(std::pair<std::size_t, std::size_t> pos) {
    auto floor = createTile();
    floor.get()->setPosition(pos);
    floor.get()->setColor(arcade::Color::DARK);
    _obj.push_back(floor);
}

void arcade::Pacman::setFood(std::pair<std::size_t, std::size_t> pos, char c) {
    if (c == '.' || c == 'o') {
        auto food = createTile();
        food.get()->setPosition(pos);
        if (c == '.')
            food.get()->setColor(arcade::Color::YELLOW);
        else if (c == 'o')
            food.get()->setColor(arcade::Color::WHITE);
        _obj.push_back(food);
    }
}

void arcade::Pacman::setText(std::pair<std::size_t , std::size_t> pos, std::string txt) {
    auto text = createText();
    text.get()->setPosition(pos);
    text.get()->setText(txt);
    _obj.push_back(text);
}

void arcade::Pacman::execInput(arcade::Input input, std::pair<std::size_t, std::size_t> pos) {
    switch (input) {
        case UP:
            if (_pacGame.getMap()[pos.second - 1][pos.first] != '#')
                _pacGame.setDir(arcade::Input::UP);
            break;
        case DOWN:
            if (_pacGame.getMap()[pos.second + 1][pos.first] != '#')
                _pacGame.setDir(arcade::Input::DOWN);
            break;
        case LEFT:
            if (_pacGame.getMap()[pos.second][pos.first - 1] != '#')
                _pacGame.setDir(arcade::Input::LEFT);
            break;
        case RIGHT:
            if (_pacGame.getMap()[pos.second][pos.first + 1] != '#')
                _pacGame.setDir(arcade::Input::RIGHT);
            break;
        case RESTART:
            this->restart();
            break;
        default:
            break;
    }
}

arcade::Input arcade::Pacman::event(arcade::Input input) {
    (void)input;
    return UNDEFINED;
}

// ----------------- PacmanGame -----------------

arcade::Pacman::PacmanGame::PacmanGame() {
    _pacmanGame = {0, 0};
        for (int i = 0; i < 4; i++) {
        _enemiesGame.push_back({0, 0});
        _enemiesDir.push_back(RIGHT);
    }
    initMap();
}

arcade::Pacman::PacmanGame::~PacmanGame() {}

// Read and get the map content
void arcade::Pacman::PacmanGame::initMap() {
    std::size_t i = 0;
    std::ifstream ifs("assets/mapPacman.txt");
    std::string tmp = "";

    if (ifs.is_open()) {
        while (getline(ifs, tmp)) {
            this->findPacmanPos(tmp, i);
            this->findEnemiesPos(tmp, i);
            _mapGame.push_back(tmp);
            _mapSave.push_back(tmp);
            i++;
        }
    }
    ifs.close();
    if (_pacmanGame.first == 0 && _pacmanGame.second == 0)
        throw Error("Pacman : Pacman player not found\n");
}

void arcade::Pacman::PacmanGame::findPacmanPos(std::string str, std::size_t i) {
    for (std::size_t j = 0; str[j] != '\0'; j++) {
        if (str[j] == 'P') {
            _pacmanGame = {j, i};
            break;
        }
    }
}

void arcade::Pacman::PacmanGame::findEnemiesPos(std::string str, std::size_t i) {
    for (std::size_t j = 0; str[j] != '\0'; j++) {
        if (str[j] == '0')
            _enemiesGame[0] = {j, i};
        if (str[j] == '1')
            _enemiesGame[1] = {j, i};
        if (str[j] == '2')
            _enemiesGame[2] = {j, i};
        if (str[j] == '3')
            _enemiesGame[3] = {j, i};
    }
}

std::pair<std::size_t, std::size_t> arcade::Pacman::PacmanGame::getPacman() const {
    return _pacmanGame;
}

std::vector<std::string> arcade::Pacman::PacmanGame::getMap() const {
    return _mapGame;
}

std::vector<std::pair<std::size_t, std::size_t>> arcade::Pacman::PacmanGame::getEnemies() const {
    return _enemiesGame;
}

int arcade::Pacman::PacmanGame::getTick() const {
    return _tick;
}

std::vector<arcade::Input> arcade::Pacman::PacmanGame::getEnemiesDir() const {
    return _enemiesDir;
}

bool arcade::Pacman::PacmanGame::getEatingMod() const {
    return _eatingMod;
}

int arcade::Pacman::PacmanGame::getScore() const {
    return _score;
}


void arcade::Pacman::PacmanGame::setDir(arcade::Input input) {
    _input = input;
}

bool arcade::Pacman::PacmanGame::enemyPos() {
    for (int i = 0; i < 4; i++) {
        if (_pacmanGame == _enemiesGame[i] && !_canEat)
            return true;
        if (_pacmanGame == _enemiesGame[i] && _canEat) {
            _enemiesGame[i] = {9, 7};
            _score += 400;
        }
    }
    return false;
}

void arcade::Pacman::PacmanGame::Move(std::pair<std::size_t, std::size_t> pos) {
    if (_tick > _tickSave) {
        _canEat = false;
        _eatingMod = false;
    }
    switch (_input) {
        case arcade::Input::UP:
            if (_mapGame[pos.second - 1][pos.first] != '#') {
                _pacmanGame.second -= GRID_SIZE;
                _mapGame[pos.second][pos.first] = ' ';
                if (_mapGame[pos.second - 1][pos.first] == '.')
                    _score++;
                if (_mapGame[pos.second - 1][pos.first] == 'o') {
                    _tickSave = _tick + 100;
                    _eatingMod = true;
                    _canEat = true;
                }
            }
            break;
        case arcade::Input::DOWN:
            if (_mapGame[pos.second + 1][pos.first] != '#') {
                _pacmanGame.second += GRID_SIZE;
                _mapGame[pos.second][pos.first] = ' ';
                if (_mapGame[pos.second + 1][pos.first] == '.')
                    _score++;
                if (_mapGame[pos.second + 1][pos.first] == 'o') {
                    _tickSave = _tick + 100;
                    _eatingMod = true;
                    _canEat = true;
                }
            }
            break;
        case arcade::Input::LEFT:
            if (_mapGame[pos.second][pos.first - 1] != '#') {
                _pacmanGame.first -= GRID_SIZE;
                _mapGame[pos.second][pos.first] = ' ';
                if (_mapGame[pos.second][pos.first - 1] == '.')
                    _score++;
                if (_mapGame[pos.second][pos.first - 1] == 'o') {
                    _tickSave = _tick + 100;
                    _eatingMod = true;
                    _canEat = true;
                }
                if (pos.first == 0 && pos.second == 9)
                    _pacmanGame = {18, 9};
            }
            break;
        case arcade::Input::RIGHT:
            if (_mapGame[pos.second][pos.first + 1] != '#') {
                _pacmanGame.first += GRID_SIZE;
                _mapGame[pos.second][pos.first] = ' ';
                if (_mapGame[pos.second][pos.first + 1] == '.')
                    _score++;
                if (_mapGame[pos.second][pos.first + 1] == 'o') {
                    _tickSave = _tick + 100;
                    _eatingMod = true;
                    _canEat = true;
                }
                if (pos.first == 18 && pos.second == 9)
                    _pacmanGame = {0, 9};
            }
            break;
        default:
            break;
    }
    if (this->foodEaten())
        this->resetFood();
    if (this->enemyPos()) {
        this->setDir(UNDEFINED);
        this->restart();
        return;
    }
}

void arcade::Pacman::PacmanGame::enemyMove(arcade::Input input, int id) {
    int enemyDirs[2];

    this->enemyOut();
    if (this->enemyPos()) {
        this->setDir(UNDEFINED);
        this->restart();
        return;
    }
    if (_tick % 10 && input == UP && _mapGame[_enemiesGame[id].second - 1][_enemiesGame[id].first] == '#') {
        enemyDirs[0] = arcade::Input::LEFT;
        enemyDirs[1] = arcade::Input::RIGHT;
        _enemiesDir[id] = static_cast<arcade::Input>(enemyDirs[rand() % 2]);
    } else if (_tick % 10 && input == RIGHT && _mapGame[_enemiesGame[id].second][_enemiesGame[id].first + 1] == '#') {
        enemyDirs[0] = arcade::Input::UP;
        enemyDirs[1] = arcade::Input::DOWN;
        _enemiesDir[id] = static_cast<arcade::Input>(enemyDirs[rand() % 2]);
    } else if (_tick % 10 && input == DOWN && _mapGame[_enemiesGame[id].second + 1][_enemiesGame[id].first] == '#') {
        enemyDirs[0] = arcade::Input::LEFT;
        enemyDirs[1] = arcade::Input::RIGHT;
        _enemiesDir[id] = static_cast<arcade::Input>(enemyDirs[rand() % 2]);
    } else if (_tick % 10 && input == LEFT && _mapGame[_enemiesGame[id].second][_enemiesGame[id].first - 1] == '#') {
        enemyDirs[0] = arcade::Input::UP;
        enemyDirs[1] = arcade::Input::DOWN;
        _enemiesDir[id] = static_cast<arcade::Input>(enemyDirs[rand() % 2]);
    }
    switch (_enemiesDir[id]) {
        case UP:
            if (_mapGame[_enemiesGame[id].second][_enemiesGame[id].first] == '0')
                _mapGame[_enemiesGame[id].second][_enemiesGame[id].first] = ' ';
            if (_mapGame[_enemiesGame[id].second - 1][_enemiesGame[id].first] != '#')
                _enemiesGame[id].second -= GRID_SIZE;
            break;
        case DOWN:
            if (_mapGame[_enemiesGame[id].second][_enemiesGame[id].first] == '0')
                _mapGame[_enemiesGame[id].second][_enemiesGame[id].first] = ' ';
            if (_mapGame[_enemiesGame[id].second + 1][_enemiesGame[id].first] != '#')
                _enemiesGame[id].second += GRID_SIZE;
            break;
        case RIGHT:
            if (_mapGame[_enemiesGame[id].second][_enemiesGame[id].first] == '0')
                _mapGame[_enemiesGame[id].second][_enemiesGame[id].first] = ' ';
            if (_mapGame[_enemiesGame[id].second][_enemiesGame[id].first + 1] != '#')
                _enemiesGame[id].first += GRID_SIZE;
            if (_enemiesGame[id].first == 18 && _enemiesGame[id].second == 9)
                _enemiesGame[id] = {0, 9};
            break;
        case LEFT:
            if (_mapGame[_enemiesGame[id].second][_enemiesGame[id].first] == '0')
                _mapGame[_enemiesGame[id].second][_enemiesGame[id].first] = ' ';
            if (_mapGame[_enemiesGame[id].second][_enemiesGame[id].first - 1] != '#')
                _enemiesGame[id].first -= GRID_SIZE;
            if (_enemiesGame[id].first == 0 && _enemiesGame[id].second == 9)
                _enemiesGame[id] = {18, 9};
            break;
        default:
            break;
    }
    _tick++;
}

void arcade::Pacman::PacmanGame::enemyOut() {
    switch (_tick) {
    case 20:
        _enemiesGame[1] = {9, 7};
        break;
    case 40:
        _enemiesGame[2] = {9, 7};
        break;
    case 60:
        _enemiesGame[3] = {9, 7};
        break;
    default:
        break;
    }
}

bool arcade::Pacman::PacmanGame::foodEaten() {
    int cpt = 0;

    for (unsigned long i = 0; i < _mapGame.size(); i++) {
        for (unsigned long j = 0; _mapGame[i][j] != '\0'; j++)
            if (_mapGame[i][j] == '.' || _mapGame[i][j] == 'o')
                cpt++;
    }
    if (cpt == 0)
        return true;
    return false;
}

void arcade::Pacman::PacmanGame::resetFood() {
    this->clear();
    _input = arcade::Input::RIGHT;
    _pacmanGame = {0, 0};
    _tick = 0;
    for (int i = 0; i < 4; i++) {
        _enemiesGame.push_back({0, 0});
        _enemiesDir.push_back(RIGHT);
    }
    initMap();
}

void arcade::Pacman::PacmanGame::setMap(std::pair<std::size_t, std::size_t> pos, char c) {
    _mapGame[pos.first][pos.second] = c;
}

void arcade::Pacman::PacmanGame::clear() {
    _mapGame.clear();
    _mapSave.clear();
    _enemiesGame.clear();
}

void arcade::Pacman::PacmanGame::restart() {
    this->clear();
    _input = arcade::Input::RIGHT;
    _pacmanGame = {0, 0};
    _tick = 0;
    _score = 0;
    for (int i = 0; i < 4; i++) {
        _enemiesGame.push_back({0, 0});
        _enemiesDir.push_back(RIGHT);
    }
    initMap();
}

extern "C" arcade::Pacman *entryPoint() {
    return new arcade::Pacman;
}
