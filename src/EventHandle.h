//
// Created by Missqu on 1/22/25.
//

#ifndef EVENTHANDLE_H
#define EVENTHANDLE_H
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
/*Event visitor, overloaded visitation*/
struct InputData
    {
        sf::Vector2i mouse_pos_on_left_click;
        sf::Vector2i mouse_pos_on_right_click;
        bool left_pressed = false;
         bool right_pressed = false;
    };
class EventHandle {
public:
    static EventHandle &get_instance(StateMachine& _state_machine_ref, sf::RenderWindow& _okno);
    void handle_events();
    InputData input_data_;
private:
    static EventHandle* instance_;
    EventHandle(StateMachine& _state_machine_ref, sf::RenderWindow &_okno);
    StateMachine& state_machine_ref_;
    sf::RenderWindow& okno_ref_;

    //------------------------
    //input values

};



#endif //EVENTHANDLE_H
