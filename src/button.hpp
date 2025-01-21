#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <string>
class Button : public sf::Drawable {

public:
  Button(sf::Vector2f _size, sf::Vector2f _pos,const std::string &_caption, const sf::Font& _font,
         sf::RenderWindow &_okno_handle);
  Button(sf::Vector2f _size, sf::Vector2f _pos, const std::string& _caption, const sf::Font& _font,
         sf::RenderWindow &_okno_handle,  const std::function<void()> &_callback);
  sf::Text text;

  void update();
	void set_callback(std::function<void()> _callback);
private:
	std::function<void(void)> callback = nullptr;
	const sf::Font &font_;
  sf::RectangleShape button_body_;
  sf::RenderWindow &okno_handle_;
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    target.draw(button_body_);
    target.draw(text);
  }
};
