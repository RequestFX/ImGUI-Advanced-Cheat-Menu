#pragma once

static bool isAimAssistEnabled, isAimEnemyTarget, isAimMateTarget, isAimBotTarget, relativeFOV = true, noAimSnap, noAimLock, isRCS, standaloneRCS;
static int aimAssistKey, aimAssistOnHold = 0, aimTargetSelection = 0, aimHitbox = 0, reactionms = 200, fov = 30;
static float rcsXStrength = 0.6, rcsYStrength = 0.9;

static bool isESPEnabled, espEnemy, espMate, espBot, espColByHealth, espShow2D, espShowSkeleton, espShowHealth, espShowHeadCircle, isESPMarkers;
static int espKey, espType = 0;
static ImVec4 espCol = ImVec4(114.f / 255.f, 144.f / 255.f, 154.f / 255.f, 200.f / 255.f), markerCol = ImVec4(60 / 255.f, 160 / 255.f, 200 / 255.f, 200 / 255.f);

static bool isModuleList;
static ImVec4 moduleListBg = ImVec4(0, 0, 0, 0.6);
static int moduleListSortby = 0, moduleListAlign = 0;