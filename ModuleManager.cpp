#include "ModuleManager.hpp"
#include "HUD.hpp"
#include "ESP.hpp"
#include "RCS.hpp"
#include "Marker.hpp"
#include "AimAssist.hpp"

ModuleManager::ModuleManager() {
	modules.push_back(&AimAssist::get());
	modules.push_back(&Marker::get());
	modules.push_back(&HUD::get());
	modules.push_back(&RCS::get());
	modules.push_back(&ESP::get());
}