//
// Created by Missqu on 1/22/25.
//

#ifndef EVENTHANDLE_H
#define EVENTHANDLE_H
#include<SFML/Graphics.hpp>
#include"../StateMachine.h"
/*Event visitor, overloaded visitation*/

class EventHandle {
public:
    static EventHandle &get_instance(StateMachine& _state_machine_ref, sf::RenderWindow& _okno);
    void handle_events(sf::RenderWindow &_okno);
private:
    static EventHandle* instance_;
    EventHandle(StateMachine& _state_machine_ref, sf::RenderWindow &_okno);
    StateMachine& state_machine_ref_;
    sf::RenderWindow& okno_ref_;
};



#endif //EVENTHANDLE_H
