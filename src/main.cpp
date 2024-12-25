#include <SFML/Graphics.hpp>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Playfield SFML3.0");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional _event = window.pollEvent())
        {
            if (_event->is<sf::Event::Closed>())
            {
                window.close();
            }else if(const auto* key_pressed = _event->getIf<sf::Event::KeyPressed>())
        {
            if( key_pressed->scancode == sf::Keyboard::Scancode::Escape)
            {
                window.close();
            }
        }
        }

        window.clear();
        window.display();
    }
}
