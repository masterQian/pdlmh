#pragma once
#include <winui.h>
using namespace winui;

inline struct Res {
	struct {
		void(__stdcall* Toast)(int duration, ConstString content) noexcept = nullptr;
	}Function;
	struct {
		Bin* Window{}, * Edit{}, * Button{};
	}Skin;
	struct {
		struct {
			Bin* S16{};
		}MSBlack;
	}Font;
	struct {
		String proxy;
	}Layout;
	bool GroundGlass{};
}res;

inline struct Proxy : Window {
	HMODULE hDll{};
	VDSwitcher vds;
	Switch SB;
	Edit IP, PORT, BLOCK;
	Reg reg;
	COLORREF CurrentColor{};
	volatile bool isListen = false;
	volatile bool isOpen = false;
	void Open() noexcept;
	void Reset() noexcept { id = 0; }
}proxy;