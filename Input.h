#ifndef INPUT_H
#define INPUT_H

class Input {
public:
    Input();
    void getInput();
    void setDirection(int newDirection);
    int getDirection();
private:
    int direction{4};
};

#endif
