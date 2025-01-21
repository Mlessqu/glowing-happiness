//
// Created by Missqu on 1/21/25.
//

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include<SFML/Graphics.hpp>


class ResourceManager {
	public:
ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	sf::Texture& get_board() { return board_texture_;}
	sf::Texture& get_o()  { return  the_o_;}
	sf::Texture& get_x() { return  the_x_;}
	sf::Font& get_font() { return font_;}

	static ResourceManager& init()
	{
		if (instance_ == nullptr)
		{
			instance_ = new ResourceManager();
			return * instance_;
		}else
		{
			assert(instance_ != nullptr);
			return *instance_;
		}
	}
	static ResourceManager& get_instance()
    {
        return *instance_;
    }
private:
	ResourceManager();
	static ResourceManager* instance_;
	sf::Texture board_texture_;
	sf::Texture the_o_;
	sf::Texture the_x_;
	sf::Font font_;
};



#endif //RESOURCEMANAGER_H
