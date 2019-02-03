#include "Tilemap.hpp"

Tilemap::Tilemap()
{
	//Set the vertices primitive type.
	mVertices.setPrimitiveType(sf::Quads);
}

void Tilemap::draw(	sf::RenderTarget& target,
					sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &mMapTexture;
	target.draw(mVertices, states);
}

bool Tilemap::loadFromFilename(std::string fname)
{
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
	mTileDefaults = tiledata["defaults"];
	
	
	///////////////////////////

	//If there's no individual tile data, return successful.
	if(tiledata.find("tiles") == tiledata.end())
	{
		return true;
	}

	//Otherwise, set mTileData to the data.
	mTileData = tiledata["tiles"];

	//Return successful.
	return true;
}

void Tilemap::setTileAt(sf::Vector2f pos, int newTileID)
{
	//Get the tile at the given position.
	auto found = mTilePositions.find(getTileInside(pos));
	
	//If not found, return.
	if(found == mTilePositions.end())
	{
		return;
	}
	
	//Otherwise, set the tile ID at that position.
	if(newTileID != 0)
		found->second = newTileID - 1;
	
	//Get the position of it in the mTiles vector.
	int vecpos = found->first.x + found->first.y * mGridDimensions.x;
	
	//Set the mTiles ID.
	mTiles[vecpos] = newTileID;
	
	//Update the vertices.
	updateVertices();
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

const nlohmann::json& Tilemap::getTileDataFor(int tileID)
{
	//Check if the tiledata was found.
	auto found = mTileData.find(std::to_string(tileID));
	
	//If it wasn't found...
	if(found == mTileData.end())
	{
		return mTileDefaults;
	}
	
	//Otherwise, return the info.
	return *found;
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