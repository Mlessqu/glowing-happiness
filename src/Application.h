//
// Created by Missqu on 1/16/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include<SFML/Graphics.hpp>

#include "ResourceManager.h"
#include"StateMachine.h"

#include "EventHandle.h"

class Application {
public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application();
	void run();
private:
	sf::RenderWindow window_;
	StateMachine state_machine_;
	ResourceManager* resource_manager_;
	EventHandle* event_handle_;
};



#endif //APPLICATION_H
