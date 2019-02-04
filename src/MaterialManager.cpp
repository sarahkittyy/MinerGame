#include "MaterialManager.hpp"

MaterialManager::MaterialManager()
{
	
}

void MaterialManager::initResources(nlohmann::json& objectdata)
{
	//For every object in the "resources" array...
	for(nlohmann::json& obj : objectdata.at("resources").get<nlohmann::json>())
	{
		//Get its name, and add it to the mResources map.
		std::string name = obj.at("name").get<std::string>();
		
		mResources[name] = 0;
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

bool MaterialManager::purchase(std::initializer_list<Resource> cost)
{
	//For every item..
	for(auto &i : cost)
	{
		//If it's not purchaseable, return false.
		if(mResources[i.name] < i.count)
			return false;
	}
	
	//We're still going, so now purchase all items.
	for(auto &i : cost)
	{
		mResources[i.name] -= i.count;
	}
	
	//We were successful.
	return true;
}