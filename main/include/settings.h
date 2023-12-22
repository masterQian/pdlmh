#pragma once

struct SettingsWindow : Window {
	static SettingsWindow* instance;
	Group Tabs[4];
	plus::Record record;
	int CurrentPage = 0; // 当前页面
	static void OpenSettings() noexcept; // 打开设置
	static void Release() noexcept;
};