#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"
#include "screen.h"
#include <vector>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

class CSnake:public CFramedWindow {
  private:
    vector<CPoint> snake;
    CPoint apple;
    CPoint previous_key;
    bool pause;
    bool help;
    bool game_over;
  public:
    CSnake(CRect r, char _c = ' ');

    void paint();
    bool handleEvent(int key);
    void move (const CPoint & delta);
    void rand_apple();
    void reset_game();
};

#endif
