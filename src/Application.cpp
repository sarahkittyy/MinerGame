#include "Application.hpp"

Application::Application() :
	mWindow(sf::VideoMode(600,600), "Miner")
{
	mWindow.setFramerateLimit(60);
}

int Application::run()
{
	while(mWindow.isOpen())
	{
		sf::Event event;
		while(mWindow.pollEvent(event))
		{
			ImGui
		}
	}
}