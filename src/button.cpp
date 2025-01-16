#include "button.hpp"
#include "input.hpp"
Button::Button(sf::Vector2f _size, sf::Vector2f _pos, const std::string &_caption,
               sf::RenderWindow &_okno_handle)
    : text(font), okno_handle(_okno_handle) {
  // font.openFromFile("arial.ttf");
  //-----
  button_body.setSize(_size);
  button_body.setFillColor(sf::Color::Green);
  button_body.setOrigin({_size.x / 2, _size.y / 2});
  button_body.setPosition(_pos);
  //-------
  text.setFont(font);
  text.setFillColor(sf::Color::Blue);
  text.setStyle(sf::Text::Bold);
  sf::Vector2f temp = button_body.getPosition();
  text.setPosition({temp.x - 30, temp.y - 10});
  text.setString(_caption);
  text.setCharacterSize(24);
}

Button::Button(sf::Vector2f _size, sf::Vector2f _pos, const std::string& _caption,
               sf::RenderWindow &_okno_handle, const std::function<void()> &
               _callback)
    : text(font), okno_handle(_okno_handle) {

  //-----
  button_body.setSize(_size);
  button_body.setFillColor(sf::Color::Green);
  button_body.setOrigin({_size.x / 2, _size.y / 2});
  button_body.setPosition(_pos);
  //-------
  text.setFont(font);
  text.setFillColor(sf::Color::Blue);
  text.setStyle(sf::Text::Bold);
  sf::Vector2f temp = button_body.getPosition();
  text.setPosition({temp.x - 30, temp.y - 10});
  text.setString(_caption);
  text.setCharacterSize(24);
  // callback function
  callback = _callback;
}
void Button::update() const {
  if (callback == nullptr)
    return;
  if (this->button_body.getGlobalBounds().contains(input_data.mouse_pos) &&
      input_data.left_mouse) {
    callback();
  }
}
