#pragma once

#include <SFML/Graphics.hpp>
#include <imgui-sfml/imgui-SFML.h>
#include <imgui/imgui.h>

#include "BuildingManager.hpp"
#include "KeyManager.hpp"
#include "Tilemap.hpp"

/**
 * @brief Base application class.
 *
 */
class Application {
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
	//////////////////CONSTANTS////////////////////
	const sf::Color BG_COLOR = sf::Color(100, 100, 255);
	///////////////////////////////////////////////

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
	 * @brief The main map.
	 *
	 */
	Tilemap mMap;

	/**
	 * @brief The main building manager.
	 *
	 */
	BuildingManager mBuilder;

	/**
	 * @brief Begin & End the main ImGui windows.
	 *
	 */
	void mUpdateGui();
};