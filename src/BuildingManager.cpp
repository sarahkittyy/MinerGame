#include "BuildingManager.hpp"

BuildingManager::BuildingManager(Tilemap *map)
{
	// Initialize defaults.
	mMap	   = map;
	mBuildMode = false;
	mTPS	   = 1;
	mGlobalClock.restart();

	// Attempt to initialize buildings...
	if (!initBuildings())
	{
		throw std::runtime_error("Building initialization failed.");
	}

	//Init the highlight rectangle.
	mHighlightRect.setSize(mMap->getTileSize());
	mDrawHighlight = false;

	// Add starter materials.
	mMaterials.addResources({.name = "Cash", .count = 10});
}

void BuildingManager::draw(sf::RenderTarget &target,
						   sf::RenderStates states) const
{
	// Draw all built buildings.
	for (auto &i : mBuilt)
	{
		target.draw(i.spr, states);
	}

	// If attempting to place a building...
	if (mBuildMode)
	{
		// Draw the held building sprite.
		target.draw(mBuildingSprite, states);
	}
	//If the highlight should be drawn, draw it.
	if (mDrawHighlight)
	{
		target.draw(mHighlightRect, states);
	}
}

nlohmann::json &BuildingManager::getObjectData()
{
	return mObjectData;
}

MaterialManager *BuildingManager::getMaterialManager()
{
	return &mMaterials;
}

void BuildingManager::renderGuiBuildings()
{
	// Boolean used to check if nothing at all is hovered.
	bool hoveredThisFrame = false;
	// For every building...
	for (auto &i : mBuildings)
	{
		// Create a building button, and begin placing a building if pressed.
		if (ImGui::ImageButton(*getBuildingTexture(i), 1))
		{
			placeBuilding(&i);
		}
		// If hovering the button...
		if (ImGui::IsItemHovered())
		{
			// Set the hovering flag & set the pointer to the hovered building.
			mBuildingButtonHovered = true;
			hoveredThisFrame	   = true;
			mBuildingHovered	   = &i;
		}
		ImGui::NextColumn();
	}
	// If not hovered at all...
	if (!hoveredThisFrame)
	{
		//..we're not hovering.
		mBuildingButtonHovered = false;
	}
}

void BuildingManager::renderGuiResources()
{
	// For every resource...
	for (auto &i : mMaterials.getResources())
	{
		// Add an image for it.
		ImGui::Image(*mMaterials.getTexture(i.first));
		ImGui::NextColumn();

		float rpt = mMaterials.getAverageResourcePerTick(i.first);

		// Add the name of it...
		ImGui::Text("%s",
					i.first.c_str());

		ImGui::NextColumn();

		ImGui::Text("-");
		ImGui::NextColumn();

		//And then the count & rpt.
		ImGui::Text("%d",
					i.second);

		ImGui::SameLine();

		ImGui::Text("(%c%.2f/T)",
					(rpt >= 0) ? ('+') : ('-'),
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

	bool mapBuildingHovered				 = false;
	Building *mapBuildingHoveredBuilding = nullptr;
	// Check if building on map is hovered...
	for (auto &i : mBuilt)
	{
		// If the sprite contains the mouse's position...
		if (i.spr.getGlobalBounds().contains(
				(sf::Vector2f)KeyManager::getMousePos()))
		{
			// We're hovering, grab a pointer to the hovered building and break.
			mapBuildingHovered		   = true;
			mapBuildingHoveredBuilding = i.building_data;
			break;
		}
	}

	// Build mode check..
	if (mBuildMode)
	{
		renderGuiBuilding(*mBuildingBuilding);
	}
	else if (mBuildingButtonHovered)   // Otherwise, if hovering over a button...
	{
		renderGuiBuilding(*mBuildingHovered);
	}
	else if (mapBuildingHovered)   // If a building on the map is hovered..
	{
		renderGuiBuilding(*mapBuildingHoveredBuilding, true);
	}
	else   // If neither...
	{
		// Render the TPS & the game time elapsed.
		ImGui::Text("Ticks/Second: %.2f\n---\n", mTPS);
		ImGui::Text("Time Elapsed: %d sec.",
					(int)mGlobalClock.getElapsedTime().asSeconds());
	}
}

void BuildingManager::renderGuiBuilding(BuildingManager::Building &building,
										bool isHighlightedOnMap)
{
	/*
	Building Tooltip info:
			* Name
			* Icon
			* Desc
			* Resource I/O
			* Price
	*/
	// Render the icon of the building.
	ImGui::Image(*getBuildingTexture(building));
	// Render how many are currently on-screen.
	ImGui::SameLine();
	ImGui::Text("Count: %d",
				getBuildingCount(building.at("name").get<std::string>()));

	// Render the name & building of the building.
	ImGui::Text("%s\n> %s\n---",
				building.at("name").get<std::string>().c_str(),
				building.at("description").get<std::string>().c_str());

	// If configured to render the sell price...
	if (isHighlightedOnMap)
	{
		// Begin rendering the sell price.
		ImGui::Text("Sells for:");
		// So for each element of the total cost..
		for (auto &i : building.at("sellprice"))
		{
			// Render the icon.
			ImGui::Image(
				*mMaterials.getTexture(i.at("name").get<std::string>()));
			// Render the name & count
			ImGui::SameLine();
			ImGui::Text("%d %s",
						i.at("count").get<int>(),
						i.at("name").get<std::string>().c_str());
		}
	}
	// Otherwise...
	else
	{
		// Render the cost.
		ImGui::Text("Cost:");
		// So for each element of the total cost..
		for (auto &i : building.at("price"))
		{
			// Render the icon.
			ImGui::Image(
				*mMaterials.getTexture(i.at("name").get<std::string>()));
			// Render the name & count
			ImGui::SameLine();
			ImGui::Text("%d %s",
						i.at("count").get<int>(),
						i.at("name").get<std::string>().c_str());
		}
	}

	// Render the resource I/O..
	if (building.at("pertick").at("resource_in").size() != 0)
		ImGui::Text("Input/Tick:");
	// Get all necessary input resources.
	for (auto &i : building.at("pertick").at("resource_in"))
	{
		std::string name = i.at("name").get<std::string>();
		int count		 = i.at("count").get<int>();

		// Render the icon.
		ImGui::Image(*mMaterials.getTexture(name));
		// Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", count, name.c_str());
	}

	// Now for out I/O...
	if (building.at("pertick").at("resource_out").size() != 0)
		ImGui::Text("Output/Tick:");
	// Get all necessary output resources.
	for (auto &i : building.at("pertick").at("resource_out"))
	{
		std::string name = i.at("name").get<std::string>();
		int count		 = i.at("count").get<int>();

		// Render the icon.
		ImGui::Image(*mMaterials.getTexture(name));
		// Render the name & count
		ImGui::SameLine();
		ImGui::Text("%d %s", count, name.c_str());
	}

	// Render what it's placeable on.
	if (!isHighlightedOnMap)
	{
		ImGui::Text("Can place on:");

		// For every placeable tile...
		for (auto &i :
			 building.at("canbuildon").get<std::vector<std::string>>())
		{
			// Render its icon.
			ImGui::Image(mMap->getTileMapTexture(),
						 mMap->getTileTextureRect(i));

			// Render the name.
			ImGui::SameLine();
			ImGui::Text("%s", i.c_str());
		}
	}
}

void BuildingManager::update()
{
	// Update build mode.
	updateBuilding();

	// If ready to update a tick...
	if (mTickClock.getElapsedTime() > sf::seconds(1.0f / mTPS))
	{
		// Update the tick.
		updateTick();

		mTickClock.restart();
	}

	// Check if hovering a building on the map.
	for (auto i = mBuilt.begin(); i != mBuilt.end();)
	{
		// If the mouse is hovered over a building
		//& the right mouse button is released..
		if (i->spr.getGlobalBounds().contains(
				(sf::Vector2f)KeyManager::getMousePos()) &&
			KeyManager::getRMouseState() == 1)
		{
			// Remove the building from the map.
			mBuilt.erase(i);

			// Return the sell price of the building.
			for (auto &j : i->building_data->at("sellprice"))
			{
				mMaterials.addResources(
					{.name  = j.at("name").get<std::string>(),
					 .count = j.at("count").get<int>()});
			}

			// Break.
			break;
		}
		else
		{
			++i;
		}
	}
}

void BuildingManager::updateTick()
{
	// Update the per-tick MaterialManager resource logger.
	mMaterials.updateResourceLogger();

	// For every built building...
	for (auto &i : mBuilt)
	{
		// Get the pertick data.
		nlohmann::json pertick = i.building_data->at("pertick");

		// Get the resources per tick in & out.
		nlohmann::json rpt_in  = pertick.at("resource_in");
		nlohmann::json rpt_out = pertick.at("resource_out");

		bool purchaseable = true;
		// Check to make sure the per-tick cost in can be paid.
		for (auto &obj : rpt_in)
		{
			// Break if unpurchaseable.
			if (!mMaterials.canPurchase(
					{.name  = obj.at("name").get<std::string>(),
					 .count = obj.at("count").get<int>()}))
			{
				purchaseable = false;
				break;
			}
		}

		// If the item is still purcheaseable...
		if (purchaseable)
		{
			// Purchase it.
			for (auto &obj : rpt_in)
			{
				mMaterials.purchase({.name  = obj.at("name").get<std::string>(),
									 .count = obj.at("count").get<int>()});
			}

			// Get the amount of resources needed.
			for (auto &obj : rpt_out)
			{
				mMaterials.addResources(
					{.name  = obj.at("name").get<std::string>(),
					 .count = obj.at("count").get<int>()});
			}
		}
	}
}

int BuildingManager::getBuildingCount(std::string building_name)
{
	// Return var (count).
	int ret = 0;

	// For every built structure...
	for (auto &i : mBuilt)
	{
		// If the names match...
		if (i.building_data->at("name").get<std::string>() == building_name)
		{
			// Increment ret;
			ret++;
		}
	}

	// Return.
	return ret;
}

BuildingManager::Building *BuildingManager::getBuilding(std::string building_name)
{
	for (int i = 0; i < mBuildings; ++i)
	{
		Building *b = &mBuildings[i];
		if (b->at("name").get<std::string>() == building_name)
		{
			//
			return b;
		}
	}
	return nullptr;
}

void BuildingManager::placeBuilding(BuildingManager::Building *building)
{
	mBuildMode = true;
	mBuildingSprite.setTexture(*getBuildingTexture(*building));
	mBuildingBuilding = building;
}

void BuildingManager::updateBuilding()
{
	bool mouseInBounds = true;
	// If off the tilemap boundaries...
	if (KeyManager::getMousePos().x > 800 || KeyManager::getMousePos().x < 0 ||
		KeyManager::getMousePos().y > 560 || KeyManager::getMousePos().y < 0)
	{
		mouseInBounds = false;
	}

	//Toggle highlight drawing.
	mDrawHighlight = true;

	// Check for keys to indicate escaping building mode.
	if (KeyManager::getKeyState(sf::Keyboard::Escape))
	{
		releaseBuilding();
		return;
	}

	// Get the mouse's highlighted tile position.
	sf::Vector2f tile_pos =
		mMap->getTileInside((sf::Vector2f)KeyManager::getMousePos());

	// Get the data for the tile we're currently on.
	nlohmann::json tiledata =
		mMap->getTileDataFor(mMap->getTileID(tile_pos));

	// Place building sprite on the tile position.
	mBuildingSprite.setPosition(tile_pos);
	mHighlightRect.setPosition(tile_pos);

	mHighlightRect.setFillColor(HIGHLIGHT.at("DEFAULT"));

	//If not in build mode, return.
	if (!mBuildMode || !mouseInBounds)
	{
		return;
	}

	// Check if we can purchase the building.////////
	bool purchaseable = true;
	for (auto &i : mBuildingBuilding->at("price"))
	{
		if (!mMaterials.canPurchase(
				{.name  = i.at("name").get<std::string>(),
				 .count = i.at("count").get<int>()}))
		{
			purchaseable = false;
			break;
		}
	}
	//Check if we can place the building/////////////
	bool placeable = false;

	// Release & return if we cannot place on this tile.
	for (auto &i : mBuildingBuilding->at("canbuildon")
					   .get<std::vector<std::string>>())
	{
		// Get the tile's name.
		std::string tile_name = tiledata.at("name").get<std::string>();

		// If the name matches the tile, the tile is placeable.
		if (tile_name == i)
		{
			placeable = true;
			break;
		}
	}
	// Assert the building's position is not taken up.
	for (auto &i : mBuilt)
	{
		// If it is..
		if (i.spr.getGlobalBounds().contains(tile_pos))
		{
			//it's not placeable..
			placeable = false;
			break;
		}
	}

	// If not purchaseable, or not placeable...
	if (!purchaseable || !placeable)
	{
		//Highlight the tile red...
		mHighlightRect.setFillColor(HIGHLIGHT.at("INVALID"));
	}

	// Check if left mouse is clicked.
	if (KeyManager::getLMouseState() == 1)
	{
		//If we're not in bounds...
		if (!mouseInBounds)
		{
			//Release & return.
			releaseBuilding();
			return;
		}   //THIS CHECK MAY BE REDUNDANT, BUT I GOT SCARED SO I LEFT IT HERE

		//If we can't place the building...
		if (!placeable)
		{
			// Release & return.
			releaseBuilding();
			return;
		}

		// If purchaseable...
		if (purchaseable)
		{
			// Purchase...
			for (auto &i : mBuildingBuilding->at("price"))
			{
				mMaterials.purchase({.name  = i.at("name").get<std::string>(),
									 .count = i.at("count").get<int>()});
			}

			// Plant the building.
			BuildingEntityData b;
			b.building_data = mBuildingBuilding;
			b.spr.setTexture(*getBuildingTexture(*mBuildingBuilding));
			b.spr.setPosition(tile_pos);

			//..Why does this line error in vs code, but compile properly??
			mBuilt.push_back(b);
		}

		// Release the building.
		releaseBuilding();
	}
}

void BuildingManager::releaseBuilding()
{
	if (KeyManager::getKeyState(sf::Keyboard::LShift) == 0)
		mBuildMode = false;
}

bool BuildingManager::initBuildings()
{
	// Load the object_data json object.
	std::ifstream file("resource/objects/object_data.json");

	// Return false if the json was not loaded.
	if (!file)
	{
		return false;
	}

	// Load the json & close the file.
	nlohmann::json object_data;
	file >> object_data;
	file.close();

	//Copy the data internally, to use later.
	mObjectData = object_data;

	// Init the material manager.
	mMaterials.initResources(object_data);

	// Get the base texture directory
	std::string texture_dir =
		"resource/objects/" + object_data.at("texturedir").get<std::string>();

	// Iterate through the list of buildings.
	for (nlohmann::json &obj :
		 object_data.at("buildings").get<nlohmann::json>())
	{
		// Push the building into the internal vector.
		std::string tex = texture_dir + obj.at("texture").get<std::string>();

		obj["texture"] = tex;

		mBuildings.push_back(obj);

		mBuildingTextures[obj.at("name").get<std::string>()].loadFromFile(tex);
	}

	// Return successful.
	return true;
}

sf::Texture *BuildingManager::getBuildingTexture(std::string building_name)
{
	// Search for the texture...
	auto found = std::find_if(
		mBuildings.begin(), mBuildings.end(), [&](Building &b) -> bool {
			return b.at("name").get<std::string>() == building_name;
		});

	// Throw if not found.
	if (found == mBuildings.end())
	{
		throw std::out_of_range("getBuildingTexture() -- building not found.");
	}

	// Return the building texture.
	return &mBuildingTextures[found->at("name").get<std::string>()];
}

sf::Texture *
BuildingManager::getBuildingTexture(BuildingManager::Building &building)
{
	// Get the name & return the corresponding texture.
	std::string name = building.at("name").get<std::string>();

	return &mBuildingTextures[name];
}