#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/): CFramedWindow(r, _c)
{
    previous_key = CPoint(1, 0);
    snake.push_back(CPoint(geom.topleft.x+5, geom.topleft.y+5));
    snake.push_back(CPoint(geom.topleft.x+4, geom.topleft.y+4));
    snake.push_back(CPoint(geom.topleft.x+3, geom.topleft.y+3));
    apple = CPoint(geom.topleft.x + 15, geom.topleft.y + 15);

    game_over = false;
    pause = false;
    help = true;
}

void CSnake::paint() {
    CFramedWindow::paint();

    gotoyx(geom.topleft.y - 1, geom.topleft.x);
    printl("| LEVEL %d |", snake.size()/3);

    gotoyx(snake[0].y, snake[0].x);
    printl("*");
    for (unsigned int i = 1; i < snake.size(); i++) {
        gotoyx(snake[i].y, snake[i].x);
        printl("+");
    }
    gotoyx(apple.y, apple.x);
    printl("o");

    if (help) print_help();
    if (game_over) print_end_game();

    napms (120 - 5 * (snake.size() / 3));
}

bool CSnake::handleEvent(int key) {
    if (key == '\t') return false;
    if (key == 'r') reset_game();
    if (key == 'p') pause = !pause;
    if (key == 'h') help = !help;
    

    if (pause == false && help == false && game_over == false) {
        switch (key) {
        case KEY_UP:
            if (previous_key.y == 1) return false;
            previous_key = CPoint(0, -1);
            move(previous_key);
            return true;
        case KEY_DOWN:
            if (previous_key.y == -1) return false;
            previous_key = CPoint(0, 1);
            move(previous_key);
            return true;
        case KEY_LEFT:
            if (previous_key.x == 1) return false;
            previous_key = CPoint(-1, 0);
            move(previous_key);
            return true;
        case KEY_RIGHT:
            if (previous_key.x == -1) return false;
            previous_key = CPoint(1, 0);
            move(previous_key);
            return true;
        default:
            move(previous_key);
            return true;
        }
    } else if (help == true) {
        return true;
    } else {
        return true;
    }
}

void CSnake::move(const CPoint & delta) {

    for (int i = snake.size(); i >= 1; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] += delta;

    if (snake[0].x == apple.x && snake[0].y == apple.y) {
        rand_apple();
        snake.push_back(CPoint(snake[snake.size()-1].x, snake[snake.size()-1].y));
    }

    for (unsigned int i = 1; i < snake.size(); i++) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) {
            game_over = true;
            break;
        }
    }
    
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

void CSnake::rand_apple() {
    int is_git = 0;
    int x, y;
    unsigned int pos;
    while (is_git != 1) {
        pos = 0;
        x = (geom.topleft.x + 1) + rand() % ((geom.topleft.x + geom.size.x - 1) - (geom.topleft.x + 1));
        y = (geom.topleft.y + 1) + rand() % ((geom.topleft.y + geom.size.y - 1) - (geom.topleft.y + 1));

        for (size_t i = 0; i < snake.size(); i++) {
            if (snake[i].x != x && snake[i].y != y) pos++;
        }

        if (pos == snake.size()) is_git = 1;
    }
    apple = CPoint(x, y);
}

void CSnake::reset_game() {
    snake.clear();
    previous_key = CPoint(1, 0);
    snake.push_back(CPoint(geom.topleft.x+5, geom.topleft.y+5));
    snake.push_back(CPoint(geom.topleft.x+4, geom.topleft.y+4));
    snake.push_back(CPoint(geom.topleft.x+3, geom.topleft.y+3));
    apple = CPoint(geom.topleft.x + 15, geom.topleft.y + 15);

    game_over = false;
    pause = false;
    help = true;
}

void CSnake::print_help() {
    gotoyx(geom.topleft.y + 5, geom.topleft.x + 3);
    printl("h - toggle help information");
    gotoyx(geom.topleft.y + 6, geom.topleft.x + 3);
    printl("p - toggle pause/play mode");
    gotoyx(geom.topleft.y + 7, geom.topleft.x + 3);
    printl("r - restart game");
    gotoyx(geom.topleft.y + 8, geom.topleft.x + 3);
    printl("arrows - move snake (in play mode) or");
    gotoyx(geom.topleft.y + 9, geom.topleft.x + 10);
    printl("move window (in pause mode)");
}

void CSnake::print_end_game() {
    gotoyx(geom.topleft.y + 1, geom.topleft.x + 1);
    printl("GAME OVER, result: %d", snake.size() - 3);
}