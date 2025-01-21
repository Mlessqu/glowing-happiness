

#include "states.hpp"
#include "ai.hpp"
#include "button.hpp"
#include "resources.hpp"
#include "utility.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <bits/stdc++.h>
#include <string>
#include <vector>
void menu_loop(sf::RenderWindow &_okno) {
  // menu initialization here
  std::vector<std::unique_ptr<Button>> buttons;
  Button start_button({200, 30}, {150, 50}, "CO OP", _okno,
                      [&] { co_op_game_loop(_okno); });

  Button vs_ai_button({200, 30}, {150, 100}, "VS AI", _okno,
                      [&] { ai_game_loop(_okno); });

  Button over_network_client({200, 50}, {150, 150}, "network as client", _okno,
                             [&] { network_loop_client(_okno); });
  Button over_network_host({200, 50}, {150, 200}, "network as host", _okno,
                           [&] { network_loop_host(_okno); });
  over_network_client.text.setCharacterSize(14);
  over_network_host.text.setCharacterSize(14);
  buttons.push_back(std::make_unique<Button>(over_network_client));
  buttons.push_back(std::make_unique<Button>(over_network_host));
  buttons.push_back(std::make_unique<Button>(vs_ai_button));
  buttons.push_back(std::make_unique<Button>(start_button));
  // loop proper
  while (_okno.isOpen())
    {
    while (const std::optional _event = _okno.pollEvent()) {
      if (_event->is<sf::Event::Closed>()) {
        _okno.close();
      }else if (_event->is<sf::Event::MouseButtonPressed>())
      {
          for (const auto & button : buttons)
          {
            button->update();
          }
      }
    }
    start_button.update();
    vs_ai_button.update();
    over_network_client.update();
    over_network_host.update();
    _okno.clear();
    _okno.draw(start_button);
    _okno.draw(vs_ai_button);
    _okno.draw(zwyciezca_text);
    _okno.draw(over_network_client);
    _okno.draw(over_network_host);
    _okno.display();
  }
}

void co_op_game_loop(sf::RenderWindow &_okno) {
  // game loop initialization here
  std::vector<sf::Sprite> sprites_to_draw;
  sprites_to_draw.push_back(board_sp);
  _okno.clear();
  _okno.draw(board_sp);
  _okno.display();
  Msq::GameState original_game_state = {};
  sf::Text debug_text(font);
  debug_text.setFillColor(sf::Color::Red);
  debug_text.setStyle(sf::Text::Bold);
  debug_text.setPosition({20, 20});
  debug_text.setCharacterSize(24);
  while (_okno.isOpen()) {
    while (const std::optional _event = _okno.pollEvent()) // poll events
    {
      debug_text.setString(
          debug_string(original_game_state.tura, original_game_state.wybor));
      if (_event->is<sf::Event::Closed>()) {
        _okno.close();
      }
      //-----------------
      if (const auto *mouseButtonPressed =
              _event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
          sf::Vector2f mouse_pos = relative_mouse_pos(_okno);
          original_game_state.wybor = get_1D_index(
              mouse_pos.x / 100,
              mouse_pos.y / 100); // translate mouse cord into 1D array 0-8
          if (Msq::is_valid_move(&original_game_state)) {

            if (Msq::czyja_tura(&original_game_state) == 2) {

              the_o_sp.setPosition(
                  {get_2D_index(original_game_state.wybor).x * 100.f,
                   get_2D_index(original_game_state.wybor).y * 100.f});
              sprites_to_draw.push_back(the_o_sp);
              // kolkos
            } else {

              the_x_sp.setPosition(
                  {get_2D_index(original_game_state.wybor).x * 100.f,
                   get_2D_index(original_game_state.wybor).y * 100.f});
              sprites_to_draw.push_back(the_x_sp);
              // krzyzyks
            }
            Msq::make_move(&original_game_state);
          }
          // draw_board(board);
        }
      }
    }
    _okno.clear(sf::Color::Green);
    _okno.draw(board_sp);
    for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end();
         itr++) // we loop over things to draw here
    {
      _okno.draw(*itr);
    }
    _okno.draw(debug_text);
    _okno.draw(zwyciezca_text);
    _okno.display();
    if (original_game_state.exit_flag == true) {
      winner_loop(_okno);
      return;
    }
  }
}

void ai_game_loop(sf::RenderWindow &_okno) {
  // game loop initialization here
  // game loop initialization here
  std::vector<sf::Sprite> sprites_to_draw;
  sprites_to_draw.push_back(board_sp);
  _okno.clear();
  _okno.draw(board_sp);
  _okno.display();
  Msq::GameState original_game_state = {};
  sf::Text debug_text(font);
  debug_text.setFillColor(sf::Color::Red);
  debug_text.setStyle(sf::Text::Bold);
  debug_text.setPosition({20, 20});
  debug_text.setCharacterSize(24);
  while (_okno.isOpen()) {
    while (const std::optional _event = _okno.pollEvent()) // poll events
    {
      debug_text.setString(
          debug_string(original_game_state.tura, original_game_state.wybor));
      if (_event->is<sf::Event::Closed>()) {
        _okno.close();
      }
      //-----------------
      if (const auto *mouseButtonPressed =
              _event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
          sf::Vector2f mouse_pos = relative_mouse_pos(_okno);
          original_game_state.wybor = get_1D_index(
              mouse_pos.x / 100,
              mouse_pos.y /
                  100); // translate mouse cord into 1D array 0-8, division by
                        // 100, because it is 100pixels wide and high
          if (Msq::czyja_tura(&original_game_state) == 1) {
            //----------------------------------------------------
            the_x_sp.setPosition(
                {get_2D_index(original_game_state.wybor).x * 100.f,
                 get_2D_index(original_game_state.wybor).y * 100.f});
            sprites_to_draw.push_back(the_x_sp);
            //--------------------------------
            Msq::make_move(&original_game_state);
            if (original_game_state.exit_flag == true) {
              break;
            }
          }

          // krzyzyks

          if (Msq::czyja_tura(&original_game_state) == 2) {

            do {
              original_game_state.wybor = ai_random_move(&original_game_state);
            } while (Msq::is_valid_move(&original_game_state));
            the_o_sp.setPosition(
                {get_2D_index(original_game_state.wybor).x * 100.f,
                 get_2D_index(original_game_state.wybor).y * 100.f});
            sprites_to_draw.push_back(the_o_sp);
            Msq::make_move(&original_game_state);
            if (original_game_state.exit_flag == true) {
              break;
            }
            // kolkos
          }
        }
      }
      // draw_board(board);
    }

    _okno.clear(sf::Color::Green);
    _okno.draw(board_sp);
    for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end();
         itr++) // we loop over things to draw here
    {
      _okno.draw(*itr);
    }
    _okno.draw(zwyciezca_text);
    _okno.draw(debug_text);
    _okno.display();
    if (original_game_state.exit_flag == true) {
      winner_loop(_okno);
      return; // exit function, effectively exit state
              // we exit it only here!
    }
  }
}
void winner_loop(sf::RenderWindow &_okno) {
  while (_okno.isOpen()) {
    while (const std::optional _event = _okno.pollEvent()) {
      if (_event->is<sf::Event::Closed>()) {
        _okno.close();
      }
      if (const auto *mouseButtonPressed =
              _event->getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseButtonPressed->button == sf::Mouse::Button::Right) {
          return;
        }
      }
    }
  }
}
void network_loop_host(sf::RenderWindow &_okno) {
  // game loop initialization here
  std::vector<sf::Sprite> sprites_to_draw;
  sprites_to_draw.push_back(board_sp);
  _okno.clear();
  _okno.draw(board_sp);
  _okno.display();
  Msq::GameState original_game_state = {};
  sf::Text debug_text(font);
  debug_text.setFillColor(sf::Color::Red);
  debug_text.setStyle(sf::Text::Bold);
  debug_text.setPosition({20, 20});
  debug_text.setCharacterSize(24);
  //------------------------------------------
  // Network
  sf::TcpListener listener;
  sf::TcpSocket client;

  std::string errors;
  sf::Packet packet;
  int wybor_przeciwnika;
  packet >> wybor_przeciwnika;
  if (listener.listen(53000) != sf::Socket::Status::Done) {
    errors.append("Nie udalo sie sluchac portu 5300");
  }
  if (listener.accept(client) != sf::Socket::Status::Done) {
    errors.append("Nie udalo sie polaczyc z clientem");
  }
  // init ends here
  while (_okno.isOpen()) {
    //-------------------------
    while (const std::optional _event = _okno.pollEvent()) // poll events
    {
      debug_text.setString(errors);
      if (_event->is<sf::Event::Closed>()) {
        _okno.close();
      }
      if (const auto* mouseButtonPressed = _event->getIf<sf::Event::MouseButtonPressed>())
      {
        //-----------------
        // host robie ture
        if (Msq::czyja_tura(&original_game_state) == 1)
          {

          original_game_state.wybor = get_1D_index(relative_mouse_pos(_okno).x,
                                                   relative_mouse_pos(_okno).y);
          if (Msq::is_valid_move(&original_game_state)) {
            packet << original_game_state.wybor;
            while (client.send(packet) == sf::Socket::Status::Partial) {
              // until we succesfully send the packet we loop it
            }

            the_x_sp.setPosition(
                {get_2D_index(original_game_state.wybor).x * 100.f,
                 get_2D_index(original_game_state.wybor).y * 100.f});
            sprites_to_draw.push_back(the_x_sp);
            Msq::make_move(&original_game_state);
          }
        }
      }
    }


    // tura klienta
    if (Msq::czyja_tura(&original_game_state) == 2) {

      while (client.receive(packet) == sf::Socket::Status::Partial) {
        // keep looping until it's sent
      }
      if (packet >> wybor_przeciwnika) {
        original_game_state.wybor = wybor_przeciwnika;
      }
      //--------------
      the_o_sp.setPosition({get_2D_index(original_game_state.wybor).x * 100.f,
                            get_2D_index(original_game_state.wybor).y * 100.f});
      sprites_to_draw.push_back(the_o_sp);
      Msq::make_move(&original_game_state);
    }
    //---------------
    _okno.clear(sf::Color::Green);
    _okno.draw(board_sp);
    for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end();
         itr++) // we loop over things to draw here
    {
      _okno.draw(*itr);
    }
    _okno.draw(debug_text);
    _okno.draw(zwyciezca_text);
    _okno.display();
    if (original_game_state.exit_flag == true) {
      winner_loop(_okno);
      return;
    }
  }
}
void network_loop_client(sf::RenderWindow &_okno) {
  // game loop initialization here
  std::vector<sf::Sprite> sprites_to_draw;
  sprites_to_draw.push_back(board_sp);
  _okno.clear();
  _okno.draw(board_sp);
  _okno.display();
  Msq::GameState original_game_state = {};
  sf::Text debug_text(font);
  debug_text.setFillColor(sf::Color::Red);
  debug_text.setStyle(sf::Text::Bold);
  debug_text.setPosition({20, 20});
  debug_text.setCharacterSize(24);
  // network
  sf::TcpSocket client;

  sf::Socket::Status status = client.connect(sf::IpAddress::LocalHost, 53000);
  if (status != sf::Socket::Status::Done) {
    // error...
    debug_text.setString("Nie udalo sie polaczyc :(");
  }
  sf::Packet packet;
  int wybor_przeciwnika;
  // init ends here
  while (_okno.isOpen()) {
    while (const std::optional _event = _okno.pollEvent()) // poll events
    {
      debug_text.setString(
          debug_string(original_game_state.tura, original_game_state.wybor));
      if (_event->is<sf::Event::Closed>())
      {
        _okno.close();
      } else if (_event->is<sf::Event::KeyPressed>()) {}
    }
    // klient robie ture
    if (Msq::czyja_tura(&original_game_state) == 2 ) {
      original_game_state.wybor = get_1D_index(relative_mouse_pos(_okno).x,
                                               relative_mouse_pos(_okno).y);
      if (Msq::is_valid_move(&original_game_state)) {

        packet << original_game_state.wybor;
        while (client.send(packet) != sf::Socket::Status::Done) {
          // until we succesfully send the packet we loop it
        }
        the_x_sp.setPosition(
            {get_2D_index(original_game_state.wybor).x * 100.f,
             get_2D_index(original_game_state.wybor).y * 100.f});
        sprites_to_draw.push_back(the_x_sp);
        Msq::make_move(&original_game_state);
      }
    }
    // draw_board(board);
  }

  // tura hosta
  if (Msq::czyja_tura(&original_game_state) == 1) {
    while (client.receive(packet) == sf::Socket::Status::Partial) {
      // keep looping until it's sent
    }
    if (packet >> wybor_przeciwnika) {
      original_game_state.wybor = wybor_przeciwnika;
    }
    //--------------
    the_o_sp.setPosition({get_2D_index(original_game_state.wybor).x * 100.f,
                          get_2D_index(original_game_state.wybor).y * 100.f});
    sprites_to_draw.push_back(the_o_sp);
    Msq::make_move(&original_game_state);
  }
  _okno.clear(sf::Color::Green);
  _okno.draw(board_sp);
  for (auto itr = sprites_to_draw.begin(); itr != sprites_to_draw.end();
       itr++) // we loop over things to draw here
  {
    _okno.draw(*itr);
  }
  _okno.draw(debug_text);
  _okno.draw(zwyciezca_text);
  _okno.display();
  if (original_game_state.exit_flag == true) {
    winner_loop(_okno);
    return;
  }
}
