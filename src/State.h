//
// Created by Missqu on 1/16/25.
//

#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
class StateMachine;

namespace sf
{
    class RenderWindow;
}
/*TODO */
class State
{
public:
    State(StateMachine &_machine_ref, sf::RenderWindow &_okno);

    virtual ~State() = default;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    std::unique_ptr<State> next_state();
protected:
    StateMachine & machine_ref_;
    sf::RenderWindow& okno_ref_;
    std::unique_ptr<State> next_state_ptr_;
private:
};


#endif //STATE_H
