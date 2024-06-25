#include "termSnake.h"

S21ViewTerm::S21ViewTerm(S21ModelTerm& model) : model(model) {}

void S21ViewTerm::handleUserInputTerm(char key) {
  switch (key) {
    case 'w':
      if (model.obj.snake[0].row != model.obj.snake[1].row + 1) {
        model.obj.dir = up;
      }
      break;
    case 'a':
      if (model.obj.snake[0].col != model.obj.snake[1].col + 1) {
        model.obj.dir = left;
      }
      break;
    case 's':
      if (model.obj.snake[0].row != model.obj.snake[1].row - 1) {
        model.obj.dir = down;
      }
      break;
    case 'd':
      if (model.obj.snake[0].col != model.obj.snake[1].col - 1) {
        model.obj.dir = right;
      }
      break;
    case 'e':
      boost = true;
      break;
    case 'c':
      model.obj.state = pauseState;
      break;
    case 'x':
      model.obj.state = gameState;
      break;
    case 'q':
      model.obj.state = terminateState;
      break;
    default:
      break;
  }
}

void S21ViewTerm::printField() {
  Objects obj = model.obj;
  clear();
  // Game field
  for (int i = 0; i < ROW; ++i) {
    for (int j = 0; j < COL; ++j) {
      if (obj.field[i][j]) {
        printw("@ ");
      } else {
        printw(". ");
      }
    }
    printw("\n");
  }

  mvprintw(0, 25, "CONTROL KEYS");
  mvprintw(2, 23, "Up - 'W'");
  mvprintw(4, 23, "Down - 'S'");
  mvprintw(2, 35, "Left - 'A'");
  mvprintw(4, 35, "Right - 'D'");
  mvprintw(6, 23, "Boost - 'E'");

  mvprintw(10, 23, "Pause - 'C'");
  mvprintw(12, 23, "Unpause - 'X'");
  mvprintw(14, 23, "Quit the Tetris - 'Q'");

  mvprintw(0, 60, "SESSION INFO");
  mvprintw(2, 58, "Apples = %d", model.obj.applesCounter);
  mvprintw(4, 58, "Max score = %d", model.obj.maxScore);
  mvprintw(6, 58, "Lvl = %d", model.obj.lvl);
  mvprintw(8, 58, "Speed = %d", model.obj.speed);

  refresh();
}
