#pragma once

#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

#include <vector>
#include <fstream>
#include <exception>

#include "MaterialManager.hpp"
#include "KeyManager.hpp"
#include "Tilemap.hpp"

/**
 * @brief Class that loads & stores building information, and
 * that updates GUI & states to allow for constructing buildings to the map.
 * 
 */
class BuildingManager : public sf::Drawable
{
public:
	/**
	 * @brief Default constructor.
	 * 
	 * @see initBuildings()
	 */
	BuildingManager(Tilemap* map);
	
	/**
	 * @brief Struct to store basic building data.
	 * 
	 */
	struct Building
	{
		std::string name;
		std::vector<MaterialManager::Resource> price;
		sf::Texture texture;
		std::string description;
	};
	
	/**
	 * @brief Placed building data.
	 * 
	 */
	struct BuildingEntityData
	{
		sf::Sprite spr;
		Building* building_data;
	};
	
	/**
	 * @brief Renders the necessary gui components.
	 * 
	 * @remarks REQUIRES ImGui::Begin() to have been called!
	 * @remarks CALL ImGui::End() AFTER.
	 * 
	 * @see ImGui::Begin()
	 */
	void renderGui();
	
	/**
	 * @brief Updates the actively placed buildings & their 
	 * 
	 */
	void update();
	
private:
	/**
	 * @brief SFML draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	/**
	 * @brief The internal material manager.
	 * 
	 */
	MaterialManager mMaterials;
	
	Tilemap* mMap;
	
	/**
	 * @brief The internal vector of buildings & their data.
	 * 
	 */
	std::vector<Building> mBuildings;
	
	std::vector<BuildingEntityData> mBuilt;
	
	/**
	 * @brief Initializes the material manager & the mBuildings vector.
	 * 
	 * @return true If successful. 
	 */
	bool initBuildings();
	
	bool mBuildMode;
	void placeBuilding(Building* building);
	void updateBuilding();
	void releaseBuilding();
	
	Building* mBuildingBuilding;
	sf::Sprite mBuildingSprite;
};