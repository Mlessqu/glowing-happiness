//
// Created by Missqu on 1/22/25.
//

#include "EventHandle.h"
#include <SFML/Window.hpp>
class EventHandle;
namespace sf
{
    class RenderWindow;
}
EventHandle *EventHandle::instance_=nullptr;
EventHandle  &EventHandle::get_instance(StateMachine& _state_machine_ref, sf::RenderWindow& _okno)
{
    if (EventHandle::instance_==nullptr)
        EventHandle::instance_ = new EventHandle( _state_machine_ref, _okno);
    return *EventHandle::instance_;
}

void EventHandle::handle_events( sf::RenderWindow& _okno)
{
    while (const std::optional event = _okno.pollEvent())
    {

    }
}

EventHandle::EventHandle(StateMachine& _state_machine_ref, sf::RenderWindow& _okno):
state_machine_ref_{_state_machine_ref},
okno_ref_{_okno}
{

}

