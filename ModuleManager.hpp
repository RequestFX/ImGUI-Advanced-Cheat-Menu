#pragma once
#include "util/Singleton.hpp"
#include "Module.hpp"

#include <vector>

class ModuleManager : public Singleton<ModuleManager> {
	friend class Singleton<ModuleManager>;
public:
	std::vector<Module*> modules; // virtual functions need pointers

	ModuleManager();
};