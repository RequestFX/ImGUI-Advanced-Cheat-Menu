#include "ModuleManager.hpp"
#include "HUD.hpp"
#include "ESP.hpp"
#include "RCS.hpp"
#include "Marker.hpp"
#include "AimAssist.hpp"

#include "util/StringH.hpp"

ModuleManager::ModuleManager() {
	modules.push_back(&AimAssist::i());
	modules.push_back(&Marker::i());
	modules.push_back(&HUD::i());
	modules.push_back(&RCS::i());
	modules.push_back(&ESP::i());
}

Module* ModuleManager::getModuleByName(std::string name) {
	for (Module* mod : modules) {
		if (StringH::equalsIgnoreCase(mod->getName(), name))return mod;
	}
	return NULL;
}