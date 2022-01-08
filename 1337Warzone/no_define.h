#pragma once

namespace No_Define
{
	uintptr_t BaseAddress;
	uint64_t PEB;
}
namespace No_Renderer_Define
{
	int Width = GetSystemMetrics(SM_CXSCREEN);
	int Height = GetSystemMetrics(SM_CYSCREEN);
}
namespace Settings
{
	bool Aimbot = false;
	int smooth = 1;
	bool ESP = false;
	bool ESP_Box = false;
	bool ESP_Line = false;
	int ESP_Box_Type = 1;
	int ESP_Line_Type = 1;
	bool ESP_LinesAbove = false;
	bool ESP_LinesBelow = false;
	bool ESP_Names = false;
	bool  Health = false;
	bool ESP_Distance = false;
	int ESP_MaxDistance = 300;
	bool ShowFovCircle = true;
	int FovCircleValue = 0;
	bool ConstantUav = false;
	bool RainbowMode = false;
	bool Skeleton = false;
}
namespace Menu
{
	void Theme();
	void Render();
}
struct Globals
{
	static Globals* Get()
	{
		static auto* instance = new Globals();
		return instance;
	}

	int MenuTab = -1;

	bool Enabled = false;
	int AimbotSmooth = 0;
	bool MenusBeside = false;
};
namespace SettingsColor 
{
	ImColor ESPBox = { 255, 255, 255, 200 };
	float ESPBox_float[4] = { 255, 255, 255, 200 };
	ImColor ESPLines = { 255, 255, 255, 200 };
	float ESPLines_float[4] = { 255, 255, 255, 200 };
	ImColor ESPNames = { 255, 0, 0, 255 };
	float ESPNames_float[4] = { 255, 0, 0, 255 };
	ImColor ESPDistance = { 255, 255, 255, 200 };
	float ESPDistance_float[4] = { 255, 255, 255, 200 };
	ImColor FovColor = { 255, 255, 255, 200 };
	float FovColor_float[4] = { 255, 255, 255, 200 };
	ImColor RainbowColorCool;
}
namespace Addresses
{
	uint64_t INFO;
	uint64_t BASE;
	uint64_t REFDEF;
	uint64_t NAMES;
	uint64_t VISIBLE;
	uint64_t BONE_BASE;
}

#include "no_draw.h"
#include "no_menu.h"
