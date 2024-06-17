#include "tetris.h"

void gameLoop(void) {
  Objects objs = initObjects();

  mvprintw(0, 0, "Press 'X' to start the Tetris");
  refreshScreen();

  // Waiting for start
  do {
    userInput(&objs);
    if (objs.action == start) {
      objs.state = spawn;
    }
  } while (objs.action != start);

  // Main loop
  while (1) {
    userInput(&objs);
    isNewMaxScore(&objs);
    updateMaxScore(&objs);
    isNextLvl(&objs);

    if (objs.action == terminate) {
      break;
    }

    switch (objs.state) {
      case startState:
        break;
      case spawn:
        spawnState(&objs);
        break;
      case moving:
        movingState(&objs);
        clearRefreshScreen();
        printTheTetris(&objs);
        break;
      case shifting:
        shiftingState(&objs);
        break;
      case attaching:
        attachingState(&objs);
        break;
      case pauseState:
        clearScreen();
        mvprintw(0, 0, "Pause, press 'X' to unpause");
        refreshScreen();

        if (objs.action == start) {
          objs.state = moving;
        }
        break;
      default:
        break;
    }
  }
}

void printTheTetris(Objects *objs) {
  printGameField(objs);
  printInfoTable(objs);

  refreshScreen();
}

void printGameField(Objects *objs) {
  int startCol = 30;

  for (int row = 0; row < ROW; row++) {
    for (int col = 0; col < COL; col++) {
      if (col == COL - 1) {
        mvprintw(row, startCol + col, "%c\n", objs->field[row][col]);
      } else {
        mvprintw(row, startCol + col, "%c", objs->field[row][col]);
      }
    }
  }
}

void printInfoTable(Objects *objs) {
  // Control keys
  mvprintw(0, 7, "CONTROL KEYS");
  mvprintw(2, 0, "Rotate - 'W'");
  mvprintw(4, 0, "Boost - 'S'");
  mvprintw(2, 15, "Left - 'A'");
  mvprintw(4, 15, "Right - 'D'");
  mvprintw(6, 0, "Drop the figure - 'E'");

  mvprintw(10, 0, "Pause - 'C'");
  mvprintw(12, 0, "Unpause - 'X'");
  mvprintw(14, 0, "Quit the Tetris - 'Q'");

  // Next figure
  mvprintw(18, 7, "NEXT FIGURE");
  switch (objs->nextFigure) {
    case straight:
      mvprintw(20, 8, "[][][][]");
      break;
    case leftHorse:
      mvprintw(20, 9, "[]");
      mvprintw(21, 9, "[][][]");
      break;
    case rightHorse:
      mvprintw(20, 13, "[]");
      mvprintw(21, 9, "[][][]");
      break;
    case square:
      mvprintw(20, 10, "[][]");
      mvprintw(21, 10, "[][]");
      break;
    case z:
      mvprintw(20, 10, "[][]");
      mvprintw(21, 12, "[][]");
      break;
    case zReversed:
      mvprintw(21, 9, "[][]");
      mvprintw(20, 11, "[][]");
      break;
    case t:
      mvprintw(20, 11, "[]");
      mvprintw(21, 9, "[][][]");
      break;
  }

  // Session info
  mvprintw(0, 65, "SESSION INFO");
  mvprintw(2, 58, "Lvl = %d", objs->lvl);
  mvprintw(4, 58, "Speed = %d", objs->speed);
  mvprintw(6, 58, "Full lines = %d", objs->lines);
  mvprintw(8, 58, "Points = %d", objs->points);
  mvprintw(10, 58, "Max score = %d", objs->maxScore);
}

char **makeFrame() {
  char **field = malloc(ROW * COL * sizeof(char) + ROW * sizeof(char *));
  char *rows = (char *)(field + ROW);

  for (int i = 0; i < ROW; i++) {
    field[i] = rows + COL * i;
  }

  for (int row = 0; row < ROW; row++) {
    for (int col = 0; col < COL; col++) {
      if (row > 3) {
        if (row < ROW - 1 && col == 0) {
          field[row][col] = '<';
        } else if (row < ROW - 1 && (col == 1 || col == COL - 2)) {
          field[row][col] = '!';
        } else if (row < ROW - 1 && col == COL - 1) {
          field[row][col] = '>';
        } else if (row == ROW - 2) {
          field[row][col] = '=';
        } else if (row == ROW - 1 && col % 2 == 0 && col > 1 && col < COL - 2) {
          field[row][col] = '\\';
        } else if (row == ROW - 1 && col % 2 == 1 && col > 1 && col < COL - 2) {
          field[row][col] = '/';
        } else if (row == ROW - 1 && (col < 2 || col > COL - 3)) {
          field[row][col] = ' ';
        } else if (col % 2 == 1) {
          field[row][col] = '.';
        } else {
          field[row][col] = ' ';
        }
      } else {
        if (col == 1 || col == COL - 2) {
          field[row][col] = '!';
        } else {
          field[row][col] = ' ';
        }
      }
    }
  }

  return field;
}

void spawnFigure(Objects *objs) {
  refreshRotatePos(objs);
  switch (objs->figure) {
    case straight:
      configureCell(objs, 0, 0, 8, 9);
      configureCell(objs, 1, 0, 10, 11);
      configureCell(objs, 2, 0, 12, 13);
      configureCell(objs, 3, 0, 14, 15);
      break;
    case leftHorse:
      configureCell(objs, 0, 0, 8, 9);
      configureCell(objs, 1, 1, 8, 9);
      configureCell(objs, 2, 1, 10, 11);
      configureCell(objs, 3, 1, 12, 13);
      break;
    case rightHorse:
      configureCell(objs, 0, 1, 8, 9);
      configureCell(objs, 1, 1, 10, 11);
      configureCell(objs, 2, 1, 12, 13);
      configureCell(objs, 3, 0, 12, 13);
      break;
    case square:
      configureCell(objs, 0, 0, 10, 11);
      configureCell(objs, 1, 0, 12, 13);
      configureCell(objs, 2, 1, 10, 11);
      configureCell(objs, 3, 1, 12, 13);
      break;
    case z:
      configureCell(objs, 0, 0, 8, 9);
      configureCell(objs, 1, 0, 10, 11);
      configureCell(objs, 2, 1, 10, 11);
      configureCell(objs, 3, 1, 12, 13);
      break;
    case zReversed:
      configureCell(objs, 0, 1, 8, 9);
      configureCell(objs, 1, 1, 10, 11);
      configureCell(objs, 2, 0, 10, 11);
      configureCell(objs, 3, 0, 12, 13);
      break;
    case t:
      configureCell(objs, 0, 1, 8, 9);
      configureCell(objs, 1, 1, 10, 11);
      configureCell(objs, 2, 1, 12, 13);
      configureCell(objs, 3, 0, 10, 11);
      break;
  }
}

void configureCell(Objects *objs, int cellNum, int x, int y, int z) {
  objs->figurePos[cellNum][0] = x;
  objs->figurePos[cellNum][1] = y;
  objs->figurePos[cellNum][2] = z;

  objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][1]] = '[';
  objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][2]] = ']';
}

// Movement mehanic
void deleteLineAndSwipeDown(Objects *objs, int lineNum) {
  for (int i = lineNum; i > 4; i--) {
    for (int j = 2; j < COL - 2; j++) {
      objs->field[i][j] = objs->field[i - 1][j];
    }
  }

  for (int j = 2; j < COL - 2; j++) {
    if (j % 2 == 1) {
      objs->field[4][j] = '.';
    } else {
      objs->field[4][j] = ' ';
    }
  }
}

void moveFigureSide(char where, Objects *objs) {
  // Clear old position
  clearOldFigure(objs);

  // Copy old figurePos
  int tempPos[4][3];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      tempPos[i][j] = objs->figurePos[i][j];
    }
  }

  if (where == 'l') {
    configureCell(objs, 0, tempPos[0][0], tempPos[0][1] - 2, tempPos[0][2] - 2);
    configureCell(objs, 1, tempPos[1][0], tempPos[1][1] - 2, tempPos[1][2] - 2);
    configureCell(objs, 2, tempPos[2][0], tempPos[2][1] - 2, tempPos[2][2] - 2);
    configureCell(objs, 3, tempPos[3][0], tempPos[3][1] - 2, tempPos[3][2] - 2);
  } else {
    configureCell(objs, 0, tempPos[0][0], tempPos[0][1] + 2, tempPos[0][2] + 2);
    configureCell(objs, 1, tempPos[1][0], tempPos[1][1] + 2, tempPos[1][2] + 2);
    configureCell(objs, 2, tempPos[2][0], tempPos[2][1] + 2, tempPos[2][2] + 2);
    configureCell(objs, 3, tempPos[3][0], tempPos[3][1] + 2, tempPos[3][2] + 2);
  }
}

void moveFigureDown(Objects *objs) {
  // Clear old position
  clearOldFigure(objs);

  // Copy old figurePos
  int tempPos[4][3];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      tempPos[i][j] = objs->figurePos[i][j];
    }
  }

  // Upd field
  configureCell(objs, 0, tempPos[0][0] + 1, tempPos[0][1], tempPos[0][2]);
  configureCell(objs, 1, tempPos[1][0] + 1, tempPos[1][1], tempPos[1][2]);
  configureCell(objs, 2, tempPos[2][0] + 1, tempPos[2][1], tempPos[2][2]);
  configureCell(objs, 3, tempPos[3][0] + 1, tempPos[3][1], tempPos[3][2]);
}

void dropFigureToTheBottom(Objects *objs) {
  int flag = 1;

  // Clear old position
  clearOldFigure(objs);

  while (flag) {
    if (isBottom(objs) == 0) {
      objs->figurePos[0][0] += 1;
      objs->figurePos[1][0] += 1;
      objs->figurePos[2][0] += 1;
      objs->figurePos[3][0] += 1;
    } else {
      // Copy old figurePos
      int tempPos[4][3];
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
          tempPos[i][j] = objs->figurePos[i][j];
        }
      }

      // Upd field
      configureCell(objs, 0, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 3, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      flag = 0;
    }
  }
}

// Rotation mehanic
void rotateFigure(Objects *objs) {
  // Clear old position
  clearOldFigure(objs);

  // Copy old figurePos
  int tempPos[4][3];
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      tempPos[i][j] = objs->figurePos[i][j];
    }
  }

  switch (objs->figure) {
    case straight:
      rotateStraight(objs, tempPos);
      break;
    case leftHorse:
      rotateLeftHorse(objs, tempPos);
      break;
    case rightHorse:
      rotateRightHorse(objs, tempPos);
      break;
    case square:
      break;
    case z:
      rotateZ(objs, tempPos);
      break;
    case zReversed:
      rotateZReversed(objs, tempPos);
      break;
    case t:
      rotateT(objs, tempPos);
      break;
  }
}

void rotateStraight(Objects *objs, int tempPos[4][3]) {
  switch (objs->rotatePos) {
    case 0:
      configureCell(objs, 0, tempPos[1][0] + 1, tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[1][0] - 1, tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 3, tempPos[1][0] - 2, tempPos[1][1], tempPos[1][2]);
      break;
    case 1:
      configureCell(objs, 0, tempPos[1][0], tempPos[1][1] - 2,
                    tempPos[1][2] - 2);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[1][0], tempPos[1][1] + 2,
                    tempPos[1][2] + 2);
      configureCell(objs, 3, tempPos[1][0], tempPos[1][1] + 4,
                    tempPos[1][2] + 4);
      break;
  }

  // Increment the rotation position
  objs->rotatePos = (objs->rotatePos + 1) % 2;
}

void rotateT(Objects *objs, int tempPos[4][3]) {
  switch (objs->rotatePos) {
    case 0:
      configureCell(objs, 0, tempPos[1][0] + 1, tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 3, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      break;
    case 1:
      configureCell(objs, 0, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[1][0], tempPos[1][1] + 2,
                    tempPos[1][2] + 2);
      configureCell(objs, 3, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      break;
    case 2:
      configureCell(objs, 0, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[1][0] - 1, tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 3, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      break;
    case 3:
      configureCell(objs, 0, tempPos[1][0], tempPos[1][1] - 2,
                    tempPos[1][2] - 2);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 3, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      break;
  }

  // Increment the rotation position
  objs->rotatePos = (objs->rotatePos + 1) % 4;
}

void rotateZReversed(Objects *objs, int tempPos[4][3]) {
  switch (objs->rotatePos) {
    case 0:
      configureCell(objs, 0, tempPos[2][0], tempPos[0][1], tempPos[0][2]);
      configureCell(objs, 1, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      configureCell(objs, 2, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 3, tempPos[1][0] + 1, tempPos[1][1], tempPos[1][2]);
      break;
    case 1:
      configureCell(objs, 0, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 1, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 2, tempPos[0][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 3, tempPos[0][0], tempPos[2][1] + 2,
                    tempPos[2][2] + 2);
      break;
  }

  // Increment the rotation position
  objs->rotatePos = (objs->rotatePos + 1) % 2;
}

void rotateZ(Objects *objs, int tempPos[4][3]) {
  switch (objs->rotatePos) {
    case 0:
      configureCell(objs, 0, tempPos[2][0] + 1, tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 1, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 2, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 3, tempPos[3][0] - 1, tempPos[3][1], tempPos[3][2]);
      break;
    case 1:
      configureCell(objs, 0, tempPos[1][0] - 1, tempPos[1][1] - 2,
                    tempPos[1][2] - 2);
      configureCell(objs, 1, tempPos[1][0] - 1, tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 3, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      break;
  }

  // Increment the rotation position
  objs->rotatePos = (objs->rotatePos + 1) % 2;
}

void rotateRightHorse(Objects *objs, int tempPos[4][3]) {
  switch (objs->rotatePos) {
    case 0:
      configureCell(objs, 0, tempPos[3][0], tempPos[3][1] - 2,
                    tempPos[3][2] - 2);
      configureCell(objs, 1, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 2, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 3, tempPos[3][0] + 2, tempPos[3][1], tempPos[3][2]);
      break;
    case 1:
      configureCell(objs, 0, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 1, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 2, tempPos[1][0], tempPos[1][1] + 2,
                    tempPos[1][2] + 2);
      configureCell(objs, 3, tempPos[1][0], tempPos[1][1] + 4,
                    tempPos[1][2] + 4);
      break;
    case 2:
      configureCell(objs, 0, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 1, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      configureCell(objs, 2, tempPos[0][0] + 1, tempPos[0][1], tempPos[0][2]);
      configureCell(objs, 3, tempPos[0][0] + 1, tempPos[0][1] + 2,
                    tempPos[0][2] + 2);
      break;
    case 3:
      configureCell(objs, 0, tempPos[2][0] - 1, tempPos[2][1] - 4,
                    tempPos[2][2] - 4);
      configureCell(objs, 1, tempPos[2][0] - 1, tempPos[2][1] - 2,
                    tempPos[2][2] - 2);
      configureCell(objs, 2, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 3, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      break;
  }

  // Increment the rotation position
  objs->rotatePos = (objs->rotatePos + 1) % 4;
}

void rotateLeftHorse(Objects *objs, int tempPos[4][3]) {
  switch (objs->rotatePos) {
    case 0:
      configureCell(objs, 0, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 1, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 2, tempPos[0][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 3, tempPos[1][0] - 2, tempPos[3][1], tempPos[3][2]);
      break;
    case 1:
      configureCell(objs, 0, tempPos[1][0], tempPos[1][1] - 4,
                    tempPos[1][2] - 4);
      configureCell(objs, 1, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      configureCell(objs, 2, tempPos[1][0], tempPos[1][1], tempPos[1][2]);
      configureCell(objs, 3, tempPos[1][0] + 1, tempPos[1][1], tempPos[1][2]);
      break;
    case 2:
      configureCell(objs, 0, tempPos[3][0], tempPos[3][1], tempPos[3][2]);
      configureCell(objs, 1, tempPos[2][0], tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 2, tempPos[2][0] - 1, tempPos[2][1], tempPos[2][2]);
      configureCell(objs, 3, tempPos[2][0] - 1, tempPos[2][1] + 2,
                    tempPos[2][2] + 2);
      break;
    case 3:
      configureCell(objs, 0, tempPos[0][0] - 1, tempPos[0][1] - 4,
                    tempPos[0][2] - 4);
      configureCell(objs, 1, tempPos[0][0], tempPos[0][1] - 4,
                    tempPos[0][2] - 4);
      configureCell(objs, 2, tempPos[0][0], tempPos[0][1] - 2,
                    tempPos[0][2] - 2);
      configureCell(objs, 3, tempPos[0][0], tempPos[0][1], tempPos[0][2]);
      break;
  }

  // Increment the rotation position
  objs->rotatePos = (objs->rotatePos + 1) % 4;
}

// Sup
void clearScreen() { clear(); }

void refreshScreen() { refresh(); }

void clearRefreshScreen() {
  clearScreen();
  refreshScreen();
}

void clearOldCell(Objects *objs, int cellNum) {
  if (objs->figurePos[cellNum][0] < 4) {
    objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][1]] = ' ';
    objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][2]] = ' ';
  } else {
    // objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][1]] = '
    // '; objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][2]]
    // = '.';
    if (objs->figurePos[cellNum][1] % 2 == 1) {
      objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][1]] =
          '.';
    } else {
      objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][1]] =
          ' ';
    }

    if (objs->figurePos[cellNum][2] % 2 == 1) {
      objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][2]] =
          '.';
    } else {
      objs->field[objs->figurePos[cellNum][0]][objs->figurePos[cellNum][2]] =
          ' ';
    }
  }
}

void clearOldFigure(Objects *objs) {
  clearOldCell(objs, 0);
  clearOldCell(objs, 1);
  clearOldCell(objs, 2);
  clearOldCell(objs, 3);
}
