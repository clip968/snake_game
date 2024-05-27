#include "Item.h"
#include "Game.h"
#include <ctime>
#include <random>

Item::Item(int target) : itemTarget(target) {}

int getRandomNum(int low, int high){
    std::random_device rd;
    std::mt19937 mt(rd()); 
    std::uniform_int_distribution<int> dist(low, high); 
    return dist(mt);
}

void Item::createItem() {
    int x, y;
    do{
        x = getRandomNum(1, 23);
        y = getRandomNum(1, 23);
    }while(gameMap[y][x]!=0);
    
    gameMap[y][x] = itemTarget;

    // 기존에 생성된 아이템은 제거
    if(gameMap[itemPosition.first][itemPosition.second] == itemTarget){
        gameMap[itemPosition.first][itemPosition.second] = 0;
    }

    // 새 생성 위치 기록
    itemPosition.first = y;
    itemPosition.second = x;

    // 아이템 생성 시간 기록
    creationTime = std::time(nullptr);
}

bool Item::timeOutChk(int chkTime){
    std::time_t currentTime = std::time(nullptr);
    double difference = std::difftime(currentTime, creationTime);
    return difference >= chkTime;
}