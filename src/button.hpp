#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class button : public sf::Drawable, public sf::Transformable
{

public:
    button::button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption)
        sf::RectangleShape button_body({150, 50});

    sf::Text text(font);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(button_body, states);
        target.draw(text, states);
    }
};

button::button(sf::Vector2f _size, sf::Vector2f _pos, std::string _caption)
{
    button_body.setFillColor(sf::Color::Green);
    button_body.setOrigin({100, 50});
    button_body.setPosition({150, 50});
    //-------
    text.setFillColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);
    text.setPosition(button_body.getPosition());
    text.setString(_caption);
    text.setCharacterSize(24);
}