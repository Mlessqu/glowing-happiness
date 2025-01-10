#pragma once
#include <SFML/Graphics.hpp>
#include <string>
extern sf::Font font;
class Button : public sf::Drawable
{

public:
    sf::RectangleShape button_body;
    Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption);

private:
    sf::Text text;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(button_body);
        target.draw(text);
    }
};

Button::Button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption) : text(font)
{
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
    text.setPosition(button_body.getPosition());
    text.setString(_caption);
    text.setCharacterSize(24);
}