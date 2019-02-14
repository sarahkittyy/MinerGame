#pragma once

#include <imgui-sfml/imgui-SFML.h>
#include <imgui/imgui.h>
#include <SFML/Graphics.hpp>

#include "BuildingManager.hpp"
#include "KeyManager.hpp"
#include "MaterialManager.hpp"
#include "Tilemap.hpp"
#include "UpgradeManager.hpp"

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
	//////////////////CONSTANTS////////////////////
	const sf::Color BG_COLOR = sf::Color(100, 100, 255);

	const sf::Vector2i WINDOW_SIZE = {840, 680};
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
	 * @brief The main upgrade manager.
	 * 
	 */
	UpgradeManager mUpgrades;

	/**
	 * @brief Begin & End the main ImGui windows.
	 *
	 */
	void mUpdateGui();
};