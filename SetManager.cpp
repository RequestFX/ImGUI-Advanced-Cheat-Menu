#include "SetManager.hpp"

#include "util/StringH.hpp"

Set& SetManager::add(Set* set) {
	settings.push_back(set);
	return *set;
}

Set* SetManager::getSetByName(std::string ID, std::string ID2) {
	for (Set* set : settings) {
		if (!ID2.empty()) {
			if (StringH::equalsIgnoreCase(set->ID2, ID2) && StringH::equalsIgnoreCase(set->ID, ID)) return set;
			continue;
		}
		if (StringH::equalsIgnoreCase(set->ID, ID))return set;
	}
	return NULL;
}