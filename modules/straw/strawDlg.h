#pragma once
#include <winui.h>
using namespace winui;

inline struct Res {
	struct {
		void(__stdcall* Toast)(int duration, ConstString content) noexcept = nullptr;
	}Function;
	struct {
		Bin* Window{}, * SuperList2{};
	}Skin;
	struct {
		struct {
			Bin* S16{};
		}MSBlack;
	}Font;
	struct {
		String straw;
	}Layout;
	bool GroundGlass{};
}res;

inline struct Straw : Window {
	HMODULE hDll{};
	VDSwitcher vds;
	SuperList SL;
	Label CL;
	Clock Clk;
	HotKey HK;
	COLORREF CurrentColor{};
	volatile bool isListen = false;
	volatile bool isOpen = false;
	void Open() noexcept;
	void Reset() noexcept { id = 0; }
}straw;