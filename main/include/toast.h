#pragma once

struct ToastWindow : Window {
	static ToastWindow* instance;
	int duration;
	String content;
	int mode;
	Clock clock;
	constexpr ToastWindow(int d, ConstString c) noexcept :
		duration{ d }, content{ c }, mode{ 0 } {}
	static void Release() noexcept;
};

// 弹出提示
void __stdcall Toast(int duration, ConstString content) noexcept;