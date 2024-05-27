#include "Input.h"
#include "Game.h"
#include <ncurses.h>

Input::Input(){
    cbreak();                // 입력 버퍼링 비활성화
    noecho();                // 입력된 문자 화면에 표시하지 않음
    keypad(stdscr, TRUE);    // 키패드 모드 활성화
    nodelay(stdscr, TRUE);   // 논블로킹 모드 활성화
}

void Input::getInput() {
    int ch = getch();
    if(ch == KEY_UP) direction = 1;
    else if(ch == KEY_DOWN) direction = 2;
    else if(ch == KEY_LEFT) direction = 3;
    else if(ch == KEY_RIGHT) direction = 4;
}

void Input::setDirection(int newDirection) {
    direction = newDirection;
}

int Input::getDirection() {
    return direction;
}
