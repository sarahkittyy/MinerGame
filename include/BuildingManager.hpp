#pragma once

#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

#include <vector>
#include <fstream>
#include <exception>

#include "MaterialManager.hpp"

/**
 * @brief Class that loads & stores building information, and
 * that updates GUI & states to allow for constructing buildings to the map.
 * 
 */
class BuildingManager
{
public:
	BuildingManager();
	
	struct Building
	{
		std::string name;
		std::vector<MaterialManager::Resource> price;
		sf::Texture texture;
	};
	
private:
	
	/**
	 * @brief The internal material manager.
	 * 
	 */
	MaterialManager mMaterials;
	
	std::vector<Building> mBuildings;
	
	bool initBuildings();
};