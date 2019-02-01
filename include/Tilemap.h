#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>

#include "nlohmann/json.hpp"

#include "CollisionBox.h"

#include "Vector2Hash.h"

/**
 * @brief Renders a grid of tiles to the screen, using a VertexArray.
 * 
 */
class Tilemap : public sf::Drawable,
				public sf::Transformable
{
protected:
	/**
	 * @brief A struct for the data of each type of tile.
	 * Each tile *ID* uses either the mDefaults values or the specified values.
	 * 
	 * @see resource/maps/<ID>.json
	 * 
	 */
	struct TileData
	{
		/**
		 * @brief True if the tile is collideable.
		 * 
		 */
		bool collideable;

		/**
		 * @brief The collision boundaries of the tile.
		 * 
		 */
		sf::FloatRect bounds;
	};
	
public:
	/**
	 * @brief Construct the map.
	 * 
	 */
	Tilemap();

	/**
	 * @brief Loads the tilemap data from it's ID.
	 * 
	 * @param id The ID of the map.
	 * @return true The map loaded properly.
	 * @return false The map didn't load properly.
	 * 
	 * @see resource/maps/<ID>.json
	 */
	bool loadFromID(int id);
	
	//////////////COLLISION INFORMATION RETRIEVAL//////////////
	
	/**
	 * @brief Get the TileData for the specific ID.
	 * 
	 * @param tileID The ID to retrieve.
	 * @return const TileData& The data of the tile.
	 */
	const TileData& getTileDataFor(int tileID);	
	
	/**
	 * @brief Get the Tile ID at the specified position.
	 * 
	 * @param pos The exact position of the tile.
	 * @return int The ID.
	 */
	int getTileID(sf::Vector2f pos);
	
	/**
	 * @brief Checks if the position given is inside a collideable tile.
	 * 
	 * @param pos The position to check. 
	 * @return true If the position is inside a collideable tile.
	 */
	bool isCollidingWithTile(sf::Vector2f pos);
	
	/**
	 * @brief Checks if the rectangle is colliding with any collideable tiles.
	 * 
	 * @param col The bounds to check.
	 * @return true If the box is colliding with any tile.
	 */
	bool isCollidingWithTile(sf::FloatRect col);

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(	sf::RenderTarget& target,
						sf::RenderStates states) const;

	/**
	 * @brief The internal vector of vertices.
	 * 
	 */
	sf::VertexArray mVertices;

	/**
	 * @brief The tilemap to render w/ the vertex array.
	 * 
	 */
	sf::Texture mMapTexture;

	//////////////MAP DATA////////////////

	/**
	 * @brief The internal vector of tile ID's.
	 * 
	 * @remarks The ID corresponds to a position in the mMapTexture, left->right. 0 is an empty, "air" tile.
	 * 
	 */
	std::vector<int> mTiles;

	/**
	 * @brief The dimensions of a single tile.
	 * 
	 */
	sf::Vector2i mTileDimensions;

	/**
	 * @brief The dimensions of the whole tilemap grid, in tiles.
	 * 
	 */
	sf::Vector2i mGridDimensions;

	/////////////////TILE DATA///////////////
	
	/**
	 * @brief A vector of all tile positions.
	 * 
	 */
	std::unordered_map<sf::Vector2f, int, Vector2Hash> mTilePositions;
	
	/**
	 * @brief The default tile data values, for unspecified tile data.
	 * 
	 */
	TileData mDefaults;

	/**
	 * @brief A map of custom tile data, specified in resource/maps/<ID>.json
	 * 
	 */
	std::unordered_map<int, TileData> mTileData;

	//////////////INITIALIZATION FUNCTIONS//////////////////

	/**
	 * @brief Retrieves all graphical data from the specified map. (<ID>_Data.json).
	 * 
	 * @param graphicaldata A json object to the file.
	 * @return true The retrieval was successful.
	 * @return false Something failed >w<
	 */
	bool getGraphicalData(nlohmann::json& graphicaldata);

	/**
	 * @brief Retrieves all data about individual tiles, as well as tile defaults.
	 * 
	 * @param tiledata 
	 * @return true 
	 * @return false 
	 */
	bool getTileData(nlohmann::json& tiledata);

	/**
	 * @brief Performs the final initializion of the vertices, for rendering.
	 * 
	 * @return true If successful.
	 */
	bool updateVertices();
	
	///////////////EXTRA UTILITY FUNCTIONS/////////////////
	
	/**
	 * @brief Returns the tile that the point is contained inside of.
	 * 
	 * @param pos The point to check. 
	 * @return sf::Vector2f The top left position of the tile currently inside.
	 */
	sf::Vector2f getTileInside(sf::Vector2f pos);
};