#include "tetris.h"

// Core
int main(void) {
  srand(time(NULL));  // Init randomizer
  initNcurses();
  gameLoop();
  deinitNcurses();
  return 0;
}