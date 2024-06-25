#include "termSnake.h"

int main() {
  S21ModelTerm model;
  S21ViewTerm view(model);
  S21ControllerTerm controller(model, view);
  return 0;
}