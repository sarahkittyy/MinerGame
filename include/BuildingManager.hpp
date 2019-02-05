#pragma once
////////TODO///////
//Refactor ;-;
///////////////////
#include <SFML/Graphics.hpp>
#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

#include <vector>
#include <fstream>
#include <exception>

#include "MaterialManager.hpp"
#include "KeyManager.hpp"
#include "Tilemap.hpp"
#include "nlohmann/json.hpp"

/**
 * @brief Class that loads & stores building information, and
 * that updates GUI & states to allow for constructing buildings to the map.
 * 
 * @remarks I'm sorry.
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
		std::vector<MaterialManager::Resource> sellprice;
		sf::Texture texture;
		std::string description;
		nlohmann::json pertick;
		std::vector<std::string> canbuildon;
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
	void renderGuiBuildings();
	
	/**
	 * @brief Renders the resources to the active ImGui context.
	 * 
	 * @remarks CALL ImGui::Begin() BEFOREHAND.
	 * 
	 */
	void renderGuiResources();
	
	/**
	 * @brief Renders the tooltip for building information.
	 * 
	 */
	void renderGuiTooltip();
	
	/**
	 * @brief Updates the actively placed buildings & "build mode".
	 * 
	 * @remarks Counts ticks & updates resources/tick.
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
	 * @brief Internal clock to time the ticks per second.
	 * 
	 */
	sf::Clock mTickClock;
	
	/**
	 * @brief Clock that's never reset, logging the total game time elapsed.
	 * 
	 */
	sf::Clock mGlobalClock;
	
	/**
	 * @brief The ticks per second.
	 * 
	 */
	int mTPS;
	
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
	 * @brief Renders the tooltip for the given building to GUI.
	 * 
	 * @param building The building to render the tooltip for.
	 */
	void renderGuiBuildingTooltip(Building& building);
	
	/**
	 * @brief Renders the tooltip for a building on the map.
	 * 
	 * @param building The building to render the tooltip for.
	 * 
	 * @see renderGuiBuildingTooltip
	 */
	void renderGuiMapBuildingTooltip(Building& building);
	
	/**
	 * @brief Initializes the material manager & the mBuildings vector.
	 * 
	 * @return true If successful. 
	 */
	bool initBuildings();
	
	/**
	 * @brief Updates a single game tick.
	 * 
	 */
	void updateTick();
	
	/**
	 * @brief Returns the amount of buildings of the specified name are built.
	 * 
	 * @param building_name The name of the building.
	 * @return int The built count.
	 */
	int getBuildingCount(std::string building_name);
	
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
	
	/**
	 * @brief True if one of the buttons are being hovered over.
	 * 
	 * @remarks Updated in renderGuiBuildings().
	 * 
	 */
	bool mBuildingButtonHovered;
	
	/**
	 * @brief Pointer to the building being hovered over.
	 * 
	 */
	Building* mBuildingHovered;
};