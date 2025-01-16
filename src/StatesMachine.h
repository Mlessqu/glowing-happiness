//
// Created by Missqu on 1/16/25.
//

#ifndef STATESMACHINE_H
#define STATESMACHINE_H
#include <stack>
#include "State.h"
#include "SFML/Window/WindowEnums.hpp"


class StatesMachine {
    public:
    StatesMachine();
    ~StatesMachine();
    void run();
private:
    std::stack<State*> states;
};



#endif //STATESMACHINE_H
