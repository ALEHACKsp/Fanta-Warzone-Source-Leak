#include <iostream>
#include <Windows.h>
#include <future>
#include <string>
#include <vector>
#include <tlhelp32.h>
#include <d3d9.h>
#include <dwmapi.h>
#include <intrin.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dwmapi.lib")
#include "no_renderer/imgui/imgui.h"
#include "no_renderer/imgui/imgui_impl_dx9.h"
#include "no_renderer/imgui/imgui_impl_win32.h"
#include "xor.h"
#include "no_renderer.h"
#include "no_define.h"
#include "no_utils.h"
#include "no_driver.h"
#include "no_vectors.h"
#include "no_offsets.h"
#include "no_framework.h"
#include "no_loop.h"
#include "no_draw.h"
#include "no_menu.h"
#include "font.h"
#include "icons.h"
#define DIRECTINPUT_VERSION 0x0800
#pragma warning(disable : 4996)
using namespace std;

int Draw_Width = GetSystemMetrics(SM_CXSCREEN);
int Draw_Height = GetSystemMetrics(SM_CYSCREEN);
IDirect3D9Ex* Draw_pObject = NULL;
IDirect3DDevice9Ex* Draw_pDevice = NULL;
D3DPRESENT_PARAMETERS Draw_pParams = { NULL };
HWND DrawOverlayHWND;
bool FirstTimeOnly = true;
static bool ShowMenuorNot;
bool OneTimeFont;

HRESULT Renderer_Init()
{
	static const MARGINS Margin = { -1 };
	static MSG Message = { NULL };
	std::cout << xorstr("  FindWindow..") << "\n\n";

	DrawOverlayHWND = FindWindow(xorstr("GDI+ Hook Window Class"), NULL);
	std::cout << xorstr("  ShowWindow..") << "\n\n";

	ShowWindow(DrawOverlayHWND, SW_SHOW);
	std::cout << xorstr("  DwmExtendFrameIntoClientArea..") << "\n\n";

	DwmExtendFrameIntoClientArea(DrawOverlayHWND, &Margin);
	std::cout << xorstr("  SetWindowLong..") << "\n\n";

	SetWindowLong(DrawOverlayHWND, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	std::cout << xorstr("  ShowWindow..") << "\n\n";

	ShowWindow(DrawOverlayHWND, SW_SHOW);
	std::cout << xorstr("  UpdateWindow..") << "\n\n";

	UpdateWindow(DrawOverlayHWND);
	std::cout << xorstr("  SetWindowPos..") << "\n\n";

	SetWindowPos(DrawOverlayHWND, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	std::cout << xorstr("  Direct3DCreate9Ex..") << "\n\n";

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &Draw_pObject))) { exit(3); }
	std::cout << xorstr("  Draw_pParams..") << "\n\n";

	D3DPRESENT_PARAMETERS Draw_pParams = { 0 };
	Draw_pParams.Windowed = TRUE;
	Draw_pParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Draw_pParams.hDeviceWindow = DrawOverlayHWND;
	Draw_pParams.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	Draw_pParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	Draw_pParams.BackBufferWidth = Draw_Width;
	Draw_pParams.BackBufferHeight = Draw_Height;
	Draw_pParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	Draw_pParams.EnableAutoDepthStencil = TRUE;
	Draw_pParams.AutoDepthStencilFormat = D3DFMT_D16;
	Draw_pParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	std::cout << xorstr("  CreateDeviceEx..") << "\n\n";

	if (FAILED(Draw_pObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DrawOverlayHWND, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Draw_pParams, 0, &Draw_pDevice))) {
		Draw_pObject->Release();
		exit(4);
	}
	std::cout << xorstr("  CreateContext..") << "\n\n";

	ImGui::CreateContext();
	std::cout << xorstr("  ImGui_ImplWin32_Init..") << "\n\n";

	ImGui_ImplWin32_Init(DrawOverlayHWND);
	std::cout << xorstr("  ImGui_ImplDX9_Init..") << "\n\n";

	ImGui_ImplDX9_Init(Draw_pDevice);
	std::cout << xorstr("  Draw_pObjectrelease..") << "\n\n";

	Draw_pObject->Release();
	std::cout << xorstr("  ZeroMemory..") << "\n\n";

	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));
	while (Message.message != WM_QUIT)
	{
		std::cout << xorstr("  PeekMessage..") << "\n\n";

		if (PeekMessage(&Message, DrawOverlayHWND, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		ImGuiIO& io = ImGui::GetIO();
		if (!OneTimeFont)
		{
			io.IniFilename = nullptr;
			io.LogFilename = nullptr;
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
			ImFontConfig icons_config;
			io.IniFilename = nullptr;
			io.LogFilename = nullptr;
			icons_config.MergeMode = true;
			icons_config.PixelSnapH = true;
			icons_config.OversampleH = 3;
			icons_config.OversampleV = 3;
			ImFontConfig CustomFont;
			CustomFont.FontDataOwnedByAtlas = false;
			std::cout << xorstr("  AddFontFromMemoryTTF..") << "\n\n";

			io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 19.5, &CustomFont);
			std::cout << xorstr("  AddFontFromMemoryCompressedTTF..") << "\n\n";

			io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 18.5f, &icons_config, icons_ranges);
			std::cout << xorstr("  AddFontDefault..") << "\n\n";

			io.Fonts->AddFontDefault();
			OneTimeFont = true;
		}

		std::cout << xorstr("  GetCursorPos..") << "\n\n";

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x;
		io.MousePos.y = p.y;
		if (GetAsyncKeyState(VK_LBUTTON)) 
		{
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].y = io.MousePos.y;
		}
		else 
		{
			io.MouseDown[0] = false;
		}
		std::cout << xorstr("  FirstTimeOnly..") << "\n\n";

		if (FirstTimeOnly)
		{
			Draw_pParams.BackBufferWidth = No_Renderer_Define::Width;
			Draw_pParams.BackBufferHeight = No_Renderer_Define::Height;
			SetWindowPos(DrawOverlayHWND, (HWND)0, 0, 0, Draw_Width, Draw_Height, SWP_NOREDRAW);
			Draw_pDevice->Reset(&Draw_pParams);
		}
		std::cout << xorstr("  ImGui_ImplDX9_NewFrame..") << "\n\n";

		ImGui_ImplDX9_NewFrame();
		std::cout << xorstr("  ImGui_ImplWin32_NewFrame..") << "\n\n";

		ImGui_ImplWin32_NewFrame();
		std::cout << xorstr("  NewFrame..") << "\n\n";

		ImGui::NewFrame();
		std::cout << xorstr("  Theme..") << "\n\n";

		Menu::Theme();
		{
			std::cout << xorstr("  Render..") << "\n\n";

			Menu::Render();
		}
		std::cout << xorstr("  EndFrame..") << "\n\n";

		ImGui::EndFrame();

		std::cout << xorstr("  Draw_Init..") << "\n\n";

		Draw_Init();

		std::cout << xorstr("  ActorLoop..") << "\n\n";

		ActorLoop();


		ImGui::EndFrame();
		Draw_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
		if (Draw_pDevice->BeginScene() >= 0) {
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			Draw_pDevice->EndScene();
		}
		HRESULT result = Draw_pDevice->Present(NULL, NULL, NULL, NULL);
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	if (Draw_pDevice != NULL)
	{
		Draw_pDevice->EndScene();
		Draw_pDevice->Release();
	}
	if (Draw_pObject != NULL) {
		Draw_pObject->Release();
	}
	DestroyWindow(DrawOverlayHWND);
	return Message.wParam;
	return S_OK;
}