#include "Snake.h"
#include "Game.h"

void Snake::init(){
    gameMap[10][5] = 4;
    gameMap[10][6] = 4;
    gameMap[10][7] = 4;
    snakeHeadPosition = {10, 7}; // {y, x}
    snakeTailPosition = {10, 5};
    currentDirection = 4;
    gateUsingChk = false;
}

bool Snake::setDirection(int direction){
    if(currentDirection + direction==3) return false;
    if(currentDirection + direction==7) return false;
    currentDirection = direction;
    return true;
}

int Snake::getDirection(){
    return currentDirection;
}

int Snake::getHeadObject(){
    int newHeadY = snakeHeadPosition.first + delta[currentDirection].first;
    int newHeadX = snakeHeadPosition.second + delta[currentDirection].second;
    return gameMap[newHeadY][newHeadX];
}

int Snake::newDirectionCalc(int y, int x, int dir){
    // 벽이 외곽에 있을 경우
    if(y==0) dir = 2;
    else if(x==0) dir = 4;
    else if(y==24) dir = 1;
    else if(x==24) dir = 3;
    else { // 벽이 중간에 있을 경우
        int rot[]={-1, 4, 3, 1, 2}, revRot[]={-1, 3, 4, 2, 1}, rev[]={-1, 2, 1, 4, 3};
        // 현재 진행 방향으로도 가능하면 그대로 진입
        if(gameMap[y + delta[dir].first][x + delta[dir].second] >= 0) return dir;
        // 시계 방향
        else if(gameMap[y + delta[rot[dir]].first][x + delta[rot[dir]].second] >= 0) return rot[dir];
        // 반시계 방향
        else if(gameMap[y + delta[revRot[dir]].first][x + delta[revRot[dir]].second] >= 0) return revRot[dir];
        // 반대 방향
        else return rev[dir];
    }
    return dir;
}

int Snake::move() {
    int object = getHeadObject();
    // gate
    if(object == 5){
        if(gateUsingChk) return -1;
        int y, x;
        int iy = snakeHeadPosition.first + delta[currentDirection].first, ix = snakeHeadPosition.second + delta[currentDirection].second;
        bool chk_found = false;
        // x, y = 반대쪽 게이트 위치
        for(y=0; y<25; ++y){
            for(x=0; x<25; ++x){
                if(!(iy == y && ix == x) && gameMap[y][x] == 5) {
                    chk_found = true;
                    break;
                }
            }
            if(chk_found) break;
        }
        gameMap[snakeHeadPosition.first][snakeHeadPosition.second] = currentDirection;
        // 새 게이트에서 사용될 방향 지정
        currentDirection = newDirectionCalc(y, x, currentDirection);
        // 게이트 반대쪽에 헤드 포지션 위치
        y += delta[currentDirection].first;
        x += delta[currentDirection].second;
        gameMap[y][x] = currentDirection;
        snakeHeadPosition = {y, x};

        reduce();
        gateUsingChk = true; // tail이 게이트를 완전히 통과할때까지 헤드는 게이트 이용불가
    }
    // growth item
    else if(object == 6){
        grow();
    }
    // poison item
    else if(object == 7){
        grow();
        reduce();
        reduce();
    }
    // floor
    else {
        grow();
        reduce();
    }
    return object;
}

// 머리 성장
void Snake::grow() {
    int newHeadY = snakeHeadPosition.first + delta[currentDirection].first;
    int newHeadX = snakeHeadPosition.second + delta[currentDirection].second;
    if(newHeadX<1 || newHeadY<1 || newHeadX>=24 || newHeadY>=24) return;
    gameMap[snakeHeadPosition.first][snakeHeadPosition.second] = currentDirection;
    gameMap[newHeadY][newHeadX] = currentDirection;
    snakeHeadPosition = {newHeadY, newHeadX};
}

// 꼬리 줄이기
void Snake::reduce() {
    int tailDirection = gameMap[snakeTailPosition.first][snakeTailPosition.second];
    int newTailY = snakeTailPosition.first + delta[tailDirection].first;
    int newTailX = snakeTailPosition.second + delta[tailDirection].second;
    if(gameMap[newTailY][newTailX] != 5){
        // 현재 꼬리 위치 초기화
        gameMap[snakeTailPosition.first][snakeTailPosition.second] = 0;
        // 꼬리 위치 업데이트
        snakeTailPosition = {newTailY, newTailX};
    }
    else { // 게이트 통과
        int y, x;
        bool chk_found = false;
        for(y=0; y<25; ++y){
            for(x=0; x<25; ++x){
                if(!(newTailY == y && newTailX == x) && gameMap[y][x] == 5) {
                    chk_found = true;
                    break;
                }
            }
            if(chk_found) break;
        }
        // 꼬리 위치 업데이트
        int tmpDirection;
        tmpDirection = newDirectionCalc(y, x, gameMap[snakeTailPosition.first][snakeTailPosition.second]);
        // 현재 꼬리 위치 초기화
        gameMap[snakeTailPosition.first][snakeTailPosition.second] = 0;
        // 새 위치 기록
        y += delta[tmpDirection].first;
        x += delta[tmpDirection].second;
        snakeTailPosition = {y, x};
        tailGateChk = true; // 게이트 생성 신호
        gateUsingChk = false; // 스네이크 게이트 사용 가능
    }
}