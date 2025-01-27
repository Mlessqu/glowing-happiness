//
// Created by Missqu on 1/16/25.
//

#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
class StateMachine;
class ResourceManager;
class EventHandle;
namespace sf
{
    class RenderWindow;
}
class State
{
public:
    State(StateMachine &_machine_ref, sf::RenderWindow &_okno);

    virtual ~State() = default;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void update(sf::Time& _delta_time, sf::Time& _lag) = 0;
    virtual void draw() = 0;
    std::unique_ptr<State> next_state();
protected:
    //void handle_event();
    StateMachine & machine_ref_;
    sf::RenderWindow& okno_ref_;
    std::unique_ptr<State> next_state_ptr_;
    ResourceManager& resource_manager_ref_;
    EventHandle& event_handle_ref_;
private:
};


#endif //STATE_H
