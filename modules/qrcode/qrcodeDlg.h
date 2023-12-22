#pragma once
#include <winui.h>
using namespace winui;

inline struct Res {
	struct {
		Bin* Window{}, * Edit{}, * Picture{};
	}Skin;
	struct {
		struct {
			Bin* S16{};
		}MSBlack;
	}Font;
	struct {
		String qrcode;
	}Layout;
	CLSID* GUID_JPG{};
	bool GroundGlass{};
}res;

inline struct Qrcode : Window {
	HMODULE hDll{};
	VDSwitcher vds;
	Picture picture;
	volatile bool isOpen = false;
	void Open() noexcept;
	void Reset() noexcept { id = 0; }
}qrcode;