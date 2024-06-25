#ifndef DESKTOP_SNAKE_H
#define DESKTOP_SNAKE_H

#define ROW 20
#define COL 10
#define CSIZE 20
#define DELAY 300
#define BOOSTED_DELAY 100
#define FILENAME "maxScore.txt"

#include <QApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>
#include <QPoint>
#include <QTime>
#include <QVector>
#include <QWidget>
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

class S21SnakeModel {
 public:
  S21SnakeModel();
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

  // void secretEnd();
};

class S21SnakeView : public QWidget {
 public:
  S21SnakeView(S21SnakeModel& model);

  bool boost = false;
  void initGame();
  void showAlert(QString text);

  void handleUserInputTerm(char key);
  void printField();

 protected:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;

 private:
  S21SnakeModel& model;
  void handleUserInputDesk(int key);
};

class S21SnakeController : public QWidget {
 public:
  S21SnakeController(S21SnakeModel& model, S21SnakeView& view);
  void handleUserInput(int key);

 protected:
  void timerEvent(QTimerEvent*) override;

 private:
  S21SnakeModel& model;
  S21SnakeView& view;

  int m_timer;
  void startDesktopTimer();
  void initGame();
  bool isBoost();

  void gameLoop();
};

#endif