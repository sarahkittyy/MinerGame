#include "MaterialManager.hpp"

MaterialManager::MaterialManager()
{
	
}

void MaterialManager::initResources(nlohmann::json& objectdata)
{
	std::string texture_dir = "resource/objects/" + objectdata.at("texturedir").get<std::string>();
	
	//For every object in the "resources" array...
	for(nlohmann::json& obj : objectdata.at("resources").get<nlohmann::json>())
	{
		//Get its name, and add it to the mResources map.
		std::string name = obj.at("name").get<std::string>();
		
		mResources[name] = 0;
		
		//Init the icon texture directory.
		mIconTextures[name] = sf::Texture();
		mIconTextures[name].loadFromFile(texture_dir + obj.at("icon").get<std::string>());
	}
}

void MaterialManager::setResourceCount(MaterialManager::Resource r)
{
	//Set the new count of resources.
	mResources[r.name] = r.count;
}

int MaterialManager::getResourceCount(std::string resource_name)
{
	return mResources[resource_name];
}

void MaterialManager::addResources(MaterialManager::Resource r)
{
	//Add the specified resource count.
	mResources[r.name] += r.count;
}

void MaterialManager::removeResources(MaterialManager::Resource r)
{
	mResources[r.name] -= r.count;
}

bool MaterialManager::canPurchase(MaterialManager::Resource r)
{
	return mResources[r.name] >= r.count;
}

bool MaterialManager::purchase(MaterialManager::Resource r)
{
	if(!canPurchase(r))
	{
		return false;
	}
	
	//Purchase the item.
	mResources[r.name] -= r.count;
	
	//We were successful.
	return true;
}

const std::unordered_map<std::string, int>& MaterialManager::getResources()
{
	return mResources;
}

sf::Texture* MaterialManager::getTexture(std::string resource)
{
	//Assert the resource exists.
	auto found = mIconTextures.find(resource);
	if(found == mIconTextures.end())
	{
		throw std::out_of_range("Resource " + resource + " not found.");
	}
	
	//Return the texture.
	return &(found->second);
}