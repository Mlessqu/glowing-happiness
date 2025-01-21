#include "Button.h"

#include "ResourceManager.h"
#include "utility.hpp"
#include <iostream>
class State;
Button::Button(sf::Vector2f _size, sf::Vector2f _pos, const std::string &_caption,const sf::Font& _font,
               sf::RenderWindow &_okno_handle)
    : font_{_font}, text{font_},
okno_handle_(_okno_handle)
{
  // font.openFromFile("arial.ttf");
  //-----
  button_body_.setSize(_size);
  button_body_.setFillColor(sf::Color::Green);
  button_body_.setOrigin({_size.x / 2, _size.y / 2});
  button_body_.setPosition(_pos);
  //-------
  // text.setFont(font);
  text.setFillColor(sf::Color::Blue);
  text.setStyle(sf::Text::Bold);
  sf::Vector2f temp = button_body_.getPosition();
  text.setPosition({temp.x - 30, temp.y - 10});
  text.setString(_caption);
  text.setCharacterSize(24);
}

Button::Button(sf::Vector2f _size, sf::Vector2f _pos, const std::string& _caption,const sf::Font& _font,
               sf::RenderWindow &_okno_handle, const std::function<void()>  &_callback )
    :font_{_font}, text(_font), okno_handle_(_okno_handle) {
  //-----
  //_ptr_to_next_state
  set_callback(_callback);
  button_body_.setSize(_size);
  button_body_.setFillColor(sf::Color::Green);
  button_body_.setOrigin({_size.x / 2, _size.y / 2});
  button_body_.setPosition(_pos);
  //-------
  // text.setFont(font);
  text.setFillColor(sf::Color::Blue);
  text.setStyle(sf::Text::Bold);
  sf::Vector2f temp = button_body_.getPosition();
  text.setPosition({temp.x - 30, temp.y - 10});
  text.setString(_caption);
  text.setCharacterSize(24);
  // callback function
}
void Button::update() {
  if (callback == nullptr)
    return;
  if(button_body_.getGlobalBounds().contains(relative_mouse_pos(okno_handle_)))
    {
    std::cout << "Callback called ";
    callback();
  }
}

void Button::set_callback(std::function<void()> _callback) {
  callback =std::move( _callback);
}
