#include "screenshot.h"

void Settings::ReadSettings() noexcept {
	Ini ini; ini.LoadFile(var.CurrentPath + L"config.ini");
	auto& section = ini[L"ScreenShot"];
	var.DefaultType = section[L"DefaultType"];
	if (var.DefaultType.empty()) var.DefaultType = L"jpg";
	var.DefaultName = section[L"DefaultName"];
	if (var.DefaultName.empty()) var.DefaultName = L"截图";
}

Result __stdcall SettingsCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: {
		Layout::InflateWindow(dlg2, res.Layout.settings, dlg2.vds);
		dlg2.edit = (Edit)dlg2(L"filename");
		for (int i = 0; i < 3; ++i) dlg2.choices[i] = (Choice)dlg2(ToString(i));
		break;
	}
	case Events::Window::Destroy: {
		dlg2.isOpen = false;
		dlg2.Reset();
	}
	}
	return 0;
}

Result __stdcall ChoiceCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (msg == Events::Control::LClick) {
		Choice choice(id);
		int index = StringTo<int>(choice.Name());
		if (choice.Select()) {
			for (int i = 0; i < 3; ++i)
				if (i != index) dlg2.choices[i].Select(false);
		}
		else {
			dlg2.choices[0].Select(true);
			dlg2.choices[1].Select(false);
			dlg2.choices[2].Select(false);
		}
	}
	return 0;
}

Result __stdcall ButtonCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (msg == Events::Control::LClick) {
		auto name = dlg2.edit.Content();
		if (name.empty()) res.Function.Toast(2000, L"默认名称不能为空");
		else {
			String type = L"jpg";
			if (dlg2.choices[1].Select()) type = L"bmp";
			else if (dlg2.choices[2].Select()) type = L"png";
			Ini ini; auto& section = ini[L"ScreenShot"];
			section[L"DefaultType"] = type;
			section[L"DefaultName"] = name;
			ini.SaveFile(var.CurrentPath + L"config.ini");
			var.DefaultName = name;
			var.DefaultType = type;
			dlg2.Destroy();
		}
	}
	return 0;
}

void Settings::Open() noexcept {
	if (var.DefaultType.empty()) ReadSettings();
	dlg2.vds = {
		{ L"Position.Left", (Memory)((Screen::Width >> 1) - 150) },
		{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 100) },
		{ L"Font.MSBlack.S16", *res.Font.MSBlack.S16 },
		{ L"Color.White", (Memory)Color::White },
		{ L"Skin.Window", *res.Skin.Window },
		{ L"Skin.Choice", *res.Skin.Choice },
		{ L"Skin.Edit", *res.Skin.Edit },
		{ L"Skin.Button", *res.Skin.Button },
		{ L"Value.GroundGlass", (Memory)res.GroundGlass },
		{ L"Value.DefaultName", &var.DefaultName },
		{ L"Value.Select0", (Memory)(var.DefaultType == L"jpg") },
		{ L"Value.Select1", (Memory)(var.DefaultType == L"bmp") },
		{ L"Value.Select2", (Memory)(var.DefaultType == L"png") },
		{ L"CallBack.Choice", &ChoiceCallBack },
		{ L"CallBack.Button", &ButtonCallBack },
	};
	dlg2.Start(&SettingsCallBack, {}, true, false, true);
}