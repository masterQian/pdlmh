#pragma once
#include <winui.h>
using namespace winui;

inline struct Res {
	struct {
		void(__stdcall* Toast)(int duration, ConstString content) noexcept = nullptr;
	}Function;
	struct {
		Bin* Window{}, * Edit{}, * Choice{}, * Picture{}, * Button{};
	}Skin;
	struct {
		struct {
			Bin* S16{};
		}MSBlack;
	}Font;
	struct {
		String screenshot, settings;
	}Layout;
	bool GroundGlass{};
}res;

inline struct Var {
	HMODULE hDll{};
	CLSID* GUID_JPG{}, * GUID_PNG{}, * GUID_BMP{};
	String CurrentPath;
	String DefaultType;
	String DefaultName;
}var;

inline struct ScreenShot : Window {
	VDSwitcher vds;
	volatile bool isOpen = false;
	Picture picture;
	ClipMonitor monitor;
	void Open() noexcept;
	void Reset() noexcept { id = 0; }
}dlg1;

inline struct Settings : Window {
	VDSwitcher vds;
	volatile bool isOpen = false;
	Edit edit;
	Choice choices[3];
	void Open() noexcept;
	void Reset() noexcept { id = 0; }
	static void ReadSettings() noexcept;
}dlg2;