#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <string>
extern sf::Font font;
class Button : public sf::Drawable {

public:
  sf::RectangleShape button_body;
  Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption);
  Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption,
         std::function<void()> _callback);
  sf::Text text;
  std::function<void()> callback;
  bool on_click();

private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    target.draw(button_body);
    target.draw(text);
  }
};

Button::Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption)
    : text(font) {
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

Button::Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption,
               std::function<void()> _callback)
    : text(font) { //-----
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

bool Button::on_click() {}