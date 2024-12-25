#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include"logic.hpp"
#include"utility.hpp"
#include"states.hpp"

sf::Font font;
sf::Text zwyciezca_text;
sf::Texture board_texture; // tekstura boardu
sf::Sprite board_sp;
//---------------------
sf::Texture the_o;
sf::Sprite the_o_sp;
//---------------------
sf::Texture the_x;
sf::Sprite the_x_sp;
int main()
{
    //---------------------
    // #####@@@@@@@@@@@@@@@@@@@@@@
    // inicjalizacja
    auto window = sf::RenderWindow({300u, 300u}, "Tic-tac-toe");
    window.setFramerateLimit(10);

    //---------------------
    if (!board_texture.loadFromFile("board.png"))
    {
    }
    else // ladowanie boarda
    board_sp.setTexture(board_texture);
    //---------------------
    if (!the_o.loadFromFile("o.png"))
    {
        // error...
    }
    else
        the_o_sp.setTexture(the_o);
    //---------------------
    if (!the_x.loadFromFile("x.png"))
    {
        // error...
    }
    else
        the_x_sp.setTexture(the_x);
    //---------------------
    // load font
    if (!font.loadFromFile("arial.ttf"))
    {
        // error...
    }
    //---------------
    // select the font
    zwyciezca_text.setFont(font);
    zwyciezca_text.setCharacterSize(24);
    zwyciezca_text.setFillColor(sf::Color::Red);
    zwyciezca_text.setStyle(sf::Text::Bold);
    // #####@@@@@@@@@@@@@@@@@@@@@@
    // MAIN LOOP
    sf::Event event;
    menu_loop(window,event);

    //game_loop(window, event);
    
    return 0;
}
