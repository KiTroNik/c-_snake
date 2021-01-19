#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/): CFramedWindow(r, _c)
{
  snake.front() = CPoint(geom.topleft.x+1, geom.topleft.y+1);
  //previous_key = KEY_RIGHT;
}

void CSnake::paint() {
  CFramedWindow::paint();
  gotoyx(snake.front().y, snake.front().x);
  printl("+");
  napms (120 - 5 * 1); //(snake.size() / 3));
}

bool CSnake::handleEvent(int key) {
    switch (key) {
        case KEY_UP:
            previous_key = CPoint(0, -1);
            move(previous_key);
            return true;
        case KEY_DOWN:
            previous_key = CPoint(0, 1);
            move(previous_key);
            return true;
        case KEY_LEFT:
            previous_key = CPoint(-1, 0);
            move(previous_key);
            return true;
        case KEY_RIGHT:
            previous_key = CPoint(1, 0);
            move(previous_key);
            return true;
        default:
            move(previous_key);
            return true;
    }
}


void CSnake::move(const CPoint & delta) {
  snake.front() += delta;

  if (snake.front().y == geom.topleft.y) {
     snake.front() = CPoint(snake.front().x, geom.size.y + geom.topleft.y - 2);
  } else if (snake.front().y == geom.size.y + geom.topleft.y - 1) { 
      snake.front() = CPoint(snake.front().x, geom.topleft.y + 1);
  } else if (snake.front().x == geom.topleft.x) {
      snake.front() = CPoint(geom.topleft.x + geom.size.x - 2, snake.front().y);
  } else if (snake.front().x == geom.topleft.x + geom.size.x - 1) {
      snake.front() = CPoint(geom.topleft.x + 1, snake.front().y);
  }
}