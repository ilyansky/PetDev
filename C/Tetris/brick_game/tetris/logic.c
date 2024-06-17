#include "tetris.h"

// Core
void userInput(Objects *objs) {
  char input = getch();
  switch (input) {
    case 'a':
      objs->action = left;
      break;
    case 'd':
      objs->action = right;
      break;
    case 'w':
      objs->action = up;
      break;
    case 's':
      objs->action = down;
      break;
    case 'e':
      objs->action = action;
      break;
    case 'c':
      objs->action = pause;
      break;
    case 'x':
      objs->action = start;
      break;
    case 'q':
      objs->action = terminate;
      break;
  }
}

void initNcurses() {
  initscr();
  cbreak();
  noecho();
  // keypad(stdscr, TRUE);
  // timeout(0);
  nodelay(stdscr, TRUE);
  curs_set(0);
}

void deinitNcurses() { endwin(); }

Objects initObjects() {
  Objects objs = {.field = makeFrame(),
                  .state = startState,

                  .figure = chooseFigure(),
                  .nextFigure = chooseFigure(),
                  .figurePos = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
                  .rotatePos = 0,

                  .action = def,
                  .timer = 0,

                  .lines = 0,
                  .points = 0,
                  .maxScore = readMaxScore(),
                  .lvl = 1,
                  .movingTime = 700,
                  .oldPoints = 0,
                  .speed = 10};

  return objs;
}

Figures chooseFigure() {
  int num = rand() % 7;
  Figures figure = num;
  return figure;
}

// States
void spawnState(Objects *objs) {
  objs->figure = objs->nextFigure;
  objs->nextFigure = chooseFigure();

  spawnFigure(objs);
  objs->state = moving;
}

void movingState(Objects *objs) {
  switch (objs->action) {
    case left:
      if (isLeft(objs) == 0) moveFigureSide('l', objs);
      break;
    case right:
      if (isRight(objs) == 0) moveFigureSide('r', objs);
      break;
    case up:
      if (canPlace(objs) == 1) rotateFigure(objs);
      break;
    case down:
      objs->timer += 400;
      break;
    case action:
      dropFigureToTheBottom(objs);
      break;
    case pause:
      objs->state = pauseState;
      return;
    // case start:
    //   objs->points += 400;
    //   break;
    default:
      break;
  }

  if (objs->timer > objs->movingTime) {
    if (isBottom(objs) == 0) {
      objs->state = shifting;
    } else {
      objs->state = attaching;
    }

    resetTimer(objs);
  }

  napms(20);
  objs->timer += 20;

  makeActionDefault(objs);
}

void shiftingState(Objects *objs) {
  moveFigureDown(objs);
  objs->state = moving;
}

void attachingState(Objects *objs) {
  int breakFlag = 0;
  int linesDeleted = 0;

  // Full lines
  for (int i = ROW - 3; i > 3; i--) {
    for (int j = 2; j < COL - 2; j++) {
      if (objs->field[i][j] != '[' && objs->field[i][j] != ']') {
        breakFlag = 1;
        break;
      }
    }

    if (breakFlag == 0) {
      deleteLineAndSwipeDown(objs, i);
      incrementLines(objs);
      i += 1;
      linesDeleted += 1;
    } else {
      breakFlag = 0;
    }
  }

  // Blocks upper top check
  for (int i = 2; i < COL - 2; i++) {
    if (objs->field[3][i] == '[' || objs->field[3][i] == ']') {
      gameOverState();
      objs->state = gameOver;
      return;
    }
  }

  // Increment points
  incrementPoints(objs, linesDeleted);

  objs->state = spawn;
}

void gameOverState() {
  clearScreen();
  mvprintw(0, 0, "Game over, press 'Q' to leave");
  refreshScreen();
}

// Movement logic
int isBottom(Objects *objs) {
  int row = 0;
  int col = 0;
  int bottomCells[4] = {0, 0, 0, 0};
  int breakFlag = 0;
  int res = 0;

  // Find cells on bottom
  for (int cell = 0; cell < 4; cell++) {
    for (int j = 0; j < 4; j++) {
      if (cell != j) {
        if (objs->figurePos[cell][1] == objs->figurePos[j][1] &&
            objs->figurePos[cell][0] < objs->figurePos[j][0]) {
          breakFlag = 1;
          break;
        }
      }
    }

    if (breakFlag == 0) {
      bottomCells[cell] = 1;
    } else {
      breakFlag = 0;
    }
  }

  // Check the bottom
  for (int cellNum = 0; cellNum < 4; cellNum++) {
    if (bottomCells[cellNum] == 1) {
      row = objs->figurePos[cellNum][0] + 1;
      col = objs->figurePos[cellNum][1];

      if (objs->field[row][col] == '=' || objs->field[row][col] == '[') {
        res = 1;
        break;
      }
    }
  }

  return res;
}

int isLeft(Objects *objs) {
  int row = 0;
  int col = 0;
  int bottomCells[4] = {0, 0, 0, 0};
  int breakFlag = 0;
  int res = 0;

  // Find cells on left
  for (int cell = 0; cell < 4; cell++) {
    for (int j = 0; j < 4; j++) {
      if (cell != j) {
        if (objs->figurePos[cell][0] == objs->figurePos[j][0] &&
            objs->figurePos[cell][1] > objs->figurePos[j][1]) {
          breakFlag = 1;
          break;
        }
      }
    }

    if (breakFlag == 0) {
      bottomCells[cell] = 1;
    } else {
      breakFlag = 0;
    }
  }

  // Check the left
  for (int cellNum = 0; cellNum < 4; cellNum++) {
    if (bottomCells[cellNum] == 1) {
      row = objs->figurePos[cellNum][0];
      col = objs->figurePos[cellNum][2] - 2;

      if (objs->field[row][col] == '!' || objs->field[row][col] == ']') {
        res = 1;
        break;
      }
    }
  }

  return res;
}

int isRight(Objects *objs) {
  int row = 0;
  int col = 0;
  int bottomCells[4] = {0, 0, 0, 0};
  int breakFlag = 0;
  int res = 0;

  // Find cells on right
  for (int cell = 0; cell < 4; cell++) {
    for (int j = 0; j < 4; j++) {
      if (cell != j) {
        if (objs->figurePos[cell][0] == objs->figurePos[j][0] &&
            objs->figurePos[cell][1] < objs->figurePos[j][1]) {
          breakFlag = 1;
          break;
        }
      }
    }

    if (breakFlag == 0) {
      bottomCells[cell] = 1;
    } else {
      breakFlag = 0;
    }
  }

  // Check the right
  for (int cellNum = 0; cellNum < 4; cellNum++) {
    if (bottomCells[cellNum] == 1) {
      row = objs->figurePos[cellNum][0];
      col = objs->figurePos[cellNum][1] + 2;

      if (objs->field[row][col] == '!' || objs->field[row][col] == '[') {
        res = 1;
        break;
      }
    }
  }

  return res;
}

// Rotation logic
int canPlace(Objects *objs) {
  int res = 0;

  switch (objs->figure) {
    case straight:
      res = canPlaceStraight(objs);
      break;
    case leftHorse:
      res = canPlaceLeftHorse(objs);
      break;
    case rightHorse:
      res = canPlaceRightHorse(objs);
      break;
    case square:
      break;
    case z:
      res = canPlaceZ(objs);
      break;
    case zReversed:
      res = canPlaceZReversed(objs);
      break;
    case t:
      res = canPlaceT(objs);
      break;
  }

  return res;
}

int canPlaceStraight(Objects *objs) {
  int row0, col0, row2, col2, row3, col3;
  int res = 0;

  switch (objs->rotatePos) {
    case 0:
      row0 = objs->figurePos[1][0] + 1;
      row2 = objs->figurePos[1][0] - 1;
      row3 = objs->figurePos[1][0] - 2;
      col0 = objs->figurePos[1][1];
      col2 = objs->figurePos[1][1];
      col3 = objs->figurePos[1][1];
      if (row3 >= 0 && objs->field[row0][col0] == ' ' &&
          objs->field[row2][col2] == ' ' && objs->field[row3][col3] == ' ') {
        res = 1;
      }
      break;
    case 1:
      row0 = objs->figurePos[1][0];
      row2 = objs->figurePos[1][0];
      row3 = objs->figurePos[1][0];
      col0 = objs->figurePos[1][1] - 2;
      col2 = objs->figurePos[1][1] + 2;
      col3 = objs->figurePos[1][1] + 4;
      if (col3 < COL - 2 && objs->field[row0][col0] == ' ' &&
          objs->field[row2][col2] == ' ' && objs->field[row3][col3] == ' ') {
        res = 1;
      }
      break;
  }

  return res;
}

int canPlaceT(Objects *objs) {
  int row1, col1;
  int res = 0;

  switch (objs->rotatePos) {
    case 0:
      row1 = objs->figurePos[1][0] + 1;
      col1 = objs->figurePos[1][1];
      if (row1 < ROW - 2 && objs->field[row1][col1] == ' ') {
        res = 1;
      }
      break;
    case 1:
      row1 = objs->figurePos[1][0];
      col1 = objs->figurePos[1][1] + 2;
      if (col1 < COL - 2 && objs->field[row1][col1] == ' ') {
        res = 1;
      }
      break;
    case 2:
      row1 = objs->figurePos[1][0] - 1;
      col1 = objs->figurePos[1][1];
      if (row1 >= 0 && objs->field[row1][col1] == ' ') {
        res = 1;
      }
      break;
    case 3:
      row1 = objs->figurePos[1][0];
      col1 = objs->figurePos[1][1] - 2;
      if (col1 > 1 && objs->field[row1][col1] == ' ') {
        res = 1;
      }
      break;
  }

  return res;
}

int canPlaceZReversed(Objects *objs) {
  int row1, col1, row2, col2;
  int res = 0;

  switch (objs->rotatePos) {
    case 0:
      row1 = objs->figurePos[2][0];
      row2 = objs->figurePos[1][0] + 1;
      col1 = objs->figurePos[0][1];
      col2 = objs->figurePos[1][1];
      if (row2 < ROW - 2 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 1:
      row1 = objs->figurePos[0][0];
      row2 = objs->figurePos[0][0];
      col1 = objs->figurePos[2][1];
      col2 = objs->figurePos[2][1] + 2;
      if (col2 < COL - 2 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
  }

  return res;
}

int canPlaceZ(Objects *objs) {
  int row1, col1, row2, col2;
  int res = 0;

  switch (objs->rotatePos) {
    case 0:
      row1 = objs->figurePos[1][0];
      row2 = objs->figurePos[2][0] + 1;
      col1 = objs->figurePos[3][1];
      col2 = objs->figurePos[2][1];
      if (row2 < ROW - 2 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 1:
      row1 = objs->figurePos[3][0];
      row2 = objs->figurePos[3][0];
      col1 = objs->figurePos[1][1];
      col2 = objs->figurePos[1][1] - 2;
      if (col2 > 1 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
  }

  return res;
}

int canPlaceRightHorse(Objects *objs) {
  int row1, col1, row2, col2;
  int res = 0;

  switch (objs->rotatePos) {
    case 0:
      row1 = objs->figurePos[3][0];
      row2 = objs->figurePos[3][0] + 2;
      col1 = objs->figurePos[3][1] - 2;
      col2 = objs->figurePos[3][1];
      if (col1 > 1 && row2 < ROW - 2 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 1:
      row1 = objs->figurePos[1][0];
      row2 = objs->figurePos[1][0];
      col1 = objs->figurePos[1][1] + 2;
      col2 = objs->figurePos[1][1] + 4;
      if (col2 < COL - 2 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 2:
      row1 = objs->figurePos[1][0] + 2;
      row2 = objs->figurePos[1][0] + 2;
      col1 = objs->figurePos[1][1];
      col2 = objs->figurePos[1][1] + 2;
      if (col2 < COL - 2 && row2 < ROW - 2 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 3:
      row1 = objs->figurePos[1][0];
      row2 = objs->figurePos[1][0];
      col1 = objs->figurePos[1][1] - 2;
      col2 = objs->figurePos[1][1] - 4;
      if (col2 > 1 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
  }

  return res;
}

int canPlaceLeftHorse(Objects *objs) {
  int row1, col1, row2, col2, row3, col3;
  int res = 0;

  switch (objs->rotatePos) {
    case 0:
      row1 = objs->figurePos[3][0] - 1;
      row2 = objs->figurePos[3][0] - 2;
      col1 = col2 = objs->figurePos[3][1];
      if (row2 >= 0 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 1:
      row1 = objs->figurePos[1][0];
      row2 = objs->figurePos[1][0] + 1;
      col1 = objs->figurePos[1][1] - 4;
      col2 = objs->figurePos[1][1];
      if (col1 > 1 && row2 < ROW - 2 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 2:
      row1 = objs->figurePos[2][0] - 1;
      row2 = objs->figurePos[2][0] - 1;
      col1 = objs->figurePos[2][1];
      col2 = objs->figurePos[2][1] + 2;
      if (col2 < COL - 2 && row2 >= 0 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ') {
        res = 1;
      }
      break;
    case 3:
      row1 = objs->figurePos[0][0];
      row2 = objs->figurePos[0][0];
      row3 = objs->figurePos[0][0] - 1;
      col1 = objs->figurePos[0][1] - 2;
      col2 = objs->figurePos[0][1] - 4;
      col3 = objs->figurePos[0][1] - 4;
      if (col3 > 1 && row3 >= 0 && objs->field[row1][col1] == ' ' &&
          objs->field[row2][col2] == ' ' && objs->field[row3][col3] == ' ') {
        res = 1;
      }
      break;
  }

  return res;
}

// Max score / lvl implementation
int readMaxScore() {
  int res = 0;

  FILE *file = fopen(FILEPATH, "r");
  if (file == NULL) {
    perror("err");
    return res;
  }

  char buffer[1000];
  if (fgets(buffer, 1000, file) != NULL) {
    res = atoi(buffer);
  }

  fclose(file);
  return res;
}

void updateMaxScore(Objects *objs) { objs->maxScore = readMaxScore(); }

void isNewMaxScore(Objects *objs) {
  if (objs->points > objs->maxScore) {
    objs->maxScore = objs->points;

    FILE *file = fopen(FILEPATH, "w");
    if (file == NULL) {
      perror("err");
      return;
    }

    fprintf(file, "%d", objs->maxScore);
    fclose(file);
  }
}

void isNextLvl(Objects *objs) {
  if (objs->lvl != 10 && objs->points - objs->oldPoints >= 600) {
    int lvls = (objs->points - objs->oldPoints) / 600;

    if (objs->lvl + lvls > 10) {
      objs->lvl = 10;
    } else {
      objs->lvl += lvls;
    }

    if (objs->movingTime - lvls * 50 < 200) {
      objs->movingTime = 200;
    } else {
      objs->movingTime -= lvls * 50;
    }

    objs->speed += lvls * 10;
    objs->oldPoints = 600 * (objs->points / 600);
  }
}

// Sup
void makeActionDefault(Objects *objs) { objs->action = def; }

void refreshRotatePos(Objects *objs) { objs->rotatePos = 0; }

void resetTimer(Objects *objs) { objs->timer = 0; }

void incrementLines(Objects *objs) { objs->lines += 1; }

void incrementPoints(Objects *objs, int linesDeleted) {
  switch (linesDeleted) {
    case 0:
      break;
    case 1:
      objs->points += 100;
      break;
    case 2:
      objs->points += 300;
      break;
    case 3:
      objs->points += 700;
      break;
    default:
      objs->points += 1500;
      break;
  }
}
