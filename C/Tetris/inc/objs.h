#ifndef OBJECTS_H
#define OBJECTS_H

typedef enum {
  startState,
  spawn,
  moving,
  shifting,
  attaching,
  pauseState,
  gameOver
} States;

typedef enum {
  straight,
  t,
  zReversed,
  z,
  rightHorse,
  leftHorse,
  square,
} Figures;

typedef enum {
  def,
  start,
  pause,
  terminate,
  left,
  right,
  up,
  down,
  action
} UserAction;

typedef struct {
  char **field;
  States state;

  Figures figure;
  Figures nextFigure;
  int figurePos[4][3];
  int rotatePos;

  UserAction action;
  int timer;

  // Info
  int lines;
  int points;
  int maxScore;
  int lvl;
  int speed;
  int movingTime;
  int oldPoints;
} Objects;

#endif
