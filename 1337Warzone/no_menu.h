#pragma once
#include "xorstr.hpp"
#include "imguipp_v2.h"
#include "icons.h"
#include "font.h"
using namespace ImGuiPP;
static auto G = Globals::Get();
static const char* ESP_Box_TypeItems[]
{
	"Box",
	"Cornered",
	"3D Box"
};
static const char* ESP_Line_TypeItems[]
{
	"Above",
	"Middle",
	"Below"
};
bool Unlocker_Injected = false;
bool ShowTheMenu = true;
std::string getTitle(int& ref)
{
	switch (ref) 
	{
	case 0:
		return "Combat";
		break;
	case 1:
		return "Exploits";
		break;
	case 2:
		return "Visuals";
		break;
	case 3:
		return "Misc";
		break;
	case 4:
		return "Config";
		break;
	case 5:
		return "Profile";
		break;
	case 6:
		return "Anticheat";
		break;
	case 7:
		return "About";
		break;
	}
}
void MakeSection(std::vector<const char*> _str, int _new) 
{
	if (!_str.size() >= 1 || _str.size() > 2)
		return;
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 10, ImGui::GetCursorPosY() + 4));
	ImGui::Text(_str[0]); ImGui::SameLine(45);
	if (Globals::Get()->MenuTab == _new) {
		ImGui::TextColored(ImColor(8, 177, 77), _str[1]);
	}
	else
		ImGui::Text(_str[1]);
	if (ImGui::IsItemClicked())
	{
		Globals::Get()->MenuTab = _new;
	}
	ImGui::SameLine(ImGuiPP::GetX() - 25);
	ImGui::Text(ICON_FA_ANGLE_RIGHT);
	ImGui::ItemSize(ImVec2(3, 3));
}

void MakeSectionEx(std::vector<const char*> _str, int _new)
{
	if (!_str.size() >= 1 || _str.size() > 2)
		return;
	ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 10, ImGui::GetCursorPosY() + 4));
	ImGui::Text(_str[0]); ImGui::SameLine(10);
	if (Globals::Get()->MenuTab == _new) 
	{
		ImGui::TextColored(ImColor(0, 250, 112), _str[1]);
	}
	else
		ImGui::Text(_str[1]);
	if (ImGui::IsItemClicked())
	{
		Globals::Get()->MenuTab = _new;
	}
	ImGui::SameLine(ImGuiPP::GetX() - 25);
	ImGui::Text(ICON_FA_ANGLE_RIGHT);
	ImGui::ItemSize(ImVec2(3, 3));
}
void ComboBox(const char* title, int* sel, std::vector<const char*> items)
{
	if (!title)
		return;
	ImGui::Spacing();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
	ImGui::Text(title);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
	ImGui::PushItemWidth(GetX() - 10);
	ImGui::PushID(title);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(65, 65, 65, 255));
	ImGui::Combo("##Combo_", sel, items.data(), items.size());
	ImGui::PopStyleColor();
	ImGui::PopID();
	ImGui::PopItemWidth();
};
void Slider(const char* title, int* value, int min, int max) 
{
	ImGui::Spacing();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
	ImGui::Text(title);
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
	ImGui::PushID(title);
	ImGui::PushItemWidth(GetX() - 10);
	ImGui::SliderInt("##_slider_", value, min, max, "");
	ImGui::PopItemWidth();
	ImGui::PopID();
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
	ImGui::Text("%i%s", *value, "%");
};
void makeTitle(const char* _title, float _w = 250) 
{
	if (!_title)
		return;
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
	CenterTextEx(_title, 250, 0, 0);
};
void Menu::Render()
{
	if (GetAsyncKeyState(VK_INSERT) & 1) 
	{
		ShowTheMenu = !ShowTheMenu;
	}
	if (ShowTheMenu)
	{
		static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
		static ImVec2 mainPos = { };
		std::string title = getTitle(G->MenuTab);
		if (ImGui::Begin("##_Fanta", 0, flags)) 
		{
			mainPos = ImGui::GetCurrentWindow()->Pos;
			makeTitle("Fanta");
			if (ImGui::BeginChild("##MainSection", ImVec2(GetX(), GetY() - 145))) {

				ImGui::Spacing();
				MakeSection({ ICON_FA_ADJUST,  "Combat" }, 0);
				MakeSection({ ICON_FA_CUBES,   "Exploits" }, 1);
				MakeSection({ ICON_FA_EYE,     "Visuals" }, 2);
				MakeSection({ ICON_FA_WRENCH,  "Misc" }, 3);
				MakeSection({ ICON_FA_GLOBE,   "Config" }, 4);
				ImGui::EndChild();
			}
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);
			ImGui::TextColored(ImColor(50, 50, 50), "Misc");
			if (ImGui::BeginChild("##BottomMisc", ImVec2(GetX(), GetY()))) 
			{
				ImGui::Spacing();
				MakeSectionEx({ "", "Profile", }, 5);
				MakeSectionEx({ "", "Anticheat" }, 6);
				MakeSectionEx({ "", "About" }, 7);
				ImGui::EndChild();
			}
			ImGui::End();
		}

		if (G->MenusBeside) 
		{
			ImGui::SetNextWindowPos(ImVec2(mainPos.x + 250, mainPos.y), ImGuiCond_Always);
		}
		else {
			ImGui::SetNextWindowPos(ImVec2(mainPos.x + 250, mainPos.y), ImGuiCond_Once);
		}

		if (G->MenuTab != -1)
		{

			if (ImGui::Begin(title.c_str(), 0, flags)) 
			{
				if (ImGui::BeginChild("##Child_", ImVec2(GetX(), GetY())))
				{
					switch (G->MenuTab)
					{
					case 0: // Combat
						makeTitle("Combat");
						ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 6, ImGui::GetCursorPosY() + 6));
						ImGui::Checkbox("Enable", &Settings::Aimbot);
						Slider("Aimbot Smooth", &G->AimbotSmooth, 0, 25);
						Slider("Aimbot Fov", &Settings::FovCircleValue, 0, 100);
						ImGui::Text("");
						if (!Settings::RainbowMode)
						{
							ImGui::ColorEdit4(xorstr("Fov Circle"), SettingsColor::FovColor_float, ImGuiColorEditFlags_NoInputs);
						}
						break;
					case 1: // Exploits
						makeTitle("Exploits");
						ImGui::Text(" Coming Soon");
						break;
					case 2: // Visuals
						makeTitle("Visuals");
						ImGui::Checkbox(xorstr(" Enable ESP"), &Settings::ESP);
						if (Settings::ESP)
						{
							ImGui::Checkbox(xorstr("ESP Box"), &Settings::ESP_Box);
							if (Settings::ESP_Box)
							{
								ImGui::Combo(xorstr("Box Type"), &Settings::ESP_Box_Type, ESP_Box_TypeItems, sizeof(ESP_Box_TypeItems) / sizeof(*ESP_Box_TypeItems));
							}
							ImGui::Checkbox(xorstr("ESP Lines"), &Settings::ESP_Line);
							if (Settings::ESP_Line)
							{
								ImGui::Combo(xorstr("Lines Type"), &Settings::ESP_Line_Type, ESP_Line_TypeItems, sizeof(ESP_Line_TypeItems) / sizeof(*ESP_Line_TypeItems));
							}
							ImGui::Checkbox(xorstr("ESP Skeleton"), &Settings::Skeleton);
							ImGui::Checkbox(xorstr("ESP Names"), &Settings::ESP_Names);
							ImGui::Checkbox(xorstr("ESP Health"), &Settings::Health);
							ImGui::Checkbox(xorstr("ESP Distance"), &Settings::ESP_Distance);
							ImGui::SliderInt(xorstr("Max Distance"), &Settings::ESP_MaxDistance, 10, 500);
						}
						if (!Settings::RainbowMode)
						{
							ImGui::Text(" Colors");
							ImGui::ColorEdit4("ESP Box", SettingsColor::ESPBox_float, ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("ESP Lines", SettingsColor::ESPLines_float, ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("ESP Names", SettingsColor::ESPNames_float, ImGuiColorEditFlags_NoInputs);
							ImGui::ColorEdit4("ESP Distance", SettingsColor::ESPDistance_float, ImGuiColorEditFlags_NoInputs);
						}
						break;
					case 3: // Misc
						makeTitle("Misc");
						ImGui::Checkbox(xorstr("Show Fov Circle"), &Settings::ShowFovCircle);
						ImGui::Checkbox(xorstr("Rainbow Mode"), &Settings::RainbowMode);
						break;
					case 4: // Config
						makeTitle("Config");
						ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 6, ImGui::GetCursorPosY() + 6));
						ImGui::Checkbox("Menus beside", &G->MenusBeside);
						break;
					case 5: // Profile
						makeTitle("Profile");
						ImGui::Text(" Coming Soon");
						break;
					case 6: // Anticheat
						makeTitle("AntiCheat");
						ImGui::Text(" Shit Usermode");
						break;
					case 7: // About
						makeTitle("About");
						ImGui::Text(" Made by:");
						ImGui::Text(" android#1337");
						ImGui::Text(" Ware#7294");
						break;
					}
				}
				ImGui::PopID();
				ImGui::End();
			}
		}
	}
	SettingsColor::FovColor = { SettingsColor::FovColor_float[0], SettingsColor::FovColor_float[1], SettingsColor::FovColor_float[2], SettingsColor::FovColor_float[3] };
	SettingsColor::ESPBox = { SettingsColor::ESPBox_float[0], SettingsColor::ESPBox_float[1], SettingsColor::ESPBox_float[2], SettingsColor::ESPBox_float[3] };
	SettingsColor::ESPLines = { SettingsColor::ESPLines_float[0], SettingsColor::ESPLines_float[1], SettingsColor::ESPLines_float[2], SettingsColor::ESPLines_float[3] };
	SettingsColor::ESPNames = { SettingsColor::ESPNames_float[0], SettingsColor::ESPNames_float[1], SettingsColor::ESPNames_float[2], SettingsColor::ESPNames_float[3] };
	SettingsColor::ESPDistance = { SettingsColor::ESPDistance_float[0], SettingsColor::ESPDistance_float[1], SettingsColor::ESPDistance_float[2], SettingsColor::ESPDistance_float[3] };
}
void Menu::Theme()
{
	ImGuiStyle& Style = ImGui::GetStyle();
	auto Color = Style.Colors;
	Style.WindowMinSize = ImVec2(245, 375);
	Style.WindowBorderSize = 0;
	Style.ChildRounding = 0;
	Style.FrameRounding = 0;
	Style.ScrollbarRounding = 0;
	Style.GrabRounding = 0;
	Style.PopupRounding = 0;
	Style.WindowRounding = 0;
	Style.WindowPadding = ImVec2(0, 0);
	Color[ImGuiCol_WindowBg] = ImColor(18, 18, 18, 255);
	Color[ImGuiCol_FrameBg] = ImColor(31, 31, 31, 255);
	Color[ImGuiCol_FrameBgActive] = ImColor(41, 41, 41, 255);
	Color[ImGuiCol_FrameBgHovered] = ImColor(41, 41, 41, 255);
	Color[ImGuiCol_Button] = ImColor(29, 29, 29, 255);
	Color[ImGuiCol_ButtonActive] = ImColor(32, 32, 32, 255);
	Color[ImGuiCol_ButtonHovered] = ImColor(36, 36, 36, 255);
	Color[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
	Color[ImGuiCol_Separator] = ImColor(36, 36, 36, 255);
	Color[ImGuiCol_ResizeGrip] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripActive] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ResizeGripHovered] = ImColor(30, 30, 30, 255);
	Color[ImGuiCol_ChildBg] = ImColor(26, 26, 26, 255);
	Color[ImGuiCol_ScrollbarBg] = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrab] = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_ScrollbarGrabActive] = ImColor(24, 24, 24, 255);
	Color[ImGuiCol_Header] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderActive] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_HeaderHovered] = ImColor(39, 39, 39, 255);
	Color[ImGuiCol_CheckMark] = ImColor(0, 250, 112, 255);
	Color[ImGuiCol_SliderGrab] = ImColor(0, 250, 112);
	Color[ImGuiCol_SliderGrabActive] = ImColor(0, 250, 112);
}