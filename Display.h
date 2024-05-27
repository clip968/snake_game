#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include <vector>
#include <utility>
#include <cstring>

class Display {
public:
    Display();
    void init();
    void drawUI();
    void drawStageClear();
    void drawGameClear();
    void drawGameOver();

    void clearAllObject();
private:
    void colorDefine();
    void drawBox(int px, int py, int width, int height, int colorIndex);
    void drawGameMap();
    void drawScoreBoard();
    void drawMissionBoard();
};

#endif
