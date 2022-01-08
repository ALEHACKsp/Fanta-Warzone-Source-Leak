#pragma once
bool FirstTime = true;

void mousemove(float tarx, float tary, float X, float Y)
{
	float ScreenCenterX = (X / 2);
	float ScreenCenterY = (Y / 2);
	float TargetX = 0;
	float TargetY = 0;

	if (tarx != 0)
	{
		if (tarx > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - tarx);
			TargetX /= G->AimbotSmooth;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (tarx < ScreenCenterX)
		{
			TargetX = tarx - ScreenCenterX;
			TargetX /= G->AimbotSmooth;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (tary != 0)
	{
		if (tary > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - tary);
			TargetY /= G->AimbotSmooth;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (tary < ScreenCenterY)
		{
			TargetY = tary - ScreenCenterY;
			TargetY /= G->AimbotSmooth;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
}

void DrawBox(float X, float Y, float W, float H, const ImU32& color)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), ImGui::GetColorU32(color));
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color));
}

void ReadAddresses()
{
	while (true) 
	{
		Addresses::INFO = GetClientInfo();
		Addresses::BASE = GetClientBase(Addresses::INFO);
		Addresses::REFDEF = GetRefDef();
		Addresses::NAMES = GetNameList();
		Sleep(15000);
	}
}

void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness) 
{
	float lineW = (W / 3);
	float lineH = (H / 5);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

float colcol_red = 1.;
float colcol_green = 0;
float colcol_blue = 0;
float colcol_speed = -4.0;

void ColorChange()
{
	static float Color[3];
	static DWORD Tickcount = 0;
	static DWORD Tickcheck = 0;
	ImGui::ColorConvertRGBtoHSV(colcol_red, colcol_green, colcol_blue, Color[0], Color[1], Color[2]);
	if (GetTickCount() - Tickcount >= 1)
	{
		if (Tickcheck != Tickcount)
		{
			Color[0] += 0.001f * colcol_speed;
			Tickcheck = Tickcount;
		}
		Tickcount = GetTickCount();
	}
	if (Color[0] < 0.0f) Color[0] += 1.0f;
	ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], colcol_red, colcol_green, colcol_blue);
	SettingsColor::RainbowColorCool = ImColor((int)(colcol_red * 255), (int)(colcol_green * 255), (int)(colcol_blue * 255), 255);
}
static void DrawLineImGui(int x1, int y1, int x2, int y2, RGBA color, int thickness)
{
	if (x2 != 0 && y2 != 0)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), thickness);
	}
}
static void FilledRectangle(int x, int y, int w, int h, RGBA color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color.R / 255.0, color.G / 255.0, color.B / 255.0, color.A / 255.0)), 0, 0);
}
RGBA GetColorFromHP(float Health)
{
	RGBA Color;
	Color.G = (255 * Health) / 127;
	Color.R = 255 - Color.G;
	Color.B = 0;
	Color.A = 255;
	return Color;
}
void SideHealthBar(int x, int y, int height, int health, int shield, RGBA ColHealth, bool shieldbar, bool healthbar)
{
	int box_h = (height * health) / 127;

	if (healthbar)
	{
		//FilledRectangle(x + 13 + 1, y, 4 + 1, height, RGBA{ 0, 0, 0, 255 });
		FilledRectangle(x - 3 + 1, y, 2 - 1, height, RGBA{ 0, 0, 0, 255 });
		FilledRectangle(x - 3, y, 2, box_h, ColHealth);
	}
}
float Distance3D(Vector3 point1, Vector3 point2)
{
	float distance = sqrt((point1.x - point2.x) * (point1.x - point2.x) +
		(point1.y - point2.y) * (point1.y - point2.y) +
		(point1.z - point2.z) * (point1.z - point2.z));
	return distance;
}

void DrawBone(Vector3 from, Vector3 to, Vector3 m_location, Vector3 LocalPos, refdef_t RefDef)
{
	if (Distance3D(m_location, from) > 118)
		return;

	if (Distance3D(m_location, to) > 118)
		return;

	if (Distance3D(from, to) > 39)
		return;

	Vector2 W2S_from = Framework->WorldToScreen(from, LocalPos, RefDef.width, RefDef.height, RefDef.view.tanHalfFov, RefDef.view.axis);
	if (W2S_from.x == 0 or W2S_from.y == 0)
		return;

	Vector2 W2S_to = Framework->WorldToScreen(to, LocalPos, RefDef.width, RefDef.height, RefDef.view.tanHalfFov, RefDef.view.axis);
	if (W2S_to.x == 0 or W2S_to.y == 0)
		return;

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(W2S_from.x, W2S_from.y), ImVec2(W2S_to.x, W2S_to.y), ImColor(255, 0, 0));
}


bool ActorLoop() 
{
	while (true) 
	{
		if (Settings::RainbowMode)
		{
			ColorChange();
		}

		if (FirstTime)
		{
			No_Define::BaseAddress = (uintptr_t)GetModuleHandleA("ModernWarfare.exe");

			No_Define::PEB = __readgsqword(0x60);
			Addresses::INFO = GetClientInfo();
			Addresses::BASE = GetClientBase(Addresses::INFO);
			Addresses::REFDEF = GetRefDef();
			Addresses::NAMES = GetNameList();
			std::thread ReadAddressesThread(ReadAddresses);	ReadAddressesThread.detach();
			FirstTime = false;
		}
		if (!Addresses::BASE || !Addresses::NAMES) return false;
		Addresses::BONE_BASE = decryption::DecryptBoneBase();
		Addresses::VISIBLE = GetVisibleBase(No_Define::BaseAddress);
		Vector3 LocalPlayerPosition = Framework->GetLocalPlayerPosition();
		refdef_t RefDef = *(refdef_t*)(Addresses::REFDEF);

		Vector2 BottomPos_W2S, HeadPos_W2S, PelvisPos_W2S;
		Player* LocalActor = Player::GetLocalActor();
		float closestDistance = FLT_MAX;
		Player* closestActor = NULL;
		for (int i = 0; i < 155; i++)
		{
			Player* CurrentActor = Player::GetCurrentActor(i);
			bool Is_Visible = CurrentActor->isVisible();
			const auto bone_index = decryption::DecryptBoneIndex(No_Define::BaseAddress, i);
			if (CurrentActor->TeamID() == LocalActor->TeamID()) 
				continue;

			if (IsValidPointer(CurrentActor) and !CurrentActor->isDead())
			{
				NameEntry Name_Entry = CurrentActor->GetNameEntry();

				if (std::string(Name_Entry.name).length() > 0) {
					Vector3 Bottom_No_W2S = CurrentActor->GetBottomPos();
					Vector3 Head_No_W2S = Bottom_No_W2S + Vector3(0.0, 0.0, 58.0);
					int Distance = LocalPlayerPosition.Distance(Bottom_No_W2S) / 40;

					if (Distance < Settings::ESP_MaxDistance) 
					{
						HeadPos_W2S = Framework->WorldToScreen(Head_No_W2S, LocalPlayerPosition, RefDef.width, RefDef.height, RefDef.view.tanHalfFov, RefDef.view.axis);
						BottomPos_W2S = Framework->WorldToScreen(Bottom_No_W2S, LocalPlayerPosition, RefDef.width, RefDef.height, RefDef.view.tanHalfFov, RefDef.view.axis);
						PelvisPos_W2S = Vector2(HeadPos_W2S.x, HeadPos_W2S.y + abs(HeadPos_W2S.y - BottomPos_W2S.y) / 2);

						float PawnHeight = abs(HeadPos_W2S.y - BottomPos_W2S.y);
						//////////////////////////////////////////////////// A I M B O T ////////////////////////////////////////////////////
						Vector2 AimHead = Vector2(HeadPos_W2S.x, HeadPos_W2S.y + PawnHeight / 8);
						Vector2 sdist = Vector2(AimHead.x - (No_Renderer_Define::Width / 2), AimHead.y - (No_Renderer_Define::Height / 2));
						auto screendist = sqrtf(sdist.x * sdist.x + sdist.y * sdist.y);
						if (screendist < Settings::FovCircleValue and screendist < closestDistance) 
						{
							closestDistance = screendist;
							closestActor = CurrentActor;
						}




						const auto bone_index = decryption::DecryptBoneIndex(No_Define::BaseAddress, i);
						Player* CurrentActor = Player::GetCurrentActor(i);
						Vector3 Bottom_No_W2S = CurrentActor->GetBottomPos();
						Vector3 LocalPlayerPosition = Framework->GetLocalPlayerPosition();
						auto RefDef = *(refdef_t*)(Addresses::REFDEF);



						if (Framework->IsInScreen(HeadPos_W2S, BottomPos_W2S, No_Renderer_Define::Width, No_Renderer_Define::Height))
						{
							float PawnHeight = abs(HeadPos_W2S.y - BottomPos_W2S.y);
							float PawnWidth = PawnHeight * 0.55;
							//////////////////////////////////////////////////// E S P ////////////////////////////////////////////////////
							//Box
							if (Settings::ESP_Box)
							{
								if (Settings::ESP_Box_Type == 0) {
									DrawBox(HeadPos_W2S.x - (PawnWidth / 2), HeadPos_W2S.y, PawnWidth, PawnHeight, Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPBox);
								}
								else if (Settings::ESP_Box_Type == 1) {
									DrawCorneredBox(HeadPos_W2S.x - (PawnWidth / 2), HeadPos_W2S.y, PawnWidth, PawnHeight, Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPBox, 2.0f);
								}
							}
							if (Settings::Skeleton)
							{
								Vector3 bone_head = decryption::GetBonePosition(bone_index, 7);
								Vector3 bone_2 = decryption::GetBonePosition(bone_index, 2);
								Vector3 bone_6 = decryption::GetBonePosition(bone_index, 6);
								Vector3 bone_6_10 = decryption::GetBonePosition(bone_index, 10);
								Vector3 bone_10_11 = decryption::GetBonePosition(bone_index, 11); //left hand
								Vector3 bone_11_12 = decryption::GetBonePosition(bone_index, 12);
								Vector3 bone_6_14 = decryption::GetBonePosition(bone_index, 14);
								Vector3 bone_14_15 = decryption::GetBonePosition(bone_index, 15); //right hand
								Vector3 bone_15_16 = decryption::GetBonePosition(bone_index, 16);
								Vector3 bone_2_18 = decryption::GetBonePosition(bone_index, 18);
								Vector3 bone_18_19 = decryption::GetBonePosition(bone_index, 19); //left foot
								Vector3 bone_2_22 = decryption::GetBonePosition(bone_index, 22);
								Vector3 bone_22_23 = decryption::GetBonePosition(bone_index, 23); //right foot
								DrawBone(bone_6, bone_head, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_6, bone_6_10, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_6_10, bone_10_11, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_10_11, bone_11_12, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_6, bone_6_14, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_6_14, bone_14_15, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_14_15, bone_15_16, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_2, bone_6, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_2, bone_2_18, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_2_18, bone_18_19, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_2, bone_2_22, Bottom_No_W2S, LocalPlayerPosition, RefDef);
								DrawBone(bone_2_22, bone_22_23, Bottom_No_W2S, LocalPlayerPosition, RefDef);
							}
							if (Settings::Health)
							{
								int _Health = Name_Entry.health;
								SideHealthBar(HeadPos_W2S.x - (PawnWidth / 2), HeadPos_W2S.y, PawnHeight, _Health, 0, GetColorFromHP(_Health), false, true);
							}
							//Lines
							if (Settings::ESP_Line)
							{
								if (Settings::ESP_Line_Type == 0)
								{
									ImGui::GetOverlayDrawList()->AddLine(ImVec2(No_Renderer_Define::Width / 2, 0), ImVec2(PelvisPos_W2S.x, PelvisPos_W2S.y), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPLines);
								}
								else if (Settings::ESP_Line_Type == 1)
								{
									ImGui::GetOverlayDrawList()->AddLine(ImVec2(No_Renderer_Define::Width / 2, No_Renderer_Define::Height / 2), ImVec2(PelvisPos_W2S.x, PelvisPos_W2S.y), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPLines);
								}
								else if (Settings::ESP_Line_Type == 2)
								{
									ImGui::GetOverlayDrawList()->AddLine(ImVec2(No_Renderer_Define::Width / 2, No_Renderer_Define::Height), ImVec2(PelvisPos_W2S.x, PelvisPos_W2S.y), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPLines);
								}
							}
							//Names
							if ((Settings::ESP_Names or Settings::ESP_Distance) or (Settings::ESP_Names and Settings::ESP_Distance)) {
								std::string null = "";
								std::string Distance_String = null + "[" + std::to_string(Distance) + "]";
								std::string Names_String = null + "[" + (Name_Entry.name) + "]";
								int Distance_Width = ImGui::CalcTextSize(Distance_String.c_str()).x, Distance_Height = ImGui::CalcTextSize(Distance_String.c_str()).y;
								int Names_Width = ImGui::CalcTextSize(Names_String.c_str()).x, Names_Height = ImGui::CalcTextSize(Names_String.c_str()).y;


								if (!Settings::ESP_Names and Settings::ESP_Distance) {
									ImGui::GetOverlayDrawList()->AddText(ImVec2(HeadPos_W2S.x - (Distance_Width / 2), BottomPos_W2S.y + Distance_Height / 2), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPDistance, Distance_String.c_str());
								}

								if (Settings::ESP_Names and !Settings::ESP_Distance) {
									ImGui::GetOverlayDrawList()->AddText(ImVec2(HeadPos_W2S.x - (Names_Width / 2), BottomPos_W2S.y + Names_Height / 2), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPNames, Names_String.c_str());
								}

								if (Settings::ESP_Names and Settings::ESP_Distance) {
									ImGui::GetOverlayDrawList()->AddText(ImVec2(HeadPos_W2S.x - (Distance_Width / 2), BottomPos_W2S.y + Distance_Height / 2), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPDistance, Distance_String.c_str());
									ImGui::GetOverlayDrawList()->AddText(ImVec2(HeadPos_W2S.x - (Names_Width / 2), BottomPos_W2S.y + Distance_Height + Names_Height / 2), Settings::RainbowMode ? SettingsColor::RainbowColorCool : SettingsColor::ESPNames, Names_String.c_str());
								}
							}
						}





						if (Settings::Aimbot)
						{
							Vector3 bone_head = decryption::GetBonePosition(bone_index, 5);
							Vector2 draw_head = Framework->WorldToScreen(bone_head, LocalPlayerPosition, RefDef.width, RefDef.height, RefDef.view.tanHalfFov, RefDef.view.axis);
							int distx = draw_head.x - (No_Renderer_Define::Width / 2);
							int disty = draw_head.y - (No_Renderer_Define::Height / 2);
							auto dist = sqrtf(distx * distx + disty + disty);
							if (GetAsyncKeyState(VK_RBUTTON) && draw_head.x > 0 && draw_head.y > 0 && dist < Settings::FovCircleValue)
							{
								if (Is_Visible)
								{
									mousemove(draw_head.x, draw_head.y, No_Renderer_Define::Width, No_Renderer_Define::Height);
								}
							}
						}











					}
				}
			}
		}
		Sleep(1);
	}
	return true;
}