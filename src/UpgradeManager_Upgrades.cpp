#include "UpgradeManager.hpp"

void UpgradeManager::initUpgradeMap()
{
	using array_t = nlohmann::json::array_t;

	/**
	 * @brief Increases the TPS by the first args.
	 * 
	 */
	mUpgradeMap["tps_inc"] = [&](array_t args) {
		this->mBuilder->mTPS += args.at(0).get<float>();
	};

	/**
	 * @brief Changes a building's pertick value.
	 * 
	 * @param args {
	 * 0: Building name.
	 * 1: "out" or "in" (resource_out / resource_in)
	 * 2: Resource name.
	 * 3: the operator to act on the existing value
	 * 4: value.
	 * }
	 * 
	 */
	mUpgradeMap["pertick_mod"] = [&](array_t args) {
		std::string bname		  = args.at(0).get<std::string>();
		std::string resource_oper = "resource_" + args.at(1).get<std::string>();
		std::string rname		  = args.at(2).get<std::string>();
		std::string oper		  = args.at(3).get<std::string>();
		int value				  = args.at(4).get<int>();

		//Get the resource array.
		BuildingManager::Building* building = this->mBuilder->getBuilding(bname);
		array_t resources					= (*building)["pertick"][resource_oper];

		//Find the necessary value.
		auto resource = std::find_if(resources.begin(), resources.end(), [&](nlohmann::json& obj) -> bool {
			return obj.at("name").get<std::string>() == rname;
		});
		int index	 = std::distance(resources.begin(), resource);

		//Get the resource count.
		int ct = resource->at("count").get<int>();

		//Iterate through the operator choices.
		if (oper == "+")
		{
			ct += value;
		}
		else if (oper == "-")
		{
			ct -= value;
		}
		else if (oper == "*")
		{
			ct *= value;
		}
		else if (oper == "/")
		{
			ct /= value;
		}
		else if (oper == "=")
		{
			ct = value;
		}

		//Set the new resource count.
		(*building)["pertick"][resource_oper][index]["count"] = ct;
	};
}