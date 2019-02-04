#include "BuildingManager.hpp"

BuildingManager::BuildingManager(Tilemap* map)
{
	mMap = map;
	mBuildMode = false;
	if(!initBuildings())
	{
		throw std::runtime_error("Building initialization failed.");
	}
}

void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//If attempting to place a building...
	if(mBuildMode)
	{
		//Draw the held building sprite.
		target.draw(mBuildingSprite, states);
	}
	
	//Draw all built buildings.
	for(auto &i : mBuilt)
	{
		target.draw(i.spr, states);
	}
}

void BuildingManager::renderGui()
{
	for(auto i : mBuildings)
	{
		if(ImGui::ImageButton(i.texture, 1))
		{
			placeBuilding(&i);
		}
		ImGui::NextColumn();
	}
}

void BuildingManager::update()
{
	//Update build mode.
	if(mBuildMode)
	{
		updateBuilding();
	}
}

void BuildingManager::placeBuilding(BuildingManager::Building* building)
{
	mBuildMode = true;
	mBuildingSprite.setTexture(building->texture);
	mBuildingBuilding = building;
}

void BuildingManager::updateBuilding()
{
	//Check for keys to indicate escaping building mode.
	if(KeyManager::getKeyState(sf::Keyboard::Escape))
	{
		releaseBuilding();
		return;
	}
	
	//If off the tilemap boundaries...
	if(	KeyManager::getMousePos().x > 400 || 
		KeyManager::getMousePos().x < 0 ||
		KeyManager::getMousePos().y > 400 ||
		KeyManager::getMousePos().y < 0)
	{
		//Return.
		return;
	}
	
	//Get the mouse's highlighted tile position.
	sf::Vector2f tile_pos = mMap->getTileInside((sf::Vector2f)KeyManager::getMousePos());
	
	//Place building sprite on the tile position.
	mBuildingSprite.setPosition(tile_pos);
	
	//Check if mouse is clicked.
	if(KeyManager::getMouseState())
	{	
		//Get the data for the tile we're currently on.
		nlohmann::json tiledata = mMap->getTileDataFor(mMap->getTileID(tile_pos));
		
		//If we're on land..
		if(tiledata.at("land").get<bool>())
		{
			//Plant the building.
			BuildingEntityData b;
			b.building_data = mBuildingBuilding;
			b.spr.setTexture(mBuildingBuilding->texture);
			b.spr.setPosition(tile_pos);
			mBuilt.push_back(b);
			
			//Release the building.
			releaseBuilding();
		}
	}
}

void BuildingManager::releaseBuilding()
{
	mBuildMode = false;
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
		b.description = obj.at("description").get<std::string>();
		
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
		
		//Push the building into the internal vector.
		mBuildings.push_back(b);
	}
	
	//Return successful.
	return true;
}