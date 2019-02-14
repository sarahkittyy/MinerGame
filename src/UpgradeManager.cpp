#include "UpgradeManager.hpp"

UpgradeManager::UpgradeManager(BuildingManager* buildingmgr)
{
	//Set the internal materialmanager ptr.
	mMaterials	 = buildingmgr->getMaterialManager();
	mRenderTooltip = false;
	mBuilder	   = buildingmgr;

	initUpgradeMap();
}

void UpgradeManager::loadUpgradeData(nlohmann::json object_data)
{
	//Texture prefix
	std::string texture_prefix = "resource/objects/textures/";

	//For every upgrade...
	for (auto& upgrade : object_data.at("upgrades"))
	{
		//Push the upgrade back in mUpgrades.
		mUpgrades.push_back(upgrade);

		std::string upgrade_name = upgrade.at("name")
									   .get<std::string>();

		//Get the texture..
		std::string texture_path = texture_prefix +
								   upgrade.at("icon").get<std::string>();

		//Load the texture.
		mUpgradeTextures[upgrade_name].loadFromFile(texture_path);
	}
}

void UpgradeManager::renderGui()
{
	//To only hover one item per frame.
	bool hoveredThisFrame = false;
	mRenderTooltip		  = false;

	//Render the buttons.
	for (auto& i : mUpgrades)
	{
		//Check if the upgrade is locked...
		if (!i.at("unlocked").get<bool>())
		{
			//Unlock it if we can purchase it...
			if (mMaterials->canPurchaseMultiple(
					mMaterials->priceToResourceVector(i.at("unlock_price").get<nlohmann::json::array_t>())))
			{
				i["unlocked"] = true;
			}
			//Otherwise ignore this item.
			else
			{
				continue;
			}
		}

		//Assert the upgrade still has uses.
		int uses = i.at("uses").get<int>();
		if (uses == 0)
		{
			continue;
		}

		//Get the texture.
		auto* tex = getUpgradeTexture(i);

		//Draw the button.
		if (ImGui::ImageButton(*tex, 1))
		{
			//If pressed, call the upgrade.
			callUpgrade(i);
		}

		//If the button is hovered...
		if (ImGui::IsItemHovered() && !hoveredThisFrame)
		{
			//Toggle tooltip rendering for that upgrade.
			hoveredThisFrame = true;
			mRenderTooltip   = true;
			tooltipUpgrade   = &i;
		}

		ImGui::NextColumn();
	}
}

bool UpgradeManager::renderGuiTooltip()
{
	if (!mRenderTooltip)
		return false;
	/*
	ITEMS TO RENDER:
	* Icon & Name
	* Description
	* Price...
	*/

	//..Icon & name..
	ImGui::Image(*getUpgradeTexture(*tooltipUpgrade));
	ImGui::SameLine();
	ImGui::Text("%s", tooltipUpgrade->at("name").get<std::string>().c_str());

	//Description.
	ImGui::Text("%s", tooltipUpgrade->at("description").get<std::string>().c_str());

	//Price...
	ImGui::Text("Price:");
	for (auto& i : tooltipUpgrade->at("price"))
	{
		//Get the resource name & count.
		std::string rname = i.at("name").get<std::string>();
		int rcount		  = i.at("count").get<int>();

		//Draw the image.
		ImGui::Image(*mMaterials->getTexture(rname));
		ImGui::SameLine();
		//Resource name & count.
		ImGui::Text("%s - %d",
					rname.c_str(),
					rcount);
	}

	return true;
}

void UpgradeManager::callUpgrade(Upgrade& upgrade)
{
	//Get the vector of resources it costs.
	std::vector<MaterialManager::Resource> resource_cost = mMaterials->priceToResourceVector(upgrade.at("price").get<nlohmann::json::array_t>());

	//Purchase it if we can..
	if (!mMaterials->purchaseMultiple(resource_cost))
	{
		return;
	}

	//..KK, now decrement it's uses.
	int uses = upgrade["uses"].get<int>();
	uses--;
	upgrade["uses"] = uses;

	//Get the price factor.
	float factor = upgrade.at("pricefactor").get<float>();

	//Multiply all resources in the price by the price factor.
	for (auto& i : upgrade["price"])
	{
		float count = i.at("count").get<float>();
		count *= factor;
		i["count"] = count;
	}

	//Iterate over all methods.
	for (auto& i : upgrade.at("methods"))
	{
		//Get the method.
		std::string method_name				= i.at("call").get<std::string>();
		nlohmann::json::array_t method_args = i.at("args")
												  .get<nlohmann::json::array_t>();
		//Call the method.
		mUpgradeMap[method_name](method_args);
	}
}

sf::Texture* UpgradeManager::getUpgradeTexture(Upgrade& up)
{
	//Get the name.
	std::string name = up.at("name").get<std::string>();

	//Find the texture.
	auto found = mUpgradeTextures.find(name);

	//If it doesn't exist, return nullptr.
	if (found == mUpgradeTextures.end())
	{
		return nullptr;
	}
	else
	{
		//Otherwise, return the texture.
		return &(found->second);
	}
}