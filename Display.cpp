#include "Display.h"
#include "Game.h"

Display::Display() {
    use_env(TRUE);
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
}

void Display::init() {
    colorDefine();
    drawUI();
}

// 콘솔에 출력할 색상 정의
void Display::colorDefine(){
    // ncurses 컬러표
    // https://static.miraheze.org/rosettacodewiki/b/bf/Terminal_control%2Ccolored_text.png
    init_pair(1, 15, COLOR_BLACK); // 1: 벽
    init_pair(2, 7, COLOR_BLACK); // 2: 이뮨벽
    init_pair(3, 8, COLOR_BLACK); // 3: floor 격자칸(회색)
    init_pair(4, 0, COLOR_BLACK); // 4: floor 격자칸(검정)
    init_pair(5, 15, COLOR_BLACK); // 5: 텍스트(검정 바탕에 흰색 글자)
    init_pair(6, 11, COLOR_BLACK); // 6: 스네이크 몸통
    init_pair(7, 6, COLOR_BLACK); // 7: 스네이크 머리
    init_pair(8, 13, COLOR_BLACK); // 8: 게이트
    init_pair(9, 2, COLOR_BLACK); // 9: 아이템
    init_pair(10, 1, COLOR_BLACK); // 10: 독
    init_pair(11, 15, 2); // 11: 게임 클리어 메세지
    init_pair(12, 15, 1); // 12: 게임 실패 메세지
}

void Display::drawBox(int px, int py, int width, int height, int colorIndex){
    attron(COLOR_PAIR(colorIndex));
    // 박스 그리기
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            mvaddch(py + i, px + j, ACS_CKBOARD); // 박스 채우기 문자
        }
    }
    attroff(COLOR_PAIR(colorIndex));
}

void Display::drawGameMap(){
    int px = 0, py = 0, width = 4, height = 2;
    for(int y = 0; y < 25; ++y) {
        for(int x = 0; x < 25; ++x) {
            // 스네이크 머리
            if(y==snakeHeadPosition.first && x==snakeHeadPosition.second){
                drawBox(px, py, width, height, 7);
            }
            // 빈칸
            else if (gameMap[y][x] == 0) {
                //if((x%2 + y%2)%2) drawBox(px, py, width, height, 3);
                //else drawBox(px, py, width, height, 4);
            }
            // 벽
            else if (gameMap[y][x] == -1) {
                drawBox(px, py, width, height, 1);
            }
            // 이뮨 벽
            else if (gameMap[y][x] == -2) {
                drawBox(px, py, width, height, 2);
            }
            // 스네이크 몸통
            else if (1<=gameMap[y][x] && gameMap[y][x]<=4) {
                drawBox(px, py, width, height, 6);
            }
            // 게이트
            else if(gameMap[y][x] == 5){
                drawBox(px, py, width, height, 8);
            }
            // 아이템
            else if(gameMap[y][x] == 6){
                drawBox(px, py, width, height, 9);
            }
            // 독
            else if(gameMap[y][x] == 7){
                drawBox(px, py, width, height, 10);
            }
            px += width;
        }
        py += height;
        px = 0; // px를 초기화하여 새 줄로 이동
    }
}

void Display::drawScoreBoard() {
    char tmpText[50];
    attron(COLOR_PAIR(5));
    mvaddstr(1, 110, "==== Score Board ====");
    sprintf(tmpText, "B : %d / %d", scoreCurrentLen, scoreMaxLen); mvaddstr(3, 116, tmpText);
    sprintf(tmpText, "+ : %d", scoreGrowthItems); mvaddstr(4, 116, tmpText);
    sprintf(tmpText, "- : %d", scorePoisonItems); mvaddstr(5, 116, tmpText);
    sprintf(tmpText, "G : %d", scoreGate); mvaddstr(6, 116, tmpText);
    sprintf(tmpText, "T : %ds", scoreTime); mvaddstr(7, 116, tmpText);
    mvaddstr(9, 110, "=====================");
    attroff(COLOR_PAIR(5));
}

void Display::drawMissionBoard(){
    char tmpText[50];
    attron(COLOR_PAIR(5));
    mvaddstr(13, 110, "====== Mission ======");
    sprintf(tmpText, "B : %d %c", missionMaxLen, (scoreMaxLen>=missionMaxLen?'v':' ')); mvaddstr(15, 116, tmpText);
    sprintf(tmpText, "+ : %d %c", missionGrowthItems, (scoreGrowthItems>=missionGrowthItems?'v':' ')); mvaddstr(16, 116, tmpText);
    sprintf(tmpText, "- : %d %c", missionPoisonItems, (scorePoisonItems>=missionPoisonItems?'v':' ')); mvaddstr(17, 116, tmpText);
    sprintf(tmpText, "G : %d %c", missionGate, (scoreGate>=missionGate?'v':' ')); mvaddstr(18, 116, tmpText);
    mvaddstr(20, 110, "=====================");
    attroff(COLOR_PAIR(5));
}

void Display::drawGameOver(){
    attron(COLOR_PAIR(12));
    mvaddstr(24, 110, "Game Over!  press(q) to quit game");
    attroff(COLOR_PAIR(12));
    refresh();
}

void Display::drawStageClear(){
    attron(COLOR_PAIR(11));
    mvaddstr(24, 110, "Stage Clear!  press(q) to next stage");
    attroff(COLOR_PAIR(11));
    refresh();
}

void Display::drawGameClear(){
    attron(COLOR_PAIR(11));
    mvaddstr(24, 110, "Congratulation! Game Clear!  press(q) to quit game");
    attroff(COLOR_PAIR(11));
    refresh();
}

void Display::drawUI() {
    // ui 정리
    clear();

    // ui 구성
    drawGameMap();
    drawScoreBoard();
    drawMissionBoard();

    // ui 출력
    refresh();
}

void Display::clearAllObject(){
    clear();
    refresh();
    endwin(); // 터미널 복원
}
