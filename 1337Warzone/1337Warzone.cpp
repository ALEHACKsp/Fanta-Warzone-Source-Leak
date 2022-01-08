#include <iostream>
#include <Windows.h>
#include <future>
#include <intrin.h>
#include "no_renderer.h"
#include <csignal>
#include <cstdlib>
#include <signal.h>
#include "xor.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#pragma comment(lib, "d3d12.lib")

#pragma warning(disable : 4996)
using namespace std;


uintptr_t pattern_scan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex = 0)
{
	static auto patternToByte = [](const char* pattern)
	{
		auto       bytes = std::vector<int>{};
		const auto start = const_cast<char*>(pattern);
		const auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else
				bytes.push_back(strtoul((const char*)current, &current, 16));
		}
		return bytes;
	};

	const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

	const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto       patternBytes = patternToByte(sSignature);
	const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

	const auto s = patternBytes.size();
	const auto d = patternBytes.data();

	size_t nFoundResults = 0;

	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;

		for (auto j = 0ul; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			if (nSelectResultIndex != 0)
			{
				if (nFoundResults < nSelectResultIndex)
				{
					nFoundResults++;
					found = false;
				}
				else
					return reinterpret_cast<uintptr_t>(&scanBytes[i]);
			}
			else
				return reinterpret_cast<uintptr_t>(&scanBytes[i]);
		}
	}

	return NULL;
}



uintptr_t DiscordModule;
std::vector<uintptr_t> pCreatedHooksArray;
bool CreateHook(uintptr_t pOriginal, uintptr_t pHookedFunction, uintptr_t pOriginalCall)
{
	static uintptr_t addrCreateHook = NULL;

	if (!addrCreateHook)
		addrCreateHook = pattern_scan(DiscordModule, xorstr("41 57 41 56 56 57 55 53 48 83 EC 68 4D 89 C6 49 89 D7"));

	if (!addrCreateHook)
		return false;

	using CreateHook_t = uint64_t(__fastcall*)(LPVOID, LPVOID, LPVOID*);
	auto fnCreateHook = (CreateHook_t)addrCreateHook;

	return fnCreateHook((void*)pOriginal, (void*)pHookedFunction, (void**)pOriginalCall) == 0 ? true : false;
}

bool EnableHookQue()
{
	static uintptr_t addrEnableHookQueu = NULL;

	if (!addrEnableHookQueu)
		addrEnableHookQueu = pattern_scan(DiscordModule, xorstr("41 57 41 56 41 55 41 54 56 57 55 53 48 83 EC 38 48 ? ? ? ? ? ? 48 31 E0 48 89 44 24 30 BE 01 00 00 00 31 C0 F0 ? ? ? ? ? ? ? 74 2B"));

	if (!addrEnableHookQueu)
		return false;

	using EnableHookQueu_t = uint64_t(__stdcall*)(VOID);
	auto fnEnableHookQueu = (EnableHookQueu_t)addrEnableHookQueu;

	return fnEnableHookQueu() == 0 ? true : false;
}


bool EnableHook(uintptr_t pTarget, bool bIsEnabled)
{
	static uintptr_t addrEnableHook = NULL;

	if (!addrEnableHook)
		addrEnableHook = pattern_scan(DiscordModule, xorstr("41 56 56 57 53 48 83 EC 28 49 89 CE BF 01 00 00 00 31 C0 F0 ? ? ? ? ? ? ? 74"));

	if (!addrEnableHook)
		return false;

	using EnableHook_t = uint64_t(__fastcall*)(LPVOID, bool);
	auto fnEnableHook = (EnableHook_t)addrEnableHook;

	return fnEnableHook((void*)pTarget, bIsEnabled) == 0 ? true : false;
}

BOOL InsertHook(uintptr_t pOriginal, uintptr_t pHookedFunction, uintptr_t pOriginalCall)
{
	bool bAlreadyCreated = false;
	for (auto _Hook : pCreatedHooksArray)
	{
		if (_Hook == pOriginal)
		{
			bAlreadyCreated = true;
			break;
		}
	}

	if (!bAlreadyCreated)
		bAlreadyCreated = CreateHook(pOriginal, pHookedFunction, pOriginalCall);

	if (bAlreadyCreated)
		if (EnableHook(pOriginal, true))
			if (EnableHookQue())
				return true;

	return false;
}

typedef HRESULT(STDMETHODCALLTYPE* tPresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

namespace ogr_function
{
	tPresent Present;
}

HRESULT STDMETHODCALLTYPE hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!pSwapChain)
		return ogr_function::Present(pSwapChain, SyncInterval, Flags);


	ImFont* main_font = imgui::start(
		static_cast<IDXGISwapChain3*>(pSwapChain),
		reinterpret_cast<ID3D12CommandQueue*>(*(QWORD*)(cod_data::image_base + decrypt::D3D12_CommandQueue_OFFSET)),
		nullptr,
		20.0f);

	imgui::imgui_frame_header();

	//esp
	imgui::imgui_no_border(draw::esp, main_font);

	//ui
	draw::ui();

	return imgui::imgui_frame_end(pSwapChain, SyncInterval, Flags);
}

void hook_present()
{
	uintptr_t base_address = (uintptr_t)GetModuleHandle(0);
	uintptr_t swap_chain_base_address = *(uintptr_t*)(base_address + decrypt::D3D12_SWAP_CHAIN_OFFSET);

	if (swap_chain_base_address == 0 || *(uintptr_t*)(base_address + decrypt::D3D12_CommandQueue_OFFSET) == 0) {
		MessageBoxA(0, "FuckError", 0, 0);
	}

	//hooked Present
	ogr_function::Present = VTManager::modify<type::tPresent>((void*)swap_chain_base_address, 8, hooker::hkPresent); //vt hook
}

int mana()
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);

    std::cout << "\n";
    std::cout << xorstr("  Initializing..") << "\n\n";

    //Renderer_Init();

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) {
        mana();
    }

    return TRUE;
}