//
// Created by Missqu on 1/21/25.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include<SFML/Graphics.hpp>


class ResourceManager {
	public:
	static ResourceManager& get_instance();

	sf::Texture& get_board() { return board_texture_;}
	sf::Texture& get_o()  { return  the_o_;}
	sf::Texture& get_x() { return  the_x_;}
	sf::Font& get_font() { return font_;}

private:
	ResourceManager();
	static ResourceManager* instance_;
	sf::Texture board_texture_;
	sf::Texture the_o_;
	sf::Texture the_x_;
	sf::Font font_;
};



#endif //RESOURCEMANAGER_H
