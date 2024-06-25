#include "deskSnake.h"

S21SnakeController::S21SnakeController(S21SnakeModel& model, S21SnakeView& view)
    : model(model), view(view) {
  initGame();
}

void S21SnakeController::initGame() {
  view.initGame();
  srand(time(0));
  startDesktopTimer();
}

void S21SnakeController::startDesktopTimer() { m_timer = startTimer(DELAY); }

void S21SnakeController::timerEvent(QTimerEvent*) {
  model.checkState();

  switch (model.obj.state) {
    case winState:
      view.showAlert("You are winner!");
      break;
    case gameOverState:
      view.showAlert("Game over");
      view.close();
      break;
    case terminateState:
      killTimer(m_timer);
      view.close();
      break;
    default:
      killTimer(m_timer);
      if (isBoost()) {
        startTimer(BOOSTED_DELAY);
      } else {
        startTimer(model.obj.delay);
      }

      view.update();
      break;
  }
}

bool S21SnakeController::isBoost() {
  if (view.boost) {
    view.boost = false;
    return true;
  }
  return false;
}