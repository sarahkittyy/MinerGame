#pragma once

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include <imgui-sfml/imgui-SFML.h>
#include <imgui/imgui.h>
#include <SFML/Graphics.hpp>

#include "BuildingManager.hpp"
#include "MaterialManager.hpp"

/**
 * @brief Provides a container for storing upgrade key-pair combos.
 * Upgrades are loaded from object_data.json.
 * Contains a method to render the icon buttons for upgrades, and call as necessary.
 * Contains a method to load upgrades from object_data.json
 * 
 * @remarks Functions passed by lambda expressions should be by-reference to modify the actual BuildingManager properties.
 * 
 */
class UpgradeManager
{
private:
	/**
	 * @brief Upgrade typedef for simplification.
	 * 
	 */
	typedef nlohmann::json::object_t Upgrade;

public:
	/**
	 * @brief Default constructor.
	 * 
	 * @param materials The internal BuildingManager reference for upgrading.
	 * 
	 */
	UpgradeManager(BuildingManager* buildingmgr);

	/**
	 * @brief Initializes all upgrades.
	 * 
	 * @param object_data resource/objects/object_data.json 
	 */
	void loadUpgradeData(nlohmann::json object_data);

	/**
	 * @brief Renders & updates the the upgrade buttons.
	 * 
	 */
	void renderGui();

	/**
	 * @brief Renders the tooltip. Call once per frame.
	 * 
	 * @return true If the tooltip needed to be rendered.
	 * @return false If the tooltip was not rendered.
	 * 
	 * @see Application::mUpdateGui()
	 */
	bool renderGuiTooltip();

private:
	/**
	 * @brief True if the tooltip is being rendered.
	 * 
	 */
	bool mRenderTooltip;

	/**
	 * @brief A pointer to the upgrade to render the tooltip for.
	 * 
	 */
	Upgrade* tooltipUpgrade;

	/**
	 * @brief Pointer to the global material manager.
	 * 
	 */
	MaterialManager* mMaterials;

	/**
	 * @brief Pointer to the global building manager.
	 * 
	 */
	BuildingManager* mBuilder;

	/**
	 * @brief Attempts to purchase and call the given upgrade.
	 * 
	 * @param upgrade The upgrade to attempt.
	 */
	void callUpgrade(Upgrade& upgrade);

	/**
	 * @brief A map of keys to their corresponding function.
	 * 
	 */
	std::unordered_map<std::string, std::function<void(nlohmann::json::array_t)>> mUpgradeMap;

	/**
	 * @brief A map of upgrade names to their button textures.
	 * 
	 */
	std::unordered_map<std::string, sf::Texture> mUpgradeTextures;

	/**
	 * @brief A vector of all upgrades.
	 * 
	 */
	std::vector<Upgrade> mUpgrades;

	/**
	 * @brief Returns the texture of the specified upgrade.
	 * 
	 * @param up The upgrade to retrieve.
	 * @return sf::Texture* The texture of it.
	 */
	sf::Texture* getUpgradeTexture(Upgrade& up);

	//////////////////////UPGRADES/////////////////////////

	/**
	 * @brief Initializes all upgrade lambdas/function objects.
	 * 
	 */
	void initUpgradeMap();
};