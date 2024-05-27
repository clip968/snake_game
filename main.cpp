#include "Game.h"

int main() {
    bool gameOverChk = false;
    Game game[4];
    for(int i=0; i<4; ++i){ // 스테이지 4개
        game[i].init(i);
        gameOverChk = game[i].run();
        game[i].cleanup();
        if(!gameOverChk) break; // 게임 오버시 프로그램 종료
    }
    return 0;
}
    