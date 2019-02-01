#pragma once

#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

/**
 * @brief Base application class.
 * 
 */
class Application
{
public:
	/**
	 * @brief Initializes all game objects.
	 * 
	 */
	Application();
	
	/**
	 * @brief Main game loop / logic handling.
	 * 
	 * @return int The exit code of the program.
	 */
	int run();
	
private:
	/**
	 * @brief The main SFML renderwindow.
	 * 
	 */
	sf::RenderWindow mWindow;
	
	/**
	 * @brief Clock for updating ImGui.
	 * 
	 */
	sf::Clock mImGuiClock;
	
	/**
	 * @brief Begin & End the main ImGui windows.
	 * 
	 */
	void mUpdateGui();
};