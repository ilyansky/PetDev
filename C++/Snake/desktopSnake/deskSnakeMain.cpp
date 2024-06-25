#include "deskSnake.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  S21SnakeModel model;
  S21SnakeView view(model);
  S21SnakeController controller(model, view);
  return app.exec();
}