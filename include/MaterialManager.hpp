#pragma once

#include <algorithm>
#include <map>
#include <queue>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "nlohmann/json.hpp"

/////////////TODO/////////////
// Multiple unordered maps,all sorted by the same type of key.
// Can/Will be refactored into one map.
//////////////////////////////

/**
 * @brief Standalone class to init, and track in-game resources.
 *
 */
class MaterialManager
{
public:
	/**
	 * @brief Default constructor.
	 *
	 */
	MaterialManager();

	/**
	 * @brief Struct to bind a resource with a count.
	 *
	 */
	struct Resource
	{
		std::string name;
		long count;
	};

	/**
	 * @brief Initialize the names of all resources.
	 *
	 * @param resources The json object for resource/objects/object_data.json
	 */
	void initResources(nlohmann::json &resources);

	/**
	 * @brief Set a specific resource to a specific amount.
	 *
	 * @param r The resource to set & its new count.
	 */
	void setResourceCount(Resource r);

	/**
	 * @brief Get the count of a specific resource.
	 *
	 * @param resource_name The name of the resource.
	 * @return int The amount in possession.
	 */
	int getResourceCount(std::string resource_name);

	/**
	 * @brief Add an amount to a specific resource.
	 *
	 * @param r.name The resource to modify.
	 * @param r.count The count of items to add to the resource.
	 */
	void addResources(Resource r);

	/**
	 * @brief Remove an amount from a specific resource.
	 *
	 * @param r.name The resource to modify.
	 * @param r.count The count of items to remove from the resource.
	 */
	void removeResources(Resource r);

	/**
	 * @brief Convert a json array to a vector of resource objects.
	 * 
	 * @param price A JSON array, formatted as a standard purchase cost.
	 * @return std::vector<Resource> A vector of the required resources.
	 */
	std::vector<Resource> priceToResourceVector(nlohmann::json::array_t price);

	/**
	 * @brief Checks if there are as many resources in storage as given.
	 *
	 * @param r The resource to check.
	 * @return true If those many resources exist.
	 */
	bool canPurchase(Resource r);

	/**
	 * @brief Checks if all the given resources are in storage.
	 * 
	 * @param r The resources to check.
	 * @return true If all the resources exist.
	 * @return false If the item is unpurchaseable.
	 */
	bool canPurchaseMultiple(std::vector<Resource> r);

	/**
	 * @brief Attempt to purchase an object from the resources required..
	 *
	 * @param r A resource to deduct from.
	 * @return true If the item is purchaseable, and was purchased.
	 * @return false If there are not enough resources in internal storage.
	 */
	bool purchase(Resource r);

	/**
	 * @brief Attempt to purchase an item of multiple resource costs.
	 * 
	 * @param r The resources to deduct from.
	 * @return true If the item was successfully purchased.
	 * @return false If there weren't enough resources to purchase the item.
	 */
	bool purchaseMultiple(std::vector<Resource> r);

	/**
	 * @brief Updates tick-by-tick resource statistics, such as average
	 * resource/tick.
	 *
	 * @remarks Call once per game tick.
	 *
	 */
	void updateResourceLogger();

	/**
	 * @brief Get the average resource gain/loss per tick.
	 *
	 * @param resource The resource to retrieve.
	 * @return float The amount gained/lost per tick.
	 */
	float getAverageResourcePerTick(std::string resource);

	/**
	 * @brief Retrieve a const reference to the resource map.
	 *
	 * @return const std::unordered_map<std::string, int>& A reference to the
	 * internal resources.
	 */
	const std::map<std::string, long> &getResources();

	/**
	 * @brief Get a pointer to the icon texture for the specified resource.
	 *
	 * @param resource The resource's texture to retrieve.
	 * @return sf::Texture* A pointer to the texture.
	 */
	sf::Texture *getTexture(std::string resource);

private:
	/**
	 * @brief Internal map of the name to the count of each resource.
	 *
	 */
	std::map<std::string, long> mResources;

	/**
	 * @brief Map of resources to their texture.
	 *
	 */
	std::unordered_map<std::string, sf::Texture> mIconTextures;

	/**
	 * @brief How many values back to log.
	 *
	 * @remarks The larger this is, the longer the display will take to reach an
	 * accurate value, but the more accurate that value will be. Perhaps a
	 * slider should be made?
	 *
	 */
	const unsigned LOG_QUEUE_SIZE = 5;

	/**
	 * @brief Logs resources for their previous values, to measure average
	 * change/tick.
	 *
	 */
	std::unordered_map<std::string, std::deque<float>> mResourceLog;
};