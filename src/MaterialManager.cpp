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

void MaterialManager::setResourceCount(Resource r)
{
	//Set the new count of resources.
	mResources[r.name] = r.count;
}

int MaterialManager::getResourceCount(std::string resource_name)
{
	return mResources[resource_name];
}

void MaterialManager::addResources(Resource r)
{
	//Add the specified resource count.
	mResources[r.name] += r.count;
}

void MaterialManager::removeResources(Resource r)
{
	mResources[r.name] -= r.count;
}

bool MaterialManager::canPurchase(Resource r)
{
	//For every item..
	for(auto &i : r)
	{
		//If it's not purchaseable, return false.
		if(mResources[i.name] < i.count)
			return false;
	}
	
	//Return true.
	return true;
}

bool MaterialManager::purchase(Resource r)
{
	if(!canPurchase(r))
	{
		return false;
	}
	
	//We're still going, so now purchase all items.
	for(auto &i : r)
	{
		mResources[i.name] -= i.count;
	}
	
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