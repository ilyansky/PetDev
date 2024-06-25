#include "deskSnake.h"

S21SnakeView::S21SnakeView(S21SnakeModel& model) : model(model) {}

void S21SnakeView::initGame() {
  resize((COL + 20) * CSIZE, ROW * CSIZE);
  setWindowTitle("Snake");
  this->show();
}

// DESKTOP
void S21SnakeView::paintEvent(QPaintEvent*) {
  Objects obj = model.obj;
  QPainter qp;
  qp.begin(this);

  // Game field
  for (int i = 0; i < ROW; ++i) {
    for (int j = 0; j < COL; ++j) {
      if (obj.field[i][j]) {
        qp.setBrush(Qt::gray);
      } else {
        qp.setBrush(Qt::white);
      }
      qp.drawRect((j + 10) * CSIZE, i * CSIZE, CSIZE, CSIZE);
    }
  }

  // Control keys
  qp.drawText(3 * CSIZE, 1 * CSIZE, "CONTROL KEYS");

  qp.drawText(1 * CSIZE, 2 * CSIZE, "Up - 'W'");
  qp.drawText(5 * CSIZE, 2 * CSIZE, "Down - 'S'");
  qp.drawText(1 * CSIZE, 3 * CSIZE, "Left - 'A'");
  qp.drawText(5 * CSIZE, 3 * CSIZE, "Right - 'D'");
  qp.drawText(1 * CSIZE, 4 * CSIZE, "Boost - 'E'");

  qp.drawText(1 * CSIZE, 6 * CSIZE, "Pause - 'C'");
  qp.drawText(1 * CSIZE, 7 * CSIZE, "Unpause - 'X'");
  qp.drawText(1 * CSIZE, 8 * CSIZE, "Quit the Snake - 'Q'");

  // Session info
  qp.drawText(23 * CSIZE, 1 * CSIZE, "SESSION INFO");

  QString applesCounter = QString("Apples = %1").arg(obj.applesCounter);
  qp.drawText(21 * CSIZE, 2 * CSIZE, applesCounter);

  QString maxScore = QString("Max score = %1").arg(obj.maxScore);
  qp.drawText(21 * CSIZE, 3 * CSIZE, maxScore);

  QString lvl = QString("Lvl = %1").arg(obj.lvl);
  qp.drawText(21 * CSIZE, 4 * CSIZE, lvl);

  QString speed = QString("Speed = %1").arg(obj.speed);
  qp.drawText(21 * CSIZE, 5 * CSIZE, speed);

  qp.end();
}

void S21SnakeView::keyPressEvent(QKeyEvent* event) {
  int key = event->key();
  handleUserInputDesk(key);
}

void S21SnakeView::handleUserInputDesk(int key) {
  switch (key) {
    case Qt::Key_W:
      if (model.obj.snake[0].row != model.obj.snake[1].row + 1) {
        model.obj.dir = up;
      }
      break;
    case Qt::Key_A:
      if (model.obj.snake[0].col != model.obj.snake[1].col + 1) {
        model.obj.dir = left;
      }
      break;
    case Qt::Key_S:
      if (model.obj.snake[0].row != model.obj.snake[1].row - 1) {
        model.obj.dir = down;
      }
      break;
    case Qt::Key_D:
      if (model.obj.snake[0].col != model.obj.snake[1].col - 1) {
        model.obj.dir = right;
      }
      break;
    case Qt::Key_E:
      boost = true;
      break;
    case Qt::Key_C:
      model.obj.state = pauseState;
      break;
    case Qt::Key_X:
      model.obj.state = gameState;
      break;
    case Qt::Key_Q:
      model.obj.state = terminateState;
      break;
    default:
      break;
  }
}

void S21SnakeView::showAlert(QString text) {
  QMessageBox msg;
  msg.setText(text);
  msg.exec();
}
