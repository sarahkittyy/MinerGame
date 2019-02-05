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