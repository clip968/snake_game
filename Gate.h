#ifndef GATE_H
#define GATE_H

#include <utility>

class Gate {
public:
    Gate();
    Gate(int target);
    void createGate();
    std::pair<int, int> getPositionA();
    std::pair<int, int> getPositionB();
private:
    int gateTarget;
    std::pair<int, int> positionA;
    std::pair<int, int> positionB;
    
};

#endif
