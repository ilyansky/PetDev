#include "termSnake.h"

// CONTROLLER
S21ControllerTerm::S21ControllerTerm(S21ModelTerm& model, S21ViewTerm& view)
    : model(model), view(view) {
  initGame();
}

void S21ControllerTerm::initGame() {
  srand(time(0));

  initscr();
  noecho();
  nodelay(stdscr, TRUE);
  curs_set(0);

  gameLoop();

  endwin();
}

void S21ControllerTerm::gameLoop() {
  while (true) {
    int delay;

    view.handleUserInputTerm(getch());
    model.checkState();

    if (model.obj.state == terminateState) {
      return;
    }

    switch (model.obj.state) {
      case winState:
        clear();
        printw("You are winner!");
        refresh();

        while (true) {
          char ch = getch();
          if (ch == 'q') {
            return;
          }
        }

        break;
      case gameOverState:
        clear();
        printw("Game over");
        refresh();
        break;
      default:
        if (isBoost()) {
          delay = BOOSTED_DELAY;
        } else {
          delay = model.obj.delay;
        }

        view.printField();
        break;
    }
    napms(delay);
  }
}

bool S21ControllerTerm::isBoost() {
  if (view.boost) {
    view.boost = false;
    return true;
  }
  return false;
}

// MODEL
S21ModelTerm::S21ModelTerm() {}

// Game state
void S21ModelTerm::checkState() {
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

bool S21ModelTerm::isSnakeCollapsed() {
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

void S21ModelTerm::eatApple() {
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

void S21ModelTerm::spawnApple() {
  int row;
  int col;

  do {
    row = rand() % ROW;
    col = rand() % COL;
  } while (isAppleInSnake(Point(row, col)));

  obj.apple = Point(row, col);
}

bool S21ModelTerm::isAppleInSnake(Point apple) {
  for (int i = 0; i < obj.snake.size(); ++i) {
    if (obj.snake[i].row == apple.row && obj.snake[i].col == apple.col) {
      return true;
    }
  }
  return false;
}

void S21ModelTerm::moveSnake() {
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

void S21ModelTerm::configureField() {
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
void S21ModelTerm::readMaxScore() {
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

void S21ModelTerm::isNewMaxScore() {
  if (obj.maxScore < obj.applesCounter) {
    updateMaxScore();
  }
}

void S21ModelTerm::updateMaxScore() {
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

void S21ModelTerm::isNextLvl() {
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

void S21ModelTerm::secretEnd() {
  int snakeSize = obj.snake.size();
  for (int i = 0; i < (ROW * COL) - snakeSize; ++i) {
    obj.snake.push_back(Point(0, 0));
  }
}
