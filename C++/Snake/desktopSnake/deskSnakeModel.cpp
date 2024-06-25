#include "deskSnake.h"

S21SnakeModel::S21SnakeModel() {}

void S21SnakeModel::checkState() {
  if (obj.snake.size() == ROW * COL) {
    obj.state = winState;
  }

  switch (obj.state) {
    case gameState:
      if (!isSnakeCollapsed()) {
        readMaxScore();
        eatApple();
        isNextLvl();
        moveSnake();
        configureField();
      } else {
        obj.state = gameOverState;
      }
      break;
    default:
      break;
  }
}

// Game state
bool S21SnakeModel::isSnakeCollapsed() {
  bool ret = false;
  Point head = obj.snake[0];
  // Check borders
  switch (obj.dir) {
    case up:
      if (head.row - 1 < 0) {
        ret = true;
      }
      break;
    case down:
      if (head.row + 1 >= ROW) {
        ret = true;
      }
      break;
    case left:
      if (head.col - 1 < 0) {
        ret = true;
      }
      break;
    case right:
      if (head.col + 1 >= COL) {
        ret = true;
      }
      break;
  }

  for (int i = 1; i < obj.snake.size(); ++i) {
    if (obj.snake[i].row == head.row && obj.snake[i].col == head.col) {
      ret = true;
      break;
    }
  }

  return ret;
}

void S21SnakeModel::eatApple() {
  Point head = obj.snake[0];
  if (head.row == obj.apple.row && head.col == obj.apple.col) {
    obj.applesCounter += 1;
    readMaxScore();
    isNewMaxScore();
    obj.snake.push_back(Point(0, 0));
    spawnApple();
    // secretEnd();
  }
}

void S21SnakeModel::spawnApple() {
  int row;
  int col;

  do {
    row = rand() % ROW;
    col = rand() % COL;
  } while (isAppleInSnake(Point(row, col)));

  obj.apple = Point(row, col);
}

bool S21SnakeModel::isAppleInSnake(Point apple) {
  for (int i = 0; i < obj.snake.size(); ++i) {
    if (obj.snake[i].row == apple.row && obj.snake[i].col == apple.col) {
      return true;
    }
  }
  return false;
}

void S21SnakeModel::moveSnake() {
  // Move tail
  for (int i = obj.snake.size() - 1; i >= 1; --i) {
    obj.snake[i].row = obj.snake[i - 1].row;
    obj.snake[i].col = obj.snake[i - 1].col;
  }

  // Move head
  switch (obj.dir) {
    case up:
      obj.snake[0].row -= 1;
      break;
    case left:
      obj.snake[0].col -= 1;
      break;
    case down:
      obj.snake[0].row += 1;
      break;
    case right:
      obj.snake[0].col += 1;
      break;
  }
}

void S21SnakeModel::configureField() {
  for (int i = 0; i < ROW; ++i) {
    for (int j = 0; j < COL; ++j) {
      obj.field[i][j] = false;
    }
  }

  Point apple = obj.apple;
  obj.field[apple.row][apple.col] = true;

  for (int i = 0; i < obj.snake.size(); ++i) {
    Point snakeCell = obj.snake[i];
    obj.field[snakeCell.row][snakeCell.col] = true;
  }
}

// Max score / lvl imp
void S21SnakeModel::readMaxScore() {
  std::ifstream file(FILENAME);
  if (!file) {
    std::cerr << "Failed to open file" << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line)) {
    obj.maxScore = std::stoi(line);
  }
}

void S21SnakeModel::isNewMaxScore() {
  if (obj.maxScore < obj.applesCounter) {
    updateMaxScore();
  }
}

void S21SnakeModel::updateMaxScore() {
  obj.maxScore = obj.applesCounter;
  try {
    std::ofstream file(FILENAME);
    if (!file) {
      throw std::ios_base::failure("Failed to open file");
    }
    file << obj.maxScore;
  } catch (const std::ios_base::failure& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return;
  }
}

void S21SnakeModel::isNextLvl() {
  if (obj.lvl != 10) {
    if (obj.applesCounter % 5 == 0 &&
        obj.applesCounter != obj.oldApplesAmount) {
      obj.oldApplesAmount = obj.applesCounter;
      obj.lvl += 1;
      obj.speed += 10;
      obj.delay -= 20;
      m_isNextLvl = true;
    }
  }
}


/*
void S21SnakeModel::secretEnd() {
  int snakeSize = obj.snake.size();
  for (int i = 0; i < (ROW * COL) - snakeSize; ++i) {
    obj.snake.push_back(Point(0, 0));
  }
}
*/