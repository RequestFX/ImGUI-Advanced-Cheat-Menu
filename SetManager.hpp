#pragma once
#include "util/Singleton.hpp"
#include "Set.hpp"

#include <vector>

class SetManager : public Singleton<SetManager> {
	friend class Singleton<SetManager>;
public:
	std::vector<Set*> settings;

	Set& add(Set* set);
	Set* getSetByName(std::string ID, std::string ID2 = "");
};