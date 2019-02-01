#include "Tilemap.h"

Tilemap::Tilemap()
{
	//Set the vertices primitive type.
	mVertices.setPrimitiveType(sf::Quads);

	//Initialize "True" defaults, if no defaults json file is specified.
	mDefaults.collideable = true;
	mDefaults.bounds = sf::FloatRect{
		0,0,32,32
	};
}

void Tilemap::draw(	sf::RenderTarget& target,
					sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &mMapTexture;
	target.draw(mVertices, states);
}

bool Tilemap::loadFromID(int id)
{
	//Get the digits in the file name.
	int digits = (int)std::log10(id) + 1;
	
	//Limit of 999 maps.
	if(digits > 3)
	{
		//Invalid ID.
		return false;
	}

	//Prepend `3-digits` zeroes to the front of the ID.
	std::string fname = std::to_string(digits); 
	fname = std::string(3 - digits, '0') + fname;



	//Load the actual tilemap data itself.
	std::ifstream ifile("resource/maps/" + fname + "_Data.json");
	
	//Assert it loaded properly.
	if(!ifile)
	{
		return false;
	}

	//load the json data.
	nlohmann::json graphicaldata;
	ifile >> graphicaldata;

	ifile.close();
	//Open the individual tile data.
	ifile.open("resource/maps/" + fname + ".json");

	//Assert it loaded properly.
	if(!ifile)
	{
		return false;
	}

	//Load the json data (again).
	nlohmann::json tiledata;
	ifile >> tiledata;

	//Initialize all data.
	if(!getGraphicalData(graphicaldata))
	{
		return false;
	}
	if(!getTileData(tiledata))
	{
		return false;
	}

	//Init the vertices, & return the final success code.
	return updateVertices();
}

bool Tilemap::getGraphicalData(nlohmann::json& graphicaldata)
{
	/*
	Data to retrieve:
		- Tile array. (int[])
		- Texture image file name (std::string).
		- Tile width & height (sf::Vector2i).
		- Grid width & height (sf::Vector2i).
	*/

	//Retrieve the grid dimensions.
	int grid_width = graphicaldata["width"];
	int grid_height = graphicaldata["height"];
	mGridDimensions = {grid_width, grid_height};

	//Retrieve the tile dimensions.
	int tile_width = graphicaldata["tilewidth"];
	int tile_height = graphicaldata["tileheight"];
	mTileDimensions = {tile_width, tile_height};

	//Retrieve the tile array.
	mTiles = graphicaldata["layers"][0]["data"].get<std::vector<int>>();

	//Load the texture.
	mMapTexture.loadFromFile(
		"resource/maps/" + 
		graphicaldata["tilesets"][0]["image"].get<std::string>()
	);

	//Load successful.
	return true;
}

bool Tilemap::getTileData(nlohmann::json& tiledata)
{
	/*
	Data to retrieve:
		- Tile ID info ("defaults", "0", "1", "2".. etc.)
			- Collideable (bool)
			- Boundaries (float[4] (sf::FloatRect format))
	*/

	//Get default tile data.//
	nlohmann::json default_data = tiledata["defaults"];

	mDefaults.collideable = default_data["collideable"].get<bool>();

	nlohmann::json bounds_array = default_data["bounds"];
	mDefaults.bounds = sf::FloatRect(
		bounds_array[0],
		bounds_array[1],
		bounds_array[2],
		bounds_array[3]
	);
	///////////////////////////

	//If there's no individual tile data, return successful.
	if(tiledata.find("tiles") == tiledata.end())
	{
		return true;
	}

	//Iterate through all tiles objects now.
	for(auto& it : tiledata["tiles"].items())
	{
		//Get the tile id.
		int tile_id = std::stoi(it.key());

		//Get a reference to the json object.
		nlohmann::json& data = it.value();
		
		//Check for the collideable tag.
		auto collideableFound = data.find("collideable");

		bool collideable = mDefaults.collideable;

		if(collideableFound != data.end())
		{
			collideable = collideableFound->get<bool>();
		}

		//Check for the boundaries.
		auto boundsFound = data.find("bounds");

		sf::FloatRect bounds = mDefaults.bounds;

		if(boundsFound != data.end())
		{
			//Get the four values of the boundaries.
			std::vector<int> vals = boundsFound->get<std::vector<int>>();

			//Set bounds to the newly found bounds.
			bounds = sf::FloatRect{
				(float)vals[0],
				(float)vals[1],
				(float)vals[2],
				(float)vals[3]
			};
		}

		//Append final values to the mTileData map.
		mTileData[tile_id] = TileData{
			.collideable = collideable,
			.bounds = bounds
		};
	}

	//Return successful.
	return true;
}

bool Tilemap::updateVertices()
{
	//Clear any previous vertices.
	mVertices.clear();

	//Get the texture boundaries.
	sf::Vector2i texSize = (sf::Vector2i)mMapTexture.getSize();

	//Get the texture grid size.
	sf::Vector2i texGridSize = {
		texSize.x / mTileDimensions.x,
		texSize.y / mTileDimensions.y
	};

	//Iterate through all tiles.
	for(unsigned i = 0; i < mTiles.size(); ++i)
	{
		//Ignore 0 (air) tiles.
		if(mTiles[i] == 0) { continue; }

		//Decrement, because 0 is now not air, but the first non-air tile.
		int tile = mTiles[i] - 1;

		//Get the top_left position in the texture of the
		//needed tile.
		sf::Vector2f tex_pos = {
			(float)(mTileDimensions.x * (tile % texGridSize.x)),
			(float)(mTileDimensions.y * (tile / texGridSize.x))
		};

		//Get the top left position of the tile.
		sf::Vector2f tile_pos = {
			(float)mTileDimensions.x * (i % mGridDimensions.x),
			(float)mTileDimensions.y * (i / mGridDimensions.x)
		};

		sf::Vector2f width = {(float)mTileDimensions.x, 0};
		sf::Vector2f height = {0, (float)mTileDimensions.y};

		//Append the vertices.
		sf::Vertex vertices[4] = {
			sf::Vertex(tile_pos, tex_pos),
			sf::Vertex(tile_pos + width, tex_pos + width),
			sf::Vertex(	tile_pos + width + height, 
						tex_pos + width + height),
			sf::Vertex(tile_pos + height, tex_pos + height)
		};
		
		//Append the quad to mTilePositions.
		mTilePositions[tile_pos] = tile;
		
		std::for_each(	std::begin(vertices), 
						std::end(vertices),
						[&](sf::Vertex& v){
							mVertices.append(v);
						});
	}

	//Return Successful.
	return true;
}

const Tilemap::TileData& Tilemap::getTileDataFor(int tileID)
{
	//Check if the tiledata was found.
	auto found = mTileData.find(tileID+1);
	
	//If it wasn't found...
	if(found == mTileData.end())
	{
		return mDefaults;
	}
	
	//Otherwise, return the info.
	return found->second;
}

bool Tilemap::isCollidingWithTile(sf::Vector2f pos)
{
	//Get the inside tile.
	sf::Vector2f tpos = getTileInside(pos);
	
	//Get the tile's ID.
	int ID = getTileID(tpos);
	
	//Get the tile's data.
	auto data = getTileDataFor(ID);
	
	//Assert the tile is collideable.
	if(!data.collideable)
		return false;
	
	//Create a FloatRect for the position + bounds.
	sf::FloatRect bounds = {
		pos.x + data.bounds.left,
		pos.y + data.bounds.top,
		data.bounds.width,
		data.bounds.height
	};
	
	//Return whether or not the position is contained.
	return bounds.contains(pos);
	
	/*
	^^^ Are the last 2 statements necessary? ^^^
	*/
}

bool Tilemap::isCollidingWithTile(sf::FloatRect col)
{
	//Get the tiles at the top left & bottom right positions.
	sf::Vector2f top_left = getTileInside(sf::Vector2f{col.left, col.top});
	sf::Vector2f bottom_right = getTileInside(sf::Vector2f{
		col.left + col.width,
		col.top + col.height
	});
	
	//Iterate through all tiles inbetween.
	for(float y = top_left.y; y <= bottom_right.y; y += mTileDimensions.y)
	{
		for(float x = top_left.x; x <= bottom_right.x; x += mTileDimensions.x)
		{
			//Get the tile at the current position.
			sf::Vector2f tpos = getTileInside(sf::Vector2f(x, y));
			
			//Get the tile's ID.
			int ID = getTileID(tpos);
			
			//Get the tile's data.
			auto data = getTileDataFor(ID);
			
			//If the tile is collideable, it's colliding. Return true.
			if(data.collideable)
				return true;
		}
	}
	
	return false;
}

sf::Vector2f Tilemap::getTileInside(sf::Vector2f pos)
{
	//Floor the positions..
	int x = pos.x;
	int y = pos.y;
	
	//Divide by mTileDimensions.
	x /= mTileDimensions.x;
	y /= mTileDimensions.y;
	
	//Multiply back & return.
	x *= mTileDimensions.x;
	y *= mTileDimensions.y;
	
	return sf::Vector2f(x, y);
}

int Tilemap::getTileID(sf::Vector2f pos)
{
	//Check if it's found.
	auto found = mTilePositions.find(pos);
	
	//If it's not found,
	if(found == mTilePositions.end())
	{
		//Return -1
		return -1;
	}
	
	//Otherwise, return the ID.
	return found->second;
}