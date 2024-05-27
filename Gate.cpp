#include "Gate.h"
#include "Game.h"
#include <ctime>
#include <random>

Gate::Gate(int target) : gateTarget(target) {}

int getRandomGate(int low, int high){
    std::random_device rd;
    std::mt19937 mt(rd()); 
    std::uniform_int_distribution<int> dist(low, high); 
    return dist(mt);
}

void Gate::createGate() {
    int x1, y1, x2, y2;

    // 첫 번째 게이트 위치 선택
    do {
        x1 = getRandomGate(0, 24);
        y1 = getRandomGate(0, 24);
    } while (gameMap[y1][x1] != -1);

    // 두 번째 게이트 위치 선택
    do {
        x2 = getRandomGate(0, 24);
        y2 = getRandomGate(0, 24);
    } while ((x1 == x2 && y1 == y2) || gameMap[y2][x2] != -1);

    // 게이트 위치 설정
    gameMap[y1][x1] = gateTarget;
    gameMap[y2][x2] = gateTarget;

    // 기존 게이트 위치 초기화 (필요한 경우)
    if ((gameMap[positionA.first][positionA.second] == gateTarget && 
         gameMap[positionB.first][positionB.second] == gateTarget)) {
        gameMap[positionA.first][positionA.second] = -1;
        gameMap[positionB.first][positionB.second] = -1;
    }

    // 새 위치 저장
    positionA = std::make_pair(y1, x1);
    positionB = std::make_pair(y2, x2);
}
