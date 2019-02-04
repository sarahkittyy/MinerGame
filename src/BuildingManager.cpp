#include "BuildingManager.hpp"

BuildingManager::BuildingManager(Tilemap* map)
{
	//Initialize defaults.
	mMap = map;
	mBuildMode = false;
	mTPS = 1;
	
	mMaterials.addResources({.name = "Cash", .count = 10});
	
	//Attempt to initialize buildings...
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

void BuildingManager::renderGuiBuildings()
{
	//For every building...
	for(auto& i : mBuildings)
	{
		//Create a building button, and begin placing a building if pressed.
		if(ImGui::ImageButton(i.texture, 1))
		{
			placeBuilding(&i);
		}
		ImGui::NextColumn();
	}
}

void BuildingManager::renderGuiResources()
{
	//For every resource...
	for(auto &i : mMaterials.getResources())
	{
		//Add an image for it.
		ImGui::Image(*mMaterials.getTexture(i.first));
		ImGui::NextColumn();
		
		//Add the name of it, and its count.
		ImGui::Text(std::string("%s - %d").c_str(), i.first.c_str(), i.second);
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
	//If ready to update a tick...	
	if(mTickClock.getElapsedTime() > sf::seconds(1.0f/mTPS))
	{
		//Update the tick.
		updateTick();
		
		mTickClock.restart();
	}
}

void BuildingManager::updateTick()
{
	//For every built building...
	for(auto &i : mBuilt)
	{
		//Get the pertick data.
		nlohmann::json pertick = i.building_data->pertick;
		
		//Get the resources per tick in & out.
		nlohmann::json rpt_in = pertick.at("resource_in");
		nlohmann::json rpt_out = pertick.at("resource_out");
		
		bool purchaseable = true;
		//Check to make sure the per-tick cost in can be paid.
		for(auto& obj : rpt_in)
		{
			//Break if unpurchaseable.
			if(!mMaterials.canPurchase({
				{
					.name = obj.at("name").get<std::string>(),
					.count = obj.at("count").get<int>()
				}
			}))
			{
				purchaseable = false;
				break;
			}
		}
		
		//If the item is still purcheaseable...
		if(purchaseable)
		{
			//Purchase it.
			for(auto& obj : rpt_in)
			{
				mMaterials.purchase({
					{
						.name = obj.at("name").get<std::string>(),
						.count = obj.at("count").get<int>()
					}
				});
			}
			
			//Get the amount of resources needed.
			for(auto& obj: rpt_out)
			{
				mMaterials.addResources({
					.name = obj.at("name").get<std::string>(),
					.count = obj.at("count").get<int>()
				});
			}
		}
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
	
	//Get the mouse's highlighted tile position.
	sf::Vector2f tile_pos = mMap->getTileInside((sf::Vector2f)KeyManager::getMousePos());
	
	//Place building sprite on the tile position.
	mBuildingSprite.setPosition(tile_pos);
	
	//If off the tilemap boundaries...
	if(	KeyManager::getMousePos().x > 400 || 
		KeyManager::getMousePos().x < 0 ||
		KeyManager::getMousePos().y > 400 ||
		KeyManager::getMousePos().y < 0)
	{
		//Return.
		return;
	}
	
	//Check if mouse is clicked.
	if(KeyManager::getMouseState() == 1)
	{	
		//Get the data for the tile we're currently on.
		nlohmann::json tiledata = mMap->getTileDataFor(mMap->getTileID(tile_pos));
		
		//If we're on land..
		if(tiledata.at("land").get<bool>())
		{
			//Assert the building's position is not taken up.
			for(auto &i : mBuilt)
			{
				//If it is..
				if(i.spr.getGlobalBounds().contains(tile_pos))
				{
					//Release & return.
					releaseBuilding();
					return;
				}
			}
			
			//Plant the building.
			BuildingEntityData b;
			b.building_data = mBuildingBuilding;
			b.spr.setTexture(mBuildingBuilding->texture);
			b.spr.setPosition(tile_pos);
			
			//..Why does this line error in vs code, but compile properly??
			mBuilt.push_back(b);
		}
		//Release the building.
		releaseBuilding();
	}
}

void BuildingManager::releaseBuilding()
{
	if(KeyManager::getKeyState(sf::Keyboard::LShift) == 0)
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
		
		b.pertick = obj.at("pertick");
		
		//Push the building into the internal vector.
		mBuildings.push_back(b);
	}
	
	//Return successful.
	return true;
}