# Object Notes

## Important object_data.json tags

* `"texturedir"`
	* The base directory to the buildings & icons directories. Defaults to textures/
* `"resources"`
	* Information on the types of collectable resources in-game.
	* Objects are g`iven a name & a path to an icon.
* `"buildings"
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
			
## Upgrades

* `"upgrades"`
	* `"name"`: The upgrade name.
	* `"description"`: The upgrade description.
	* `"icon"`: Path to the texture displayed for the upgrade.
	* `"unlocked"`: Whether or not the upgrade is unlocked by default.
	* `"unlock_price"`: The minimum resource count to reach to view the unlock (not spent).
	* `"uses"`: How many uses before expiring. -1 is infinite.
	* `"price"`: Array of resource objects, with a name & a count. See above.
	* `"pricefactor"`: What to multiply the price by on each purchase.
	* `"methods"`: Array of upgrade function calls.
		* `"call"`: See below.
		* `"args"`: Array, see below.
		
### Methods

All upgrade calls are defined in `src/UpgradeManager_Upgrades.cpp`

Here is a table of all of them.
<!--Sorry for the ugliness of this table.-->

| Call Name | Purpose | Argument Count | Arguments |
|-----------|---------|----------------|-----------|
| tps_inc | Increases the TPS | 1 | Increases the game TPS by the given number. |
| pertick_mod | Changes the per-tick resource modifications of a building. | 5 | 0 - Name of the building<br>1 - "in" or "out", for the resources in/tick or out/tick.<br>2 - The resource name.<br>3 - "+","-","*","/" - The operator to use on the existing value with the next value.<br>4 - The value to change the existing value with.
| price_mod | Changes the sell/buy price of a building | 5 | 0 - "sell", "buy", "both" - Which type of cost to modify.<br>1 - The building name.<br>2 - The resource name.<br>3 - The operator to act on the value.<br>4 - The value to change the existing value with.
