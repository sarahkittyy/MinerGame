#include "MaterialManager.hpp"

MaterialManager::MaterialManager()
{
}

void MaterialManager::initResources(nlohmann::json &objectdata)
{
	std::string texture_dir =
		"resource/objects/" + objectdata.at("texturedir").get<std::string>();

	// For every object in the "resources" array...
	for (nlohmann::json &obj :
		 objectdata.at("resources").get<nlohmann::json>())
	{
		// Get its name, and add it to the mResources map.
		std::string name = obj.at("name").get<std::string>();

		mResources[name] = 0;

		// Init the icon texture directory.
		mIconTextures[name] = sf::Texture();
		mIconTextures[name].loadFromFile(texture_dir +
										 obj.at("icon").get<std::string>());

		// Init the deque resourceLog
		mResourceLog[name] = std::deque<float>();
	}
}

void MaterialManager::setResourceCount(MaterialManager::Resource r)
{
	// Set the new count of resources.
	mResources[r.name] = r.count;
}

int MaterialManager::getResourceCount(std::string resource_name)
{
	return mResources[resource_name];
}

void MaterialManager::addResources(MaterialManager::Resource r)
{
	// Add the specified resource count.
	mResources[r.name] += r.count;
}

void MaterialManager::removeResources(MaterialManager::Resource r)
{
	mResources[r.name] -= r.count;
}

std::vector<MaterialManager::Resource> MaterialManager::priceToResourceVector(
	nlohmann::json::array_t price)
{
	std::vector<Resource> ret;

	//Append each resource item.
	for (auto &i : price)
	{
		ret.push_back({.name  = i.at("name").get<std::string>(),
					   .count = i.at("count").get<long>()});
	}

	//Return the resulting vector.
	return ret;
}

bool MaterialManager::canPurchase(MaterialManager::Resource r)
{
	return mResources[r.name] >= r.count;
}

bool MaterialManager::canPurchaseMultiple(std::vector<MaterialManager::Resource> r)
{
	bool ret = true;
	//For every resource...
	for (auto &i : r)
	{
		//If any one of them isn't purcahseable...
		if (!canPurchase(i))
		{
			//..It's unpurchaseable.
			ret = false;
			break;
		}
	}
	return ret;
}

bool MaterialManager::purchase(MaterialManager::Resource r)
{
	if (!canPurchase(r))
	{
		return false;
	}

	// Purchase the item.
	mResources[r.name] -= r.count;

	// We were successful.
	return true;
}

bool MaterialManager::purchaseMultiple(std::vector<MaterialManager::Resource> r)
{
	if (!canPurchaseMultiple(r))
	{
		return false;
	}

	//Purchase
	for (auto &i : r)
	{
		mResources[i.name] -= i.count;
	}

	//Return successful.
	return true;
}

void MaterialManager::updateResourceLogger()
{
	// Push the count of all resources back into the logger.
	for (auto &i : mResources)
	{
		std::deque<float> *queue = &(mResourceLog.find(i.first)->second);
		// Push the current value.
		queue->push_back(i.second);

		// Pop the other end if the size is too large.
		if (queue->size() > LOG_QUEUE_SIZE)
		{
			queue->pop_front();
		}
	}
}

float MaterialManager::getAverageResourcePerTick(std::string resource)
{
	// Get the queue of the specific resource.
	std::deque<float> *queue = &(mResourceLog.find(resource)->second);

	// Get the difference of all elements.
	std::vector<float> queue_diff;

	// Assert that elements are actually yknow, *in the queue*
	if (queue->size() <= 1)
	{
		return 0;
	}

	// Iterate over all queue elements.
	for (unsigned i = 0; i < queue->size() - 1; ++i)
	{
		// Push back the change in resources per tick.
		queue_diff.push_back((*queue)[i + 1] - (*queue)[i]);
	}

	// Return the average difference.
	return std::accumulate(queue_diff.begin(), queue_diff.end(), 0.0f) /
		   (float)queue_diff.size();
}

const std::map<std::string, long> &MaterialManager::getResources()
{
	return mResources;
}

sf::Texture *MaterialManager::getTexture(std::string resource)
{
	// Assert the resource exists.
	auto found = mIconTextures.find(resource);
	if (found == mIconTextures.end())
	{
		throw std::out_of_range("Resource " + resource + " not found.");
	}

	// Return the texture.
	return &(found->second);
}