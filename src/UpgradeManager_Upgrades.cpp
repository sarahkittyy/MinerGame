#include "UpgradeManager.hpp"

void UpgradeManager::initUpgradeMap()
{
	using array_t  = nlohmann::json::array_t;
	using object_t = nlohmann::json::object_t;
	using nlohmann::json;
	using std::string;

	/**
	 * @brief When executing upgrades that modify values, operators are usually passed by string. This function therefore reduces boilerplate code.
	 * 
	 */
	auto exec_oper =
		[&](string oper, float& lvalue, const float& rvalue) {
			//Iterate through the operator choices.
			if (oper == "+")
			{
				lvalue += rvalue;
			}
			else if (oper == "-")
			{
				lvalue -= rvalue;
			}
			else if (oper == "*")
			{
				lvalue *= rvalue;
			}
			else if (oper == "/")
			{
				lvalue /= rvalue;
			}
			else if (oper == "=")
			{
				lvalue = rvalue;
			}
		};

	/**
	 * @brief Increases the TPS by the first arg.
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
	 * 2: The resource name.
	 * 3: The operator to act on the existing value
	 * 4: The rvalue.
	 * }
	 * 
	 */
	mUpgradeMap["pertick_mod"] = [&, exec_oper](array_t args) {
		string bname		 = args.at(0).get<string>();
		string resource_oper = "resource_" + args.at(1).get<string>();
		string rname		 = args.at(2).get<string>();
		string oper			 = args.at(3).get<string>();
		float value			 = args.at(4).get<float>();

		//Get the resource array.
		BuildingManager::Building* building = this->mBuilder->getBuilding(bname);
		array_t resources					= (*building)["pertick"][resource_oper];

		//Find the necessary value.
		auto resource = std::find_if(resources.begin(), resources.end(), [&](json& obj) -> bool {
			return obj.at("name").get<string>() == rname;
		});
		int index	 = std::distance(resources.begin(), resource);

		//Get the resource count.
		float ct = resource->at("count").get<float>();

		//Execute the operator.
		exec_oper(oper, ct, value);

		//Set the new resource count.
		(*building)["pertick"][resource_oper][index]["count"] = ct;
	};

	/**
	 * @brief Modifies the price / sell price of the building.
	 * 
	 * @param args {
	 * 0: "sell", "buy", or "both" - which type of cost to modify.
	 * 1: The building name.
	 * 2: The resource name.
	 * 3: The operator to act on the existing value.
	 * 4: The rvalue.
	 * }
	 * 
	 */
	mUpgradeMap["price_mod"] = [&, exec_oper](array_t args) {
		string cost_to_modify = args.at(0).get<string>();
		string building_name  = args.at(1).get<string>();
		string resource_name  = args.at(2).get<string>();
		string oper			  = args.at(3).get<string>();
		float rvalue		  = args.at(4).get<float>();

		//Get the building.
		auto building = this->mBuilder->getBuilding(building_name);

		if (cost_to_modify == "buy" || cost_to_modify == "both")
		{
			//Get the price.
			array_t cprice = building->at("price");

			//Get the resource count to modify.
			auto resource =
				std::find_if(cprice.begin(),
							 cprice.end(),
							 [&](json& obj) -> bool {
								 return obj["name"].get<string>() == resource_name;
							 });

			float resource_val = resource->at("count").get<float>();

			//Fix the value.
			exec_oper(oper, resource_val, rvalue);

			//Get the distance into the price vector we are.
			int index = std::distance(cprice.begin(), resource);

			//Push the resource back.
			(*building)["price"][index]["count"] = (long)resource_val;
		}
		if (cost_to_modify == "sell" || cost_to_modify == "both")
		{
			//Get the price.
			array_t cprice = building->at("sellprice");

			//Get the resource count to modify.
			auto resource =
				std::find_if(cprice.begin(),
							 cprice.end(),
							 [&](json& obj) -> bool {
								 return obj["name"].get<string>() == resource_name;
							 });

			float resource_val = resource->at("count").get<float>();

			//Fix the value.
			exec_oper(oper, resource_val, rvalue);

			//Get the distance into the price vector we are.
			int index = std::distance(cprice.begin(), resource);

			//Push the resource back.
			(*building)["sellprice"][index]["count"] = (long)resource_val;
		}
	};
}