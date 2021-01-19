#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "screen.h"
#include <unistd.h>

class CSnake:public CFramedWindow {
  private:
    list<CPoint> snake;
    CPoint apple;
    CPoint previous_key;
  public:
    CSnake(CRect r, char _c = ' ');

    void paint();
    bool handleEvent(int key);
    void move (const CPoint & delta);
};

#endif
