#ifndef TERMINAL_SNAKE_H
#define TERMINAL_SNAKE_H

#define ROW 20
#define COL 10
#define DELAY 300
#define BOOSTED_DELAY 100
#define FILENAME "maxScore.txt"

#include <ncurses.h>

#include <fstream>
#include <iostream>
#include <string>

#include "gtest/gtest.h"

struct Point {
  int row;
  int col;

  Point(int r, int c) : row(r), col(c) {}
};

typedef enum { up, left, down, right } Direction;

typedef enum {
  gameState,
  pauseState,
  gameOverState,
  winState,
  terminateState
} State;

struct Objects {
  std::vector<std::vector<bool>> field;
  std::vector<Point> snake;
  Point apple;
  Direction dir;
  State state;

  int applesCounter;
  int maxScore;

  int delay;
  int lvl;
  int speed;
  int oldApplesAmount;

  Objects(Direction dir = right, State state = gameState, int applesCounter = 0,
          int maxScore = 0, int delay = DELAY, int lvl = 1, int speed = 10,
          int oldApplesAmount = 0)
      : field(ROW, std::vector<bool>(COL, false)),
        snake(),
        apple(10, 5),
        dir(dir),
        state(state),
        applesCounter(applesCounter),
        maxScore(maxScore),
        delay(delay),
        lvl(lvl),
        speed(speed),
        oldApplesAmount(oldApplesAmount) {
    // Init start snake = 4 cells
    for (int i = 3; i >= 0; --i) {
      snake.push_back(Point(0, i));
    }
  }
};

class S21ModelTerm {
 public:
  S21ModelTerm();

  Objects obj;
  bool m_isNextLvl = false;

  // Game state
  void checkState();
  bool isSnakeCollapsed();
  void eatApple();
  void spawnApple();
  bool isAppleInSnake(Point apple);
  void moveSnake();
  void configureField();

  // Max score / lvl imp
  void readMaxScore();
  void isNewMaxScore();
  void updateMaxScore();
  void isNextLvl();

  void secretEnd();
};

class S21ViewTerm {
 public:
  S21ViewTerm(S21ModelTerm& model);

  bool boost = false;

  void handleUserInputTerm(char key);
  void printField();

 private:
  S21ModelTerm& model;
};

class S21ControllerTerm {
 public:
  S21ControllerTerm(S21ModelTerm& model, S21ViewTerm& view);

 private:
  S21ModelTerm& model;
  S21ViewTerm& view;

  int m_timer;

  void initGame();
  void gameLoop();
  bool isBoost();
};

#endif