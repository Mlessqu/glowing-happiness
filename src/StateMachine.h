//
// Created by Missqu on 1/16/25.
//

#ifndef STATESMACHINE_H
#define STATESMACHINE_H
#include <memory>
#include <stack>
#include<SFML/Graphics.hpp>

namespace sf{class RenderWindow;}
class State;



class StateMachine {
    public:
    StateMachine();
    ~StateMachine();
    void next_state();
    void pop_state();
    void update();
    void draw();
    void quit();
    void run(std::unique_ptr<State> _state);
    [[nodiscard]] bool running() const;
    template <typename T>
    static std::unique_ptr<T> create_new_state(StateMachine &_state_machine,sf::RenderWindow &_okno);

    private:
    bool is_running;
    bool is_popped;
    std::stack<std::unique_ptr<State>> states;
};

template <typename T>
std::unique_ptr<T> StateMachine::create_new_state(StateMachine &_state_machine, sf::RenderWindow& _okno)
{

    auto new_state = std::unique_ptr<T>{nullptr};
    new_state = std::make_unique<T>(_state_machine, _okno);
    return new_state;
}


#endif //STATESMACHINE_H
