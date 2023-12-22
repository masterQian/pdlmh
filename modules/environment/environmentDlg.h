#pragma once
#include <winui.h>
using namespace winui;

inline struct Res {
	struct {
		void(__stdcall* Toast)(int duration, ConstString content) noexcept = nullptr;
	}Function;
	struct {
		Bin* Window{}, * IconList{}, * SuperList2{}, * Menu{};
	}Skin;
	struct {
		struct {
			Bin* S16{};
		}MSBlack;
	}Font;
	struct {
		String environment, menu;
	}Layout;
	ByteSet more;
	bool GroundGlass{};
}res;

inline struct EnvDlg : Window {
	HMODULE hDll{};
	VDSwitcher vds;
	SuperList list;
	Menu menu;
	Reg reg1, reg2;
	int cur = 0;
	ICO more;
	std::unordered_map<String, String> data1, data2;
	volatile bool isOpen = false;
	void Open() noexcept;
	void Reset() noexcept { id = 0; }
}env;