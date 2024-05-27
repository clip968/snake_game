#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <utility>

class Snake {
public:
    int getDirection();
    bool setDirection(int newDirection);
    int move();
    int currentDirection;
    void init();
private:
    std::pair<int, int> snakeTailPosition;
    std::pair<int, int> delta[5] = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    void grow();
    void reduce();
    int getHeadObject();
    int newDirectionCalc(int y, int x, int dir);
};

#endif
