#pragma once
#include "util/Singleton.hpp"

class Config : public Singleton<Config> {
	friend class Singleton<Config>;
public:
	bool save();
	bool load();
};