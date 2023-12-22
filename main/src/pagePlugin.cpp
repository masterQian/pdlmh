#include "../include/pdlmh.h"

#include <filesystem>

// 插件通知回调
Result __stdcall PluginNotifyCallBack(Plugin* plugin, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	return 0;
}

// 初始化系统调用
void InitSystemCall() noexcept {
	mainWindow->Plugin.sys = {
		// 全局变量
		{ L"mainWindow", &mainWindow },
		{ L"BackGroundImage", &var->BackGroundImage },
		{ L"NewSkinWindow", &var->NewSkinWindow },
		{ L"Config", &var->Config },
		{ L"GroundGlass", (Memory)var->Config.GroundGlass },
		{ L"Data", &var->Data },
		{ L"GUID_JPG", &var->GUID_JPG },
		{ L"GUID_BMP", &var->GUID_BMP },
		{ L"GUID_PNG", &var->GUID_PNG },
		// 资源
		{ L"Image.Icon", &res->Image.Icon },
		{ L"Skin.Edit", &res->Skin.Edit },
		{ L"Skin.Button", &res->Skin.Button },
		{ L"Skin.Choice", &res->Skin.Choice },
		{ L"Skin.Picture", &res->Skin.Picture },
		{ L"Skin.IconList", &res->Skin.IconList },
		{ L"Skin.IconList2", &res->Skin.IconList2 },
		{ L"Skin.Group", &res->Skin.Group },
		{ L"Skin.IconButton", &res->Skin.IconButton },
		{ L"Skin.IconButton2", &res->Skin.IconButton2 },
		{ L"Skin.SuperList", &res->Skin.SuperList },
		{ L"Skin.SuperList2", &res->Skin.SuperList2 },
		{ L"Skin.Progress", &res->Skin.Progress },
		{ L"Skin.Menu", &res->Skin.Menu },
		{ L"Font.MSBlack.S12", &res->Font.MSBlack.S12 },
		{ L"Font.MSBlack.S14", &res->Font.MSBlack.S14 },
		{ L"Font.MSBlack.S16", &res->Font.MSBlack.S16 },
		{ L"Font.MSBlack.SL14", &res->Font.MSBlack.SL14 },
		{ L"Font.MSBlack.SL16", &res->Font.MSBlack.SL16 },
		{ L"Font.MSBlack.SB14", &res->Font.MSBlack.SB14 },
		{ L"Font.MSBlack.SB16", &res->Font.MSBlack.SB16 },
		// 函数
		{ L"Toast", &Toast },
	};
}

// 载入插件
void LoadPlugins() noexcept {
	using namespace std::filesystem;
	Ini ini;
	for (auto& subPath : directory_iterator(path(Con::Path_Plugin))) {
		try {
			if (is_directory(subPath)) {
				Plugin plugin;
				plugin.path = subPath.path().wstring();
				ini.LoadFile(plugin.path + Con::Path_Plugin_Ini);
				auto& section = ini[LS::PluginInfo];
				plugin.file = section[LS::PluginInfoFile];
				plugin.name = section[LS::PluginInfoName];
				plugin.ico = File::ReadICO(plugin.path + LS::Separator + section[LS::PluginInfoIcon]);
				plugin.version = section[LS::PluginInfoVersion];
				plugin.author = section[LS::PluginInfoAuthor];
				plugin.comment = section[LS::PluginInfoComment];
				plugin.isUse = StringTo<int>(section[LS::PluginInfoIsUse]);
				if (plugin.isUse) {
					if (plugin.hPlugin = LoadLibraryW((plugin.path + LS::Separator + plugin.file).data())) {
						auto hInit = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncInit);
						plugin.hDestroy = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncDestroy);
						plugin.hRun = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncRun);
						if (StringTo<int>(section[LS::PluginInfoSettings]))
							plugin.hSettings = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncSettings);
						if (hInit && plugin.hDestroy && plugin.hRun) {
							if (hInit((int)&mainWindow->Plugin.sys, 0, (int)&PluginNotifyCallBack, (int)&plugin))
								mainWindow->Plugin.data.push_back(std::move(plugin));
						}
					}
				}
				else mainWindow->Plugin.data.push_back(std::move(plugin));
			}
		}
		catch (filesystem_error&) {}
	}
}

// 开启插件提示时钟
void MainWindow::__Plugin::StartClock() noexcept {
	if (!TipShow && TipIndex < data.size()) {
		Tip.Content(data[TipIndex].comment).Icon(data[TipIndex].ico)
			.BackColor(Color::RGB_ARGB(var->Config.BackGroundColor)).Start(1);
		TipShow = true;
	}
}

// 插件列表按钮回调
Result __stdcall PluginListCallBack(ID id, Event msg, Arg row, Arg col, Arg, Arg source) {
	if (source == Attrs::ListEventSource::Item) {
		auto& plugins = mainWindow->Plugin.data;
		SuperList list(id);
		switch (msg) {
		case Events::SuperList::ItemLCLick: { // 单击
			if (col == 5) { // 设置
				if (plugins[row].isUse) {
					if (plugins[row].hSettings) {
						if (!plugins[row].hSettings(0, 0, 0, 0))
							Toast(2000, LS::Tip_PluginError);
					}
				}
				else Toast(2000, LS::Tip_PluginNotUse);
			}
			break;
		}
		case Events::SuperList::ItemRCLick: { // 右键
			list.CurrentItem(row);
			mainWindow->menuPlugin.Open();
			break;
		}
		case Events::SuperList::ItemLDCLick: { // 双击
			if (col > 0 && col < 5) {
				if (plugins[row].isUse) {
					auto result = false;
					if (plugins[row].hRun)
						result = plugins[row].hRun(0, 0, 0, 0);
					if (!result) Toast(2000, LS::Tip_PluginError);
				}
				else Toast(2000, LS::Tip_PluginNotUse);
			}
			break;
		}
		case Events::SuperList::ItemMouseIn: { // 鼠标进入
			if (var->Config.ListWave) list.ItemHeight(row, LS::ListDefaultWaveHeight);
			if (!mainWindow->Plugin.TipShow) {
				mainWindow->Plugin.TipIndex = row;
				mainWindow->Plugin.Clk.Start(1000);
			}
			break;
		}
		case Events::SuperList::ItemMouseOut: { // 鼠标离开
			if (var->Config.ListWave) list.ItemHeight(row, LS::ListDefaultHeight);
			mainWindow->Plugin.Clk.Stop();
			if (mainWindow->Plugin.TipShow) {
				mainWindow->Plugin.Tip.Start(0);
				mainWindow->Plugin.TipShow = false;
			}
			break;
		}
		}
	}
	return 0;
}

// 插件菜单回调
void __stdcall MainWindow::MenuPluginCallBack(Menu::Item item, Event msg, short tag) {
	if (msg == Events::Menu::Open) { mainWindow->Absorb.Can = false; return; }
	else if (msg == Events::Menu::Close) { mainWindow->Absorb.Can = true; return; }
	else [[likely]] if (msg == Events::Menu::ItemLCLick) {
		auto& list = mainWindow->Plugin.list;
		auto index = list.CurrentItem();
		auto& plugin = mainWindow->Plugin.data[index];
		switch (tag) {
		case 0: { // 启用
			if (plugin.isUse) Toast(2000, LS::Tip_PluginAlreadyUse);
			else {
				auto path = plugin.path + Con::Path_Plugin_Ini;
				Ini ini; ini.LoadFile(path); auto& section = ini[LS::PluginInfo];
				section[LS::PluginInfoIsUse] = LS::True;
				bool result = false;
				if (plugin.hPlugin) result = true;
				else {
					if (plugin.hPlugin = LoadLibraryW((plugin.path + LS::Separator + plugin.file).data())) {
						auto hInit = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncInit);
						plugin.hDestroy = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncDestroy);
						plugin.hRun = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncRun);
						if (StringTo<int>(section[LS::PluginInfoSettings]))
							plugin.hSettings = (PluginCall)GetProcAddress(plugin.hPlugin, LS::PluginFuncSettings);
						if (hInit && plugin.hDestroy && plugin.hRun) {
							if (hInit((int)&mainWindow->Plugin.sys, 0, (int)&PluginNotifyCallBack, (int)&plugin))
								result = true;
						}
					}
				}
				if (result) {
					plugin.isUse = true;
					ini.SaveFile(path);
					list.ItemIcon(index, 0, res->Ico.Choice.On);
					Toast(2000, LS::Tip_PluginUse);
				}
				else Toast(2000, LS::Tip_PluginError);
			}
			break;
		}
		case 1: { // 禁用
			if (!plugin.isUse) Toast(2000, LS::Tip_PluginAlreadyNoUse);
			else {
				auto path = plugin.path + Con::Path_Plugin_Ini;
				Ini ini; ini.LoadFile(path); auto& section = ini[LS::PluginInfo];
				section[LS::PluginInfoIsUse] = LS::False;
				ini.SaveFile(path);
				if (plugin.hDestroy) plugin.hDestroy(0, 0, 0, 0);
				plugin.isUse = false;
				list.ItemIcon(index, 0, res->Ico.Choice.Off);
				Toast(2000, LS::Tip_PluginNoUse);
			}
			break;
		}
		case 2: { // 打开文件位置
			Process::Execute(Environment::CurrentPath + plugin.path);
			break;
		}
		}
	}
}

void MainWindow::LazyLoadPagePlugin() noexcept {
	mainWindow->LockUpdate();
	var->vds[L"CallBack.PluginList"] = &PluginListCallBack;
	mainWindow->Tabs[3] = Layout::InflateControl(*mainWindow, res->Layout.pagePlugin, var->vds);
	auto list = (SuperList)mainWindow->Tabs[3](L"PluginList");
	mainWindow->Plugin.list = list;
	list.InsertColumn(-1, {}, 0, 24, Attrs::ItemAlign::Center, 20, 20);
	list.InsertColumn(-1, {}, 0, 40, Attrs::ItemAlign::Center, 32, 32);
	list.InsertColumn(-1, {}, Color::White, 189, Attrs::ItemAlign::Center, 0, 0, res->Font.MSBlack.SL16);
	list.InsertColumn(-1, {}, Color::White, 50, Attrs::ItemAlign::Center, 0, 0, res->Font.MSBlack.SL16);
	list.InsertColumn(-1, {}, Color::White, 100, Attrs::ItemAlign::Center, 0, 0, res->Font.MSBlack.SL16);
	list.InsertColumn(-1, {}, 0, 32, Attrs::ItemAlign::Center, 24, 24);
	InitSystemCall();
	LoadPlugins();
	int index;
	for (auto& plugin : mainWindow->Plugin.data) {
		index = list.InsertItem();
		list.ItemIcon(index, 0, plugin.isUse ? res->Ico.Choice.On : res->Ico.Choice.Off);
		list.ItemIcon(index, 1, (PICO)plugin.ico ? plugin.ico : res->Ico.Default[0]);
		list.ItemTitle(index, 2, plugin.name);
		list.ItemTitle(index, 3, plugin.version);
		list.ItemTitle(index, 4, plugin.author);
		list.ItemFontColor(index, -1, Color::White);
		if (plugin.hSettings) list.ItemIcon(index, 5, res->Ico.Settings);
	}
	mainWindow->UnlockUpdate();
	mainWindow->Plugin.Tip.FontColor(Color::White).Font(res->Font.MSBlack.SL16)
		.Align(Attrs::Align::Start_Center_Mul).Transparency(200);
}

void MainWindow::UpdatePagePlugin() noexcept {
	static Mutex mutex;
	if (mutex.lock()) {
		for (auto& plugin : mainWindow->Plugin.data) {
			if (!plugin.isUse && plugin.hPlugin) {
				FreeLibrary(plugin.hPlugin);
				plugin.hPlugin = nullptr;
				plugin.hDestroy = nullptr;
				plugin.hRun = nullptr;
				plugin.hSettings = nullptr;
			}
		}
		mutex.unlock();
	}
}

void MainWindow::FreePlugins() noexcept {
	for (auto& plugin : Plugin.data)
		if (plugin.isUse) FreeLibrary(plugin.hPlugin);
}