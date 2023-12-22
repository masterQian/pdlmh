#include "../include/pdlmh.h"

// 设置单选框回调
Result __stdcall SettingsRadioCallBack(ID id, Event msg, Arg, Arg, Arg, Arg) {
	if (msg == Events::Control::LClick) {
		static Mutex mutex;
		if (mutex.lock()) {
			String value = Radio(id).Name();
			var->Config.SearchEngine = StringTo<INT>(value);
			// [写磁盘]
			Ini ini; ini.LoadFile(Con::Path_Config_Settings);
			ini[LS::IniSettings][LS::IniSearchEngine] = value;
			ini.SaveFile(Con::Path_Config_Settings);
			mutex.unlock();
		}
	}
	return 0;
}

// 设置复选框回调
Result __stdcall SettingsChoiceCallBack(ID id, Event msg, Arg, Arg, Arg, Arg) {
	if (msg == Events::Control::LClick) {
		static Mutex mutex;
		Choice choice = Choice(id);
		if (mutex.lock()) {
			String group = Group(choice.Parent()).Name();
			bool checked = choice.Select();
			Ini ini; ini.LoadFile(Con::Path_Config_Settings);
			if (group == LS::IniTreeFilter) {
				auto value = StringTo<int>(choice.Name());
				if (checked) var->Config.FolderTreeFilter |= value;
				else var->Config.FolderTreeFilter &= ~value;
				// [写磁盘]
				ini[LS::IniSettings][LS::IniTreeFilter] = ToString(var->Config.FolderTreeFilter);
			}
			else {
				String name = choice.Name();
				if (name == LS::IniAutoStart) {
					var->Config.AutoStart = checked;
					Reg reg(Reg::LocalMachine, LS::RegAutoStart);
					if (checked) reg.SetStringValue(LS::SoftwareName, Environment::CurrentFullName);
					else reg.DeleteKey(LS::SoftwareName);
					reg.Close();
					// [写磁盘]
					ini[LS::IniSettings][LS::IniAutoStart] = ToString((int)checked);
				}
				else if (name == LS::IniListWave) {
					var->Config.ListWave = checked;
					// [写磁盘]
					ini[LS::IniSettings][LS::IniListWave] = ToString((int)checked);
				}
				else if (name == LS::IniGroundGlass) {
					var->Config.GroundGlass = checked;
					mainWindow->GroundGlass(checked);
					SettingsWindow::instance->GroundGlass(checked);
					// [写磁盘]
					ini[LS::IniSettings][LS::IniGroundGlass] = ToString((int)checked);
				}
			}
			ini.SaveFile(Con::Path_Config_Settings);
			mutex.unlock();
		}
	}
	return 0;
}

// 设置滑块条回调
Result __stdcall SettingsSliderCallBack(ID id, Event msg, Arg value, Arg, Arg, Arg) {
	if (msg == Events::Slider::PositionChange) {
		static Mutex mutex;
		if (mutex.lock()) {
			var->Config.EffectSpeed = value;
			// [写磁盘]
			Ini ini; ini.LoadFile(Con::Path_Config_Settings);
			ini[LS::IniSettings][LS::IniEffectSpeed] = ToString(value);
			ini.SaveFile(Con::Path_Config_Settings);
			mutex.unlock();
		}
	}
	return 0;
}

// 设置调色板回调
Result __stdcall SettingsColorPickCallBack(ID id, Event msg, Arg value, Arg, Arg, Arg) {
	if (msg == Events::ColorPick::ColorChange) {
		static Mutex mutex;
		if (mutex.lock()) {
			var->Config.BackGroundColor = Color::ARGB_RGB(value);
			auto bs = Color::SolidBitmap(var->Config.BackGroundColor);
			var->BackGroundImage = Bin(bs.data(), bs.size());
			var->NewSkinWindow = SkinWindow(mainWindow->Skin()).BackGround(var->BackGroundImage).Create();
			mainWindow->Skin(var->NewSkinWindow);
			SettingsWindow::instance->Skin(var->NewSkinWindow);
			// [写磁盘]
			Ini ini; ini.LoadFile(Con::Path_Config_Settings);
			ini[LS::IniSettings][LS::IniBackGroundColor] = ToString(var->Config.BackGroundColor);
			ini.SaveFile(Con::Path_Config_Settings);
			mutex.unlock();
		}
	}
	return 0;
}

// 切换缓动回调
Result __stdcall SettingsGradientCallBack(ID, Event msg, Arg id, Arg result, Arg, Arg data) {
	int New = SeparateHigh(data), Old = SeparateLow(data);
	switch (msg) {
	case Events::Gradient::Begin: {
		if (New == 2) SettingsWindow::instance->record.Start(4000);
		else SettingsWindow::instance->record.Stop();
		SettingsWindow::instance->Tabs[New].Visual(true);
		break;
	}
	case Events::Gradient::Result: {
		if (id == 0) SettingsWindow::instance->Tabs[Old].Left(result);
		else SettingsWindow::instance->Tabs[New].Left(result);
		break;
	}
	case Events::Gradient::End: SettingsWindow::instance->Tabs[Old].Visual(false); break;
	}
	return 0;
}

// 切换版面
void SettingsSelectTab(int Old, int New) noexcept {
	if (Old != New) {
		SettingsWindow::instance->CurrentPage = New;
		Gradient::Start(SettingsGradientCallBack, Gradient::Task().Add(150, 610,
			Gradient::Mode::CircleInOut).Add(610, 150, Gradient::Mode::CircleInOut),
			40 / var->Config.EffectSpeed, false, MergeInt(New, Old));
	}
}

// 设置Tab回调
Result __stdcall SettingsTabCallBack(ID id, Event msg, Arg index, Arg, Arg, Arg) {
	if (msg == Events::IconList::ItemLCLick) {
		static Mutex mutex;
		if (mutex.lock()) {
			SettingsSelectTab(SettingsWindow::instance->CurrentPage, index);
			mutex.unlock();
		}
	}
	return 0;
}

// 设置窗口回调
Result __stdcall SettingsCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	auto& settingsWindow = *SettingsWindow::instance;
	switch (msg) {
	case Events::Window::Create: {
		auto& v1 = var->Config.SearchEngine;
		auto& v2 = var->Config.FolderTreeFilter;
		VDSwitcher vds = {
			{ L"Position.Left", (Memory)((Screen::Width >> 1) - 315) },
			{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 235) },
			{ L"Image.Icon", res->Image.Icon },
			{ L"Skin.Window", var->NewSkinWindow },
			{ L"Skin.Group", res->Skin.Group },
			{ L"Skin.Slider", res->Skin.Slider },
			{ L"Skin.ColorPick", res->Skin.ColorPick },
			{ L"Skin.Edit", res->Skin.Edit },
			{ L"Skin.Choice", res->Skin.Choice },
			{ L"Skin.IconList", res->Skin.IconList },
			{ L"Color.White", (Memory)Color::White },
			{ L"Text.About", &res->Data.About },
			{ L"Font.MSBlack.SL14", res->Font.MSBlack.SL14 },
			{ L"Font.MSBlack.S16", res->Font.MSBlack.S16 },
			{ L"CallBack.SettingsTab", SettingsTabCallBack },
			{ L"CallBack.SettingsRadio", SettingsRadioCallBack },
			{ L"CallBack.SettingsChoice", SettingsChoiceCallBack },
			{ L"CallBack.SettingsSlider", SettingsSliderCallBack },
			{ L"CallBack.SettingsColorPick", SettingsColorPickCallBack },
			{ L"Value.AutoStart", (Memory)var->Config.AutoStart },
			{ L"Value.ListWave", (Memory)var->Config.ListWave },
			{ L"Value.EffectSpeed", (Memory)var->Config.EffectSpeed },
			{ L"Value.BackGroundColor", (Memory)Color::RGB_ARGB(var->Config.BackGroundColor) },
			{ L"Value.SearchEngine.Null", (Memory)(v1 == 0) },
			{ L"Value.SearchEngine.Baidu", (Memory)(v1 == 1) },
			{ L"Value.SearchEngine.Bing", (Memory)(v1 == 2) },
			{ L"Value.SearchEngine.Google", (Memory)(v1 == 3) },
			{ L"Value.FolderTreeFilter.System", (Memory)((v2 & 4) == 4) },
			{ L"Value.FolderTreeFilter.Hide", (Memory)((v2 & 2) == 2) },
			{ L"Value.FolderTreeFilter.Normal", (Memory)((v2 & 32) == 32) },
			{ L"Value.FolderTreeFilter.Folder", (Memory)((v2 & 16) == 16) },
			{ L"Value.FolderTreeFilter.ReadOnly", (Memory)((v2 & 1) == 1) },
			{ L"Value.GroundGlass", (Memory)var->Config.GroundGlass },
			{ L"Value.NewUpdate", &res->Data.Update },
		};
		// 反射布局
		Layout::InflateWindow(settingsWindow, res->Layout.Settings, vds);
		// 初始化Tab栏
		settingsWindow.CurrentPage = 0;
		settingsWindow.Tabs[0] = (Group)settingsWindow(L"Normal");
		settingsWindow.Tabs[1] = (Group)settingsWindow(L"Extends");
		settingsWindow.Tabs[2] = (Group)settingsWindow(L"About");
		settingsWindow.Tabs[3] = (Group)settingsWindow(L"Update");
		// 初始化关于
		settingsWindow.record = (plus::Record)settingsWindow(L"About")(L"Record");
		break;
	}
	case Events::Window::Destroy: {
		SettingsWindow::instance->record.Stop();
		SettingsWindow::instance = nullptr;
		break;
	}
	}
	return 0;
}

SettingsWindow* SettingsWindow::instance = nullptr;

void SettingsWindow::OpenSettings() noexcept {
	if (!SettingsWindow::instance) {
		SettingsWindow settingsWindow;
		SettingsWindow::instance = &settingsWindow;
		settingsWindow.Start(SettingsCallBack, {}, true, false, true);
	}
}

void SettingsWindow::Release() noexcept {
	if (SettingsWindow::instance) SettingsWindow::instance->Destroy();
}