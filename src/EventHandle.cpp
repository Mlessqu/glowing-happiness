//
// Created by Missqu on 1/22/25.
//

#include "EventHandle.h"

#include <iostream>

#include<SFML/Graphics.hpp>
struct InputData;
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

void EventHandle::handle_events()
{
    while (const std::optional event = okno_ref_.pollEvent())
    {
        //window close

        if (event->is<sf::Event::Closed>())
        {
            state_machine_ref_.quit();
        }
        // /------------------------------------
#pragma region mouse events
        else if (const auto* mouse_pressed = event->getIf<sf::Event::MouseButtonPressed>()) //was mouse button pressed?
        {
            if (mouse_pressed->button == sf::Mouse::Button::Left)
            {
                input_data_.left_mouse_pressed = true;
                input_data_.mouse_pos_on_left_click = sf::Mouse::getPosition(okno_ref_);
            }
            else input_data_.left_mouse_pressed = false;
            if (mouse_pressed->button == sf::Mouse::Button::Right)
            {
                input_data_.right_mouse_pressed = true;
                input_data_.mouse_pos_on_right_click = sf::Mouse::getPosition(okno_ref_);
            }
            else input_data_.right_mouse_pressed = false;
        }
#pragma endregion
#pragma region keyboard events
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
        {
            input_data_.left = true;
        }else input_data_.left = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
        {
            input_data_.right = true;
        }else input_data_.right = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
        {
            input_data_.up = true;
        }else input_data_.up = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
        {
            input_data_.down = true;
        }else input_data_.down = false;

    }
#pragma endregion

}

EventHandle::EventHandle(StateMachine& _state_machine_ref, sf::RenderWindow& _okno):
state_machine_ref_{_state_machine_ref},
okno_ref_{_okno}
{

}

