#include "BuildingManager.hpp"

BuildingManager::BuildingManager()
{
	if(!initBuildings())
	{
		throw std::runtime_error("Building initialization failed.");
	}
}

bool BuildingManager::initBuildings()
{
	//Load the object_data json object.
	std::ifstream file("resource/objects/object_data.json");
	
	//Return false if the json was not loaded.
	if(!file)
	{
		return false;
	}
	
	//Load the json & close the file.
	nlohmann::json object_data;
	file >> object_data;
	file.close();
	
	//Init the material manager.
	mMaterials.initResources(object_data);
	
	//Get the base texture directory
	std::string texture_dir = "resource/objects/" + object_data.at("texturedir").get<std::string>();
	
	//Iterate through the list of buildings.
	for(nlohmann::json& obj : object_data.at("buildings").get<nlohmann::json>())
	{
		//Create a new building.
		Building b;
		b.name = obj.at("name").get<std::string>();
		b.texture.loadFromFile(texture_dir + obj.at("texture").get<std::string>());
		
		//Iterate through all price objects.
		for(nlohmann::json& price_obj : obj.at("price").get<nlohmann::json>())
		{
			//Create a new Resource object.
			MaterialManager::Resource r;
			r.name = price_obj.at("name").get<std::string>();
			r.count = price_obj.at("count").get<int>();
			//Add the new resource object to the building cost vector.
			b.price.push_back(r);
		}
	}
	
	//Return successful.
	return true;
}