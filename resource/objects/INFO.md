# Object Notes

## Important object_data.json tags

* "texturedir"
	* The base directory to the buildings & icons directories. Defaults to textures/
* "resources"
	* Information on the types of collectable resources in-game.
	* Objects are given a name & a path to an icon.
* "buildings"
	* Data on buildings.
	* Each building object contains a:
		* Name.
		* Price
			* Contains an array of objects similar to in `resources`, except with a count instead of an icon.
			* Can contain multiple necessary resources, each with their own price.
		* Texture
			* Path to the texture of the building itself.
		* Description
			* A description of the tower's stats and/or usage.
		* Pertick
			* Data on the tower's function per tick.
			* Ex:
			```json
			"pertick": {
				"resource_in": [{
					"name": "Coal",
					"count": 10
				}],
				"resource_out": [{
					"name": "Wood",
					"count": 1
				}]
			}
			```
			This object takes in 10 coal/tick and outputs 1 wood/tick.
		* Canbuildon
			* Contains an array of strings corresponding to tile names.
			* The tower can only be placed on specified tile types.
			* See `resource/maps/...`

## Coming Soon:

* Upgrades!