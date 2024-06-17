#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "objs.h"

#define ROW 26
#define COL 24
#define FILEPATH "maxScore.txt"

/*************************************************************
 * Logic
 ************************************************************/

// Core
void userInput(Objects *objs);
void initNcurses();
void deinitNcurses();
Objects initObjects();
Figures chooseFigure();

// States
void spawnState(Objects *objs);
void movingState(Objects *objs);
void shiftingState(Objects *objs);
void attachingState(Objects *objs);
void gameOverState();

// Movement logic
int isBottom(Objects *objs);
int isLeft(Objects *objs);
int isRight(Objects *objs);

// Rotation logic
int canPlace(Objects *objs);
int canPlaceLeftHorse(Objects *objs);
int canPlaceRightHorse(Objects *objs);
int canPlaceZ(Objects *objs);
int canPlaceZReversed(Objects *objs);
int canPlaceT(Objects *objs);
int canPlaceStraight(Objects *objs);

// Max score / lvl implementation
int readMaxScore();
void updateMaxScore(Objects *objs);
void isNewMaxScore(Objects *objs);
void isNextLvl(Objects *objs);

// Sup
void makeActionDefault(Objects *objs);
void refreshRotatePos(Objects *objs);
void resetTimer(Objects *objs);
void incrementLines(Objects *objs);
void incrementPoints(Objects *objs, int linesDeleted);

/*************************************************************
 * Interface
 ************************************************************/

// Core
void gameLoop(void);
char **makeFrame();
void printTheTetris(Objects *objs);
void printGameField(Objects *objs);
void printInfoTable(Objects *objs);

void spawnFigure(Objects *objs);
void configureCell(Objects *objs, int cellNum, int x, int y, int z);

// Movement mehanic
void moveFigureDown(Objects *objs);
void moveFigureSide(char where, Objects *objs);
void deleteLineAndSwipeDown(Objects *objs, int lineNum);
void dropFigureToTheBottom(Objects *objs);

// Rotation mehanic
void rotateLeftHorse(Objects *objs, int tempPos[4][3]);
void rotateRightHorse(Objects *objs, int tempPos[4][3]);
void rotateZ(Objects *objs, int tempPos[4][3]);
void rotateZReversed(Objects *objs, int tempPos[4][3]);
void rotateT(Objects *objs, int tempPos[4][3]);
void rotateStraight(Objects *objs, int tempPos[4][3]);
void rotateFigure(Objects *objs);

// Sup
void clearRefreshScreen();
void clearScreen();
void refreshScreen();
void clearOldCell(Objects *objs, int cellNum);
void clearOldFigure(Objects *objs);

#endif