#pragma once

#include <unordered_map>
#include <initializer_list>

#include <SFML/Graphics.hpp>

#include "nlohmann/json.hpp"

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
		int count;
	};
	
	/**
	 * @brief Initialize the names of all resources.
	 * 
	 * @param resources The json object for resource/objects/object_data.json
	 */
	void initResources(nlohmann::json& resources);
	
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
	 * @brief Attempt to purchase an object from the list of resources required.
	 * 
	 * @param cost A list of resources to deduct from.
	 * @return true If the item is purchaseable, and was purchased.
	 * @return false If there are not enough resources in internal storage. 
	 */
	bool purchase(std::initializer_list<Resource> cost);
	
	/**
	 * @brief Retrieve a const reference to the resource map.
	 * 
	 * @return const std::unordered_map<std::string, int>& A reference to the internal resources.
	 */
	const std::unordered_map<std::string, int>& getResources();
	
	/**
	 * @brief Get a pointer to the icon texture for the specified resource.
	 * 
	 * @param resource The resource's texture to retrieve.
	 * @return sf::Texture* A pointer to the texture.
	 */
	sf::Texture* getTexture(std::string resource);

	
private:
	/**
	 * @brief Internal map of the name to the count of each resource.
	 * 
	 */
	std::unordered_map<std::string, int> mResources;
	
	/**
	 * @brief Map of resources to their texture.
	 * 
	 */
	std::unordered_map<std::string, sf::Texture> mIconTextures;
};