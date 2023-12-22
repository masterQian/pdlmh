#pragma once
#include <winui.h>
using namespace winui;

inline struct Res {
	struct {
		void(__stdcall* Toast)(int duration, ConstString content) noexcept = nullptr;
	}Function;
	struct {
		Bin* Window{}, * Edit{};
	}Skin;
	struct {
		struct {
			Bin* S16{};
		}MSBlack;
	}Font;
	struct {
		String unlock;
	}Layout;
	String CurrentPath;
	bool GroundGlass{};
}res;

inline struct Unlock : Window {
	HMODULE hDll{};
	VDSwitcher vds;
	Edit edit;
	Drag drag;
	volatile bool isOpen = false;
	volatile bool isKill = false;
	void Open() noexcept;
	void Reset() noexcept { id = 0; }
}unlock;