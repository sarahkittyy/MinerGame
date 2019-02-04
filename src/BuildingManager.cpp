#include "BuildingManager.hpp"

BuildingManager::BuildingManager(Tilemap* map)
{
	//Initialize defaults.
	mMap = map;
	mBuildMode = false;
	mTPS = 1;
	mGlobalClock.restart();
	
	//Attempt to initialize buildings...
	if(!initBuildings())
	{
		throw std::runtime_error("Building initialization failed.");
	}
	
	//Add starter materials.
	mMaterials.addResources({.name = "Cash", .count = 10});
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
	//Boolean used to check if nothing at all is hovered.
	bool hoveredThisFrame = false;
	//For every building...
	for(auto& i : mBuildings)
	{
		//Create a building button, and begin placing a building if pressed.
		if(ImGui::ImageButton(i.texture, 1))
		{
			placeBuilding(&i);
		}
		//If hovering the button...
		if(ImGui::IsItemHovered())
		{
			//Set the hovering flag & set the pointer to the hovered building.
			mBuildingButtonHovered = true;
			hoveredThisFrame = true;
			mBuildingHovered = &i;
		}
		ImGui::NextColumn();
	}
	//If not hovered at all...
	if(!hoveredThisFrame)
	{
		//..we're not hovering.
		mBuildingButtonHovered = false;
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
		
		float rpt = getResourcePerTick(i.first);
		
		//Add the name of it, and its count.
		ImGui::Text(std::string("%s - %d (%c%.1f)").c_str(),
					 i.first.c_str(), 
					 i.second, 
					 (rpt >= 0)?('+'):('-'),
					 std::abs(rpt));
		ImGui::NextColumn();
	}
}

void BuildingManager::renderGuiTooltip()
{
	/* PSUEDOCODE (?)
	
	Building Tooltip Info
		* Name
		* Icon
		* Description
		* Price
		* Resource I/O
	
	If in build mode:
		* Building tooltip.
		
	If building button hovered:
		*  Building tooltip.
	
	If nothing is selected:
		* TPS
		* Game Time Elapsed
	
	If building on map is highlighted:
		* Sell price.
		* Note: (Right click to sell)
		
	Extra Notes:
		* Sell price = 90% buy price.
	*/
	
	bool mapBuildingHovered = false;
	Building* mapBuildingHoveredBuilding = nullptr;
	//Check if building on map is hovered...
	for(auto &i : mBuilt)
	{
		//If the sprite contains the mouse's position...
		if(i.spr.getGlobalBounds().contains(
			(sf::Vector2f)KeyManager::getMousePos()
		))
		{
			//We're hovering, grab a pointer to the hovered building and break.
			mapBuildingHovered = true;
			mapBuildingHoveredBuilding = i.building_data;
			break;
		}
	}

	//Build mode check..
	if(mBuildMode)
	{
		renderGuiBuildingTooltip(*mBuildingBuilding);
	}
	else if(mBuildingButtonHovered) //Otherwise, if hovering over a button...
	{
		renderGuiBuildingTooltip(*mBuildingHovered);
	}
	else if(mapBuildingHovered) //If a building on the map is hovered..
	{
		renderGuiMapBuildingTooltip(*mapBuildingHoveredBuilding);
	}
	else //If neither...
	{
		//Render the TPS & the game time elapsed.
		ImGui::Text("Ticks/Second: %d\n---\n", mTPS);
		ImGui::Text("Time Elapsed: %d sec.", 
						(int)mGlobalClock.getElapsedTime().asSeconds());
	}
}

void BuildingManager::renderGuiBuildingTooltip(BuildingManager::Building& building)
{
	/*
	Building Tooltip info:
		* Name
		* Icon
		* Desc
		* Resource I/O
		* Price
	*/
	//Render the icon of the building.
	ImGui::Image(building.texture);
	
	//Render the name & building of the building.
	ImGui::Text("%s\n> %s\n---", building.name.c_str(), building.description.c_str());
	
	//Begin rendering the price..
	ImGui::Text("Cost:");
	//So for each element of the total cost..
	for(auto &i : building.price)
	{
		//Render the icon.
		ImGui::Image(*mMaterials.getTexture(i.name));
		//Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", i.count, i.name.c_str());
	}
	
	//Render the resource I/O..
	if(building.pertick.at("resource_in").size() != 0)
		ImGui::Text("Input/Tick:");
	//Get all necessary input resources.
	for(auto &i : building.pertick.at("resource_in"))
	{
		std::string name = i.at("name").get<std::string>();
		int count = i.at("count").get<int>();
		
		//Render the icon.
		ImGui::Image(*mMaterials.getTexture(name));
		//Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", count, name.c_str());
	}
	
	//Now for out I/O...
	if(building.pertick.at("resource_out").size() != 0)
		ImGui::Text("Output/Tick:");
	//Get all necessary output resources.
	for(auto &i : building.pertick.at("resource_out"))
	{
		std::string name = i.at("name").get<std::string>();
		int count = i.at("count").get<int>();
		
		//Render the icon.
		ImGui::Image(*mMaterials.getTexture(name));
		//Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", count, name.c_str());
	}
}

void BuildingManager::renderGuiMapBuildingTooltip(BuildingManager::Building& building)
{
	/*
	Selling Tooltip Info
		* Name
		* Icon
		* Description
		* Sell price.
		* Resource I/O
		* Note: Right click to sell.
	*/
	//Render the icon of the building.
	ImGui::Image(building.texture);
	
	//Render the name & building of the building.
	ImGui::Text("%s\n> %s\n---", building.name.c_str(), building.description.c_str());
	
	//Begin rendering the sell price.
	ImGui::Text("Sells for:");
	//So for each element of the total cost..
	for(auto &i : building.sellprice)
	{
		//Render the icon.
		ImGui::Image(*mMaterials.getTexture(i.name));
		//Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", i.count, i.name.c_str());
	}
	
	//Render the resource I/O..
	if(building.pertick.at("resource_in").size() != 0)
		ImGui::Text("Input/Tick:");
	//Get all necessary input resources.
	for(auto &i : building.pertick.at("resource_in"))
	{
		std::string name = i.at("name").get<std::string>();
		int count = i.at("count").get<int>();
		
		//Render the icon.
		ImGui::Image(*mMaterials.getTexture(name));
		//Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", count, name.c_str());
	}
	
	//Now for out I/O...
	if(building.pertick.at("resource_out").size() != 0)
		ImGui::Text("Output/Tick:");
	//Get all necessary output resources.
	for(auto &i : building.pertick.at("resource_out"))
	{
		std::string name = i.at("name").get<std::string>();
		int count = i.at("count").get<int>();
		
		//Render the icon.
		ImGui::Image(*mMaterials.getTexture(name));
		//Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", count, name.c_str());
	}
	
	//Inform the user they can right click to sell.
	ImGui::Text("-Sell with RMB-");
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
	
	//Check if hovering a building on the map.
	for(auto i = mBuilt.begin(); i != mBuilt.end(); )
	{
		//If the mouse is hovered over a building
		//& the right mouse button is released..
		if(i->spr.getGlobalBounds().contains(
			(sf::Vector2f)KeyManager::getMousePos())
			&& KeyManager::getRMouseState() == 2)
		{
			//Remove the building from the map.
			mBuilt.erase(i);
			
			//Return the sell price of the building.
			for(auto &j : i->building_data->sellprice)
			{
				mMaterials.addResources(j);
			}
			
			//Break.
			break;
		}
		else { ++i; }
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
					.name = obj.at("name").get<std::string>(),
					.count = obj.at("count").get<int>()
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
						.name = obj.at("name").get<std::string>(),
						.count = obj.at("count").get<int>()
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

float BuildingManager::getResourcePerTick(std::string resource)
{
	//Variables for how many gained & how many lost.
	float gained = 0, lost = 0;
	for(auto &i : mBuilt)
	{
		//Iterate over all input resources
		for(nlohmann::json &r_in : i.building_data->pertick.at("resource_in"))
		{
			//If it's name matches, add it's count to how much lost per tick.
			if(r_in.at("name").get<std::string>() == resource)
			{
				lost += r_in.at("count").get<int>();
			}
		}
		
		//Iterate over all output resources...
		for(nlohmann::json &r_out : i.building_data->pertick.at("resource_out"))
		{
			//If it's name matches, add its count to gained/tick.
			if(r_out.at("name").get<std::string>() == resource)
			{
				gained += r_out.at("count").get<int>();
			}
		}
	}
	
	//Return the final overall loss/gain.
	return gained-lost;
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
	
	//Check if left mouse is clicked.
	if(KeyManager::getLMouseState() == 1)
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
			
			//Check if we can purchase the building.
			bool purchaseable = true;
			for(auto &i : mBuildingBuilding->price)
			{
				if(!mMaterials.canPurchase({
					.name = i.name,
					.count = i.count
				}))
				{
					purchaseable = false;
					break;
				}
			}
			
			//If purchaseable...
			if(purchaseable)
			{
				//Purchase...
				for(auto &i : mBuildingBuilding->price)
				{
					mMaterials.purchase({
						.name = i.name,
						.count = i.count
					});
				}
				
				//Plant the building.
				BuildingEntityData b;
				b.building_data = mBuildingBuilding;
				b.spr.setTexture(mBuildingBuilding->texture);
				b.spr.setPosition(tile_pos);
				
				//..Why does this line error in vs code, but compile properly??
				mBuilt.push_back(b);
			}	
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
		//////BUILDING INITIALIZATION HAPPENS HERE////
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
		//Iterate the same as before, but with sellprice objects.
		for(nlohmann::json& sellprice_obj : obj.at("sellprice").get<nlohmann::json>())
		{
			//Create a new Resource object.
			MaterialManager::Resource r;
			r.name = sellprice_obj.at("name").get<std::string>();
			r.count = sellprice_obj.at("count").get<int>();
			//Add the new resource object to the building cost vector.
			b.sellprice.push_back(r);
		}
		
		b.pertick = obj.at("pertick");
		
		//Push the building into the internal vector.
		mBuildings.push_back(b);
	}
	
	//Return successful.
	return true;
}