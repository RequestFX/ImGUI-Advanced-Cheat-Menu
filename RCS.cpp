#include "RCS.hpp"
#include "menu/imgui_helper.hpp"
#include <Windows.h>

RCS::RCS() : Module(obf("RCS"), obf("Comprehends for Shooting Recoil")) {
	xPow = 0.6;
	yPow = 0.5;
}