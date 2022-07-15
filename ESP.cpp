#include "ESP.hpp"
#include "menu/imgui_helper.hpp"
#include "SetManager.hpp"
#include <Windows.h>

ESP::ESP() : Module(obf("ESP"), obf("Render Entities through Walls"), VK_DIVIDE) {
	colSkeleton = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(222, 144, 154, 200), obf("colSkeleton"), getName())).getVec4();
	col2DBox = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(114, 222, 154, 200), obf("col2DBox"), getName())).getVec4();
	colHealthBar = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(114, 144, 222, 200), obf("colHealthBar"), getName())).getVec4();
	colHeadCircle = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(188, 169, 154, 200), obf("colHeadCircle"), getName())).getVec4();
	
	isSkeleton = &SetManager::i().add(new Set(false, obf("isSkeleton"), getName())).getBVal();
	is2DBox = &SetManager::i().add(new Set(false, obf("is2DBox"), getName())).getBVal();
	isHealthBar = &SetManager::i().add(new Set(false, obf("isHealthBar"), getName())).getBVal();
	isHeadCircle = &SetManager::i().add(new Set(false, obf("isHeadCircle"), getName())).getBVal();
	isEnemy = &SetManager::i().add(new Set(true, obf("isEnemy"), getName())).getBVal();
	isMate = &SetManager::i().add(new Set(false, obf("isMate"), getName())).getBVal();
	isBot = &SetManager::i().add(new Set(false, obf("isBot"), getName())).getBVal();
	isSkeletonHealthBased = &SetManager::i().add(new Set(false, obf("isSkeletonHealthBased"), getName())).getBVal();
	is2DBoxHealthBased = &SetManager::i().add(new Set(false, obf("is2DBoxHealthBased"), getName())).getBVal();
	isHealthBarHealthBased = &SetManager::i().add(new Set(false, obf("isHealthBarHealthBased"), getName())).getBVal();
	isHeadCircleHealthBased = &SetManager::i().add(new Set(false, obf("isHeadCircleHealthBased"), getName())).getBVal();
}