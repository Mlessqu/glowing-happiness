//
// Created by Missqu on 1/16/25.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include<SFML/Graphics.hpp>
#include"StateMachine.h"

class Application {
public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application();
	void run();
private:
	sf::RenderWindow window_;
	StateMachine state_machine_;
	void process_events();
	void update();
	void render();
};



#endif //APPLICATION_H
