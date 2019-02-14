#pragma once
////////TODO///////
// Refactor ;-;
///////////////////
#include <imgui-sfml/imgui-SFML.h>
#include <imgui/imgui.h>
#include <SFML/Graphics.hpp>

#include <algorithm>
#include <exception>
#include <fstream>
#include <vector>

#include "KeyManager.hpp"
#include "MaterialManager.hpp"
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
	 * @brief Declare the upgrade manager as a friend class.
	 * 
	 */
	friend class UpgradeManager;

	/**
	 * @brief Default constructor.
	 *
	 * @see initBuildings()
	 */
	BuildingManager(Tilemap *map);

	/**
	 * @brief Simple typedef to make building usage easier.
	 *
	 */
	typedef nlohmann::json Building;

	/**
	 * @brief Placed building data.
	 *
	 */
	struct BuildingEntityData
	{
		sf::Sprite spr;
		Building *building_data;
	};

	/**
	 * @brief Get the main object data json object.
	 * 
	 * @return nlohmann::json& A reference to the loaded object_data.json.
	 */
	nlohmann::json &getObjectData();

	/**
	 * @brief Return the internal material manager.
	 * 
	 * @return MaterialManager* A pointer to the main game material manager.
	 */
	MaterialManager *getMaterialManager();

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
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

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
	 * @brief The whole object_data json file.
	 * 
	 */
	nlohmann::json mObjectData;

	/**
	 * @brief The ticks per second.
	 *
	 */
	float mTPS;

	/**
	 * @brief Internal reference to the tilemap, to retrieve tile properties.
	 *
	 */
	Tilemap *mMap;

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
	void renderGuiBuilding(Building &building, bool isHighlightedOnMap = false);

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
	 * @brief Returns a pointer to the building with the given name.
	 * 
	 * @return Building* 
	 */
	Building *getBuilding(std::string building_name);

	/**
	 * @brief Map of building names to their textures.
	 *
	 */
	std::unordered_map<std::string, sf::Texture> mBuildingTextures;

	/**
	 * @brief Get the texture of the given building.
	 *
	 * @param building_name The name of the building.
	 * @return sf::Texture* A pointer to the required texture.
	 */
	sf::Texture *getBuildingTexture(std::string building_name);

	/**
	 * @brief Get the texture of the given building.
	 *
	 * @param building The building.
	 * @return sf::Texture* A pointer to the building's texture.
	 */
	sf::Texture *getBuildingTexture(Building &building);

	/**
	 * @brief True if currently in "build mode" -- dragging tower for placement.
	 *
	 */
	bool mBuildMode;

	/**
	 * @brief Build mode's internal reference to the currently selected
	 * building.
	 *
	 */
	Building *mBuildingBuilding;

	/**
	 * @brief Enable buildmode & start moving the sprite.
	 *
	 * @param building
	 */
	void placeBuilding(Building *building);

	/**
	 * @brief Called by update(), updates the building sprite & places the
	 * building if necessary & in buildmode.
	 *
	 */
	void updateBuilding();

	/**
	 * @brief Releases the held building, ending build mode.
	 *
	 */
	void releaseBuilding();

	/**
	 * @brief The sprite rendered when dragging & dropping the building.
	 *
	 */
	sf::Sprite mBuildingSprite;

	/**
	 * @brief A rectangle rendered ontop of the map, to indicate placeable/unplaceable, and/or which tile is being hovered over.
	 * 
	 */
	sf::RectangleShape mHighlightRect;

	/**
	 * @brief A constant map of names to colors, for the different colors the
	 * map cursor can take on.
	 * 
	 */
	const std::unordered_map<std::string, sf::Color> HIGHLIGHT = {
		{"DEFAULT",
		 sf::Color(255, 255, 255, 130)},
		{"INVALID",
		 sf::Color(255, 65, 65, 130)}};

	/**
	 * @brief True if the HighlightRect should be drawn.
	 * 
	 */
	bool mDrawHighlight;

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
	Building *mBuildingHovered;
};