#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/): CFramedWindow(r, _c)
{
  head.y = geom.topleft.y + 1;
  head.x = geom.topleft.x + 1;
  previous_key = CPoint(1, 0);
}

void CSnake::paint() {
  CFramedWindow::paint();
  gotoyx(head.y, head.x);
  printl("+");
}

bool CSnake::handleEvent(int key) {
    switch (key) {
    case KEY_UP:
      previous_key = (CPoint (0, -1));
      return true;
    case KEY_DOWN:
      previous_key = (CPoint (0, 1));
      return true;
    case KEY_RIGHT:
      previous_key = (CPoint (1, 0));
      return true;
    case KEY_LEFT:
      previous_key = (CPoint (-1, 0));
      return true;
    };
    //sleep(1);
    move(previous_key);
    return true;
}

void CSnake::move(const CPoint & delta) {
  head += delta;

  if (head.y == geom.topleft.y) {
     head = CPoint(head.x, geom.size.y + geom.topleft.y - 2);
  } else if (head.y == geom.size.y + geom.topleft.y - 1) {
      head = CPoint(head.x, geom.topleft.y + 1);
  } else if (head.x == geom.topleft.x) {
      head = CPoint(geom.topleft.x + geom.size.x - 2, head.y);
  } else if (head.x == geom.topleft.x + geom.size.x - 1) {
    head = CPoint(geom.topleft.x + 1, head.y);
  }
}