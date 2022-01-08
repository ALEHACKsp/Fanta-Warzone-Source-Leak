#pragma once

bool Draw_Init() 
{
	ImU32 FovColor = ImGui::GetColorU32({ 255, 0, 0, 255 });
	if(Settings::ShowFovCircle)
	ImGui::GetOverlayDrawList()->AddCircle(ImVec2(No_Renderer_Define::Width / 2, No_Renderer_Define::Height / 2), Settings::FovCircleValue, Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::FovColor, 0);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(20, 20), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::FovColor, xorstr("1337Warzone | android#1337 & Ware#7294"));
	return true;
}