//
// Created by Missqu on 1/23/25.
//

#ifndef NETWORKDATA_H
#define NETWORKDATA_H
#include <cstdint>
#include<SFML/Network.hpp>
struct NetworkData
{
  std::uint8_t turn;
  std::uint8_t wybor;
  std::uint8_t kto; //1- krzyzyk, 2-kolko
};

sf::Packet& operator<<(sf::Packet& packet, const NetworkData& data)
{
  return packet << data.turn << data.wybor << data.kto;
}

sf::Packet& operator>>(sf::Packet& packet, NetworkData& data)
{
  return packet >> data.turn >> data.wybor >> data.kto;
}

#endif //NETWORKDATA_H
