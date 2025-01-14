#pragma once
#include "input.hpp"
#include "utility.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#include <functional>
#include <string>
extern sf::Font font;
class Button : public sf::Drawable {

public:
  Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption,
         sf::RenderWindow &_okno_handle);
  Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption,
         sf::RenderWindow &_okno_handle, std::function<void()> _callback);
  sf::Text text;
  std::function<void()> callback = nullptr;
  void update();

private:
  sf::RectangleShape button_body;
  sf::RenderWindow &okno_handle;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    target.draw(button_body);
    target.draw(text);
  }
};

