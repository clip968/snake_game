#include "Game.h"
#include <unistd.h>
#include <ctime>

// 전역 변수 정의
char gameMap[25][25] = {};
std::pair<int, int> snakeHeadPosition;
int scoreCurrentLen;
int scoreMaxLen;
int scoreGrowthItems;
int scorePoisonItems;
int scoreGate;
int scoreTime;
int missionMaxLen;
int missionGrowthItems;
int missionPoisonItems;
int missionGate;
bool tailGateChk = false;

#define ITEM_REMAKE_TIME 20

Game::Game() : growthItem(6), poisonItem(7), gate(5) {}

void Game::init(int mapIndex) {
    // 게임에서 사용될 각종 변수 초기화
    stage = mapIndex;
    chkGameOver = false;
    tick = 400;
    startTime = std::time(nullptr); // 현재 시간 저장
    initMap(mapIndex);
    initScore();
    initMission();
    // 스네이크 생성
    snake.init();
    // 아이템 2개 생성
    growthItem.createItem();
    poisonItem.createItem();
    //게이트 생성
    gate.createGate();
    display.init();
}

void Game::initMap(int mapIndex){
    // 기본 맵 초기화(외곽 -1, 나머지 0)
    for (int y = 0; y < 25; ++y) {
        for (int x = 0; x < 25; ++x) {
            if (y == 0 || y == 24 || x == 0 || x == 24) {
                gameMap[y][x] = -1; // 외곽은 -1
            } else {
                gameMap[y][x] = 0; // 나머지는 0
            }
        }
    }
    gameMap[0][0] = gameMap[0][24] = gameMap[24][0] = gameMap[24][24] = -2;
    if(mapIndex == 1){ // 스테이지2는 가운데 가로줄로 벽
        for (int i = 4; i < 21; ++i) {
            gameMap[12][i] = -1;
        }
    }
    else if(mapIndex == 2){ // 스테이지 3은 가로줄 2개
        for (int i = 4; i < 21; ++i) {
            gameMap[5][i] = -1;
            gameMap[20][i] = -1;
        }
    }
    else if(mapIndex == 3){ // 스테이지 4는 +자 벽
        for (int i = 4; i < 21; ++i) {
            if(i>=11 && i<=13) continue;
            gameMap[12][i] = gameMap[i][12] = -1;
        }
    }
}

void Game::initScore(){
    scoreCurrentLen = scoreMaxLen = 3;
    scoreGrowthItems = scorePoisonItems = scoreGate = 0;

}

void Game::initMission(){
    missionMaxLen = 10 + stage; // 최대길이
    missionGrowthItems = 5 + stage; // 획득 growth 아이템
    missionPoisonItems = 2 + stage; // 획득 poison 아이템
    missionGate = 1 + stage; // 사용한 게이트
}

void Game::timeUpdate() {
    std::time_t currentTime = std::time(nullptr);
    double difference = std::difftime(currentTime, startTime);
    scoreTime = (int)difference;
}

// 게임 실행
bool Game::run() {
    bool gameStatChk;
    int cnt{};
    while (true) {
        // 입력 처리
        input.getInput();
        if(!snake.setDirection(input.getDirection())){ // 진행방향 반대 방향키 입력
            display.drawGameOver();
            return false; // 게임 오버로 종료
        }
        if(cnt==0){
            gameStatChk = update();  // 각종 상태 업데이트
            timeUpdate(); // 시간정보 업데이트
            if(!gameStatChk) {
                display.drawGameOver();   
                return false; // 게임오버로 게임 종료
            }
            display.drawUI(); // 게임화면 출력
        }
        // 게임 미션 클리어 확인
        if(scoreMaxLen>=missionMaxLen && scoreGrowthItems>=missionGrowthItems && scorePoisonItems>=missionPoisonItems && scoreGate>=missionGate) {
            if(stage<3) display.drawStageClear();
            else display.drawGameClear(); // 마지막 스테이지
            return true; // 게임 클리어
        }

        usleep(tick); // 틱동안 정지
        ++cnt;
        if(cnt==1000) cnt = 0;
    }
    return true;
}

void Game::gameSpeedUpdate(){
    if(scoreCurrentLen > 5){
        tick = 350;
    }
    else if(scoreCurrentLen > 7){
        tick = 300;
    }
    else if(scoreCurrentLen > 9){
        tick = 250;
    }

}

void Game::itemsTimeChk(){
    if(growthItem.timeOutChk(ITEM_REMAKE_TIME)) growthItem.createItem();
    if(poisonItem.timeOutChk(ITEM_REMAKE_TIME)) poisonItem.createItem();
}

bool Game::update() {
    int object = snake.move();
    if(object<0 || (object>=1 && object<=4)) {
        return false;
    }
    else if(object == 5) {
        input.setDirection(snake.currentDirection); // 게이트 통과하면 현재 진행 방향 저장
        ++scoreGate;
    }
    else if(object == 6) {
        growthItem.createItem();
        ++scoreCurrentLen;
        scoreMaxLen = scoreCurrentLen>scoreMaxLen?scoreCurrentLen:scoreMaxLen;
        ++scoreGrowthItems;
    }
    else if(object == 7) {
        -- scoreCurrentLen;
        ++scorePoisonItems;
        if(scoreCurrentLen<3){  // 몸 길이 3미만 게임 오버
            display.drawUI();
            return false;
        }
        poisonItem.createItem();
    }
    if(tailGateChk) {
        tailGateChk = false;
        gate.createGate();
    }
    gameSpeedUpdate(); // 현재 길이에 비례해 게임 속도 증가
    itemsTimeChk(); // 아이템들 생성 시간 확인해서 5초 지나면 삭제하고 새 아이템 생성
    return true;
}

void Game::cleanup(){
    char ch = getch();
    while(ch != 'q'){
        ch = getch();
    }
    // 터미널 복원
    display.clearAllObject();
}