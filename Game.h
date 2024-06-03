#ifndef GAME_H
#define GAME_H

#include "Gate.h"
#include <algorithm>
#include <vector>
#include "Display.h"
#include "Input.h"
#include "Snake.h"
#include "Item.h"

extern char gameMap[25][25];
extern std::pair<int, int> snakeHeadPosition;
extern int scoreCurrentLen, scoreMaxLen, scoreGrowthItems, scorePoisonItems, scoreGate, scoreTime;
extern int missionMaxLen, missionGrowthItems, missionPoisonItems, missionGate;
extern bool tailGateChk;
class Game {
public:
    Game();
    void init(int mapIndex);
    void initMap(int mapIndex);
    void initScore();
    void initMission();

    bool run();
    bool update();
    void gameSpeedUpdate();

    void cleanup();

private:
    Display display;
    Input input;
    Snake snake;
    Item growthItem, poisonItem;
    Gate gate;
    bool chkGameOver;
    int tick;
    int stage;
    void itemsTimeChk();
    void timeUpdate();
    std::time_t startTime;
};

#endif