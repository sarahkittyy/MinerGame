#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "nlohmann/json.hpp"

#include "Vector2Hash.inl"

/**
 * @brief Renders a grid of tiles to the screen, using a VertexArray.
 *
 */
class Tilemap : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief Construct the map.
	 *
	 */
	Tilemap();

	/**
	 * @brief Construct the map from it's name. Calls loadFromFilename()
	 * 
	 */
	Tilemap(std::string fname);

	/**
	 * @brief Loads the tilemap data from it's name.
	 *
	 * @param name The name of the map, without the path/.json extension.
	 * @return true The map loaded properly.
	 * @return false The map didn't load properly.
	 *
	 * @see resource/maps/name.json
	 */
	bool loadFromFilename(std::string fname);

	//////////////COLLISION INFORMATION RETRIEVAL//////////////

	/**
	 * @brief Get the TileData for the specific ID.
	 *
	 * @param tileID The ID to retrieve.
	 * @return nlohmann::json The data of the tile.
	 *
	 * @remarks tileID includes air as 0.
	 */
	nlohmann::json getTileDataFor(int tileID);

	/**
	 * @brief Get the Tile ID at the specified position.
	 *
	 * @param pos The exact position of the tile.
	 * @return int The ID.
	 */
	int getTileID(sf::Vector2f pos);

	/**
	 * @brief Get a Tile's ID from it's name.
	 *
	 * @param tile_name The name of a tile.
	 * @return int Its ID.
	 */
	int getTileIDFromName(std::string tile_name);

	/**
	 * @brief Set the the at given position to the given ID.
	 *
	 * @param pos The tile position to set.
	 * @param newTileID The new tile ID.
	 */
	void setTileAt(sf::Vector2f pos, int newTileID);

	/**
	 * @brief Returns the tile that the point is contained inside of.
	 *
	 * @param pos The point to check.
	 * @return sf::Vector2f The top left position of the tile currently inside.
	 */
	sf::Vector2f getTileInside(sf::Vector2f pos);

	/**
	 * @brief Get the size of each individual tile.
	 *
	 * @return sf::Vector2f The size of a tile.
	 */
	sf::Vector2f getTileSize();

	/**
	 * @brief Return the texture of the tilemap.
	 *
	 * @return sf::Texture& A reference to the internal tilemap texture.
	 */
	sf::Texture &getTileMapTexture();

	/**
	 * @brief Get the position of a tile in the tilemap.
	 *
	 * @param tile_name The name of the tile.
	 * @return sf::FloatRect The area of mMapTexture that the tile resides.
	 */
	sf::FloatRect getTileTextureRect(std::string tile_name);

private:
	/**
	 * @brief SFML's draw() override.
	 *
	 */
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

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
	 * @remarks The ID corresponds to a position in the mMapTexture,
	 * left->right. 0 is an empty, "air" tile. DO NOT USE OUTSIDE
	 * updateVertices()
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
	 * @brief The default tile data.
	 *
	 * @see resource/maps/INFO.md
	 *
	 */
	nlohmann::json mTileDefaults;

	/**
	 * @brief A json object for individual tile data.
	 *
	 * @remarks Objects are sorted by ID, so mTileData::at("0") is structured
	 * the same as mTileDefaults.
	 *
	 * @see resource/maps/INFO.md
	 */
	nlohmann::json mTileData;

	//////////////INITIALIZATION FUNCTIONS//////////////////

	/**
	 * @brief Retrieves all graphical data from the specified map.
	 * (<ID>_Data.json).
	 *
	 * @param graphicaldata A json object to the file.
	 * @return true The retrieval was successful.
	 * @return false Something failed >w<
	 */
	bool getGraphicalData(nlohmann::json &graphicaldata);

	/**
	 * @brief Retrieves all data about individual tiles, as well as tile
	 * defaults.
	 *
	 * @param tiledata
	 * @return true
	 * @return false
	 */
	bool getTileData(nlohmann::json &tiledata);

	/**
	 * @brief Performs the final initializion of the vertices, for rendering.
	 *
	 * @return true If successful.
	 */
	bool updateVertices();
};