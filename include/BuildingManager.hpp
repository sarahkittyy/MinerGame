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
	
	/**
	 * @brief Internal reference to the tilemap, to retrieve tile properties.
	 * 
	 */
	Tilemap* mMap;
	
	/**
	 * @brief The internal vector of buildings & their data.
	 * 
	 */
	std::vector<Building> mBuildings;
	
	/**
	 * @brief Vector of placed building data, for the actual rendered buildings.
	 * 
	 */
	std::vector<BuildingEntityData> mBuilt;
	
	/**
	 * @brief Initializes the material manager & the mBuildings vector.
	 * 
	 * @return true If successful. 
	 */
	bool initBuildings();
	
	/**
	 * @brief True if currently in "build mode" -- dragging tower for placement.
	 * 
	 */
	bool mBuildMode;
	
	/**
	 * @brief Enable buildmode & start moving the sprite.
	 * 
	 * @param building 
	 */
	void placeBuilding(Building* building);
	
	/**
	 * @brief Called by update(), updates the building sprite & places the building if necessary & in buildmode.
	 * 
	 */
	void updateBuilding();
	
	/**
	 * @brief Releases the held building, ending build mode.
	 * 
	 */
	void releaseBuilding();
	
	/**
	 * @brief Build mode's internal reference to the currently selected building.
	 * 
	 */
	Building* mBuildingBuilding;
	
	/**
	 * @brief The sprite rendered when dragging & dropping the building.
	 * 
	 */
	sf::Sprite mBuildingSprite;
};