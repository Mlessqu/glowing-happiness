//
// Created by Missqu on 1/21/25.
//

#include "ResourceManager.h"

#include <iostream>

ResourceManager::ResourceManager()
{
	//load textures
	if (!board_texture_.loadFromFile("board.png"))
	{
		std::cerr << "Error loading board texture" << std::endl;
	}
	if (!the_o_.loadFromFile("o.png"))
	{
		std::cerr << "Error loading the_o.png" << std::endl;
	}
	if (!the_x_.loadFromFile("x.png"))
	{
		std::cerr << "Error loading the_x.png" << std::endl;
	}
	//load font
	if (!font_.openFromFile("arial.ttf"))
	{
		std::cerr << "Error loading arial.ttf" << std::endl;
	}
}
ResourceManager* ResourceManager::instance_=nullptr;
ResourceManager &ResourceManager::get_instance()
{
	if (ResourceManager::instance_ == nullptr)
	{
		ResourceManager::instance_ = new ResourceManager();
	}
	return *ResourceManager::instance_;
}




