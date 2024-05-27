#ifndef ITEM_H
#define ITEM_H

#include <utility>
#include <ctime>

class Item {
public:
    Item(int target);
    void createItem();
    bool timeOutChk(int chkTime); // 생성된지 chkTime 이상인지 확인
private:
    std::pair<int, int> itemPosition;
    int itemTarget;
    std::time_t creationTime;
};

#endif
