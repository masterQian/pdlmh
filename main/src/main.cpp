#include "../include/pdlmh.h"
#include "../include/util.h"
#include <ShlObj.h>

// 窗口吸附回调
Result __stdcall AbsorbCallBack(ID, Event msg, Arg, Arg result, Arg, Arg) {
	if (msg == Events::Gradient::Result) mainWindow->Left(result);
	return 0;
}

// 窗口吸附
void AbsorbWindow() noexcept {
	if (mainWindow->Absorb.Can && !mainWindow->Absorb.Mutex) {
		mainWindow->Absorb.Mutex = true;
		POINT point; GetCursorPos(&point);
		if (point.x < 5 && mainWindow->Absorb.Is) {
			Gradient::Start(AbsorbCallBack, Gradient::Task().Add(-450, 0), 5, true);
			mainWindow->Absorb.Is = false;
		}
		else if (point.x > 450 && !mainWindow->Absorb.Is) {
			Gradient::Start(AbsorbCallBack, Gradient::Task().Add(0, -450), 5, true);
			mainWindow->Absorb.Is = true;
		}
		mainWindow->Absorb.Mutex = false;
	}
}

// 搜索编辑框回调
Result __stdcall SearchCallBack(ID id, Event msg, Arg status, Arg, Arg key, Arg) {
	if (msg == Events::Control::KeyEvent && status == Attrs::KeyType::Down) {
		if (key == VK_RETURN) {
			Edit edit(id);
			if (auto path = edit.Content(); !path.empty()) {
				edit.Content({});
				if (path.substr(1, 2) == L":\\") {
					if (GetFileAttributesW(path.data()) != INVALID_FILE_ATTRIBUTES)
						Process::Execute(path);
					else Toast(2000, L"文件或目录不存在");
				}
				else if (path.substr(0, 4) == L"http" || path.substr(0, 3) == L"www")
					Process::Execute(path);
				else {
					switch (var->Config.SearchEngine) {
					case 1: Process::Execute(L"https://www.baidu.com/s?wd=" + path); break;
					case 2: Process::Execute(L"https://cn.bing.com/search?q=" + path); break;
					case 3: Process::Execute(L"https://www.google.com/search?q=" + path); break;
					default: Toast(2000, L"设置中搜索引擎已关闭"); break;
					}
				}
			}
		}
	}
	return 0;
}

// 设置按钮回调
Result __stdcall OpenSettingsCallBack(ID id, Event msg, Arg, Arg, Arg, Arg) {
	switch (msg) {
	case Events::Control::LClick: {
		SettingsWindow::OpenSettings();
		break;
	}
	case Events::Control::LUp:
	case Events::Control::LDown: {
		if (var->Config.ListWave) {
			IconButton button(id);
			int offset = (msg == Events::Control::LUp ? -2 : 2);
			button.IconWidth(button.IconWidth() + offset);
			button.IconHeight(button.IconHeight() + offset);
		}
	}
	}
	return 0;
}

// 切换Tab栏缓动回调
Result __stdcall TabGradientCallBack(ID, Event msg, Arg id, Arg result, Arg, Arg data) {
	int New = SeparateHigh(data), Old = SeparateLow(data);
	switch (msg) {
	case Events::Gradient::Begin: mainWindow->Tabs[New].Visual(true); break;
	case Events::Gradient::Result: {
		if (id == 0) mainWindow->Tabs[Old].Left(result);
		else mainWindow->Tabs[New].Left(result);
		break;
	}
	case Events::Gradient::End: mainWindow->Tabs[Old].Visual(false); break;
	}
	return 0;
}

// 切换Tab栏
void SelectTab(int Old, int New) noexcept {
	if (Old != New) {
		auto size = mainWindow->Tabs.size();
		if (New >= 0 && New < size) {
			mainWindow->CurrentPage = New;
			if (!mainWindow->Tabs[New]) mainWindow->lazyFun[New * 2](); // 页面懒加载
			mainWindow->lazyFun[New * 2 + 1]();
			Gradient::Start(TabGradientCallBack, Gradient::Task().Add(5, 450,
				Gradient::Mode::CircleInOut).Add(450, 5, Gradient::Mode::CircleInOut),
				40 / var->Config.EffectSpeed, false, MergeInt(New, Old));
		}
	}
}

// Tab栏切换回调
Result __stdcall TabCallBack(ID id, Event msg, Arg index, Arg, Arg, Arg) {
	switch (msg) {
	case Events::IconList::ItemLCLick: {
		static Mutex mutex;
		if (mutex.lock()) {
			SelectTab(mainWindow->CurrentPage, index);
			mutex.unlock();
		}
		break;
	}
	}
	return 0;
}

// 托盘菜单回调
void __stdcall MainWindow::MenuTrayCallBack(Menu::Item item, Event msg, short tag) {
	if (msg == Events::Menu::ItemLCLick) {
		switch (tag) {
		case 0: mainWindow->Destroy(); break; // 退出
		}
	}
}

// 开启项目提示时钟
void MainWindow::__ItemTip::StartClock() noexcept {
	if (!TipShow) {
		Tip.Content(TipList.ItemTitle(TipIndex)).
			BackColor(Color::RGB_ARGB(var->Config.BackGroundColor)).Start(1);
		TipShow = true;
	}
}

// 主窗口回调
Result __stdcall MainCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: { // 创建事件
		// 反射布局
		Layout::InflateWindow(*mainWindow, res->Layout.Main, var->vds);
		// 初始化Tab栏
		mainWindow->CurrentPage = 0;
		mainWindow->Tab = (IconList)(*mainWindow)(L"Tab");
		mainWindow->lazyFun = {
			&MainWindow::LazyLoadPageProgram, &MainWindow::UpdatePageProgram,
			&MainWindow::LazyLoadPageSystem, &MainWindow::UpdatePageSystem,
			&MainWindow::LazyLoadPageTree, &MainWindow::UpdatePageTree,
			&MainWindow::LazyLoadPagePlugin, &MainWindow::UpdatePagePlugin,
			&MainWindow::LazyLoadPageFile, &MainWindow::UpdatePageFile,
		};
		mainWindow->Tabs.resize(mainWindow->lazyFun.size() >> 1);
		MainWindow::LazyLoadPageProgram(); // 懒加载程序页面
		// 初始化菜单
		mainWindow->InitMenu();
		// 初始化view
		mainWindow->Absorb.Mutex = false; mainWindow->Absorb.Can = true;
		mainWindow->Absorb.Is = true; mainWindow->Absorb.Clk.Bind(*mainWindow, 250); // 吸附时钟绑定
		mainWindow->TrayObject.Bind(*mainWindow, res->Image.Icon, LS::SoftwareNameString); // 托盘绑定
		mainWindow->DragObject.Bind(*mainWindow); // 拖放绑定
		mainWindow->Plugin.Clk.Bind(*mainWindow); // 插件提示时钟绑定
		mainWindow->ItemTip.Clk.Bind(*mainWindow); // 项目提示时钟绑定
		break;
	}
	case Events::Window::Destroy: { // 销毁事件
		ToastWindow::Release();
		SettingsWindow::Release();
		for (auto& plugin : mainWindow->Plugin.data) {
			if (plugin.isUse) {
				if (plugin.hDestroy) plugin.hDestroy(0, 0, 0, 0);
			}
		}
		mainWindow->DestroyMenu();
		mainWindow->ItemTip.Clk.Destroy();
		mainWindow->Plugin.Clk.Destroy();
		mainWindow->DragObject.Destroy();
		mainWindow->TrayObject.Destroy();
		mainWindow->Absorb.Clk.Destroy();
		break;
	}
	case Events::Window::Clock: { // 时钟事件
		if (mainWindow->Absorb.Clk.Check(arg1)) AbsorbWindow();
		else if (mainWindow->Plugin.Clk.Check(arg1)) mainWindow->Plugin.StartClock();
		else if (mainWindow->ItemTip.Clk.Check(arg1)) mainWindow->ItemTip.StartClock();
		break;
	}
	case Events::Window::Tray: { // 托盘事件
		if (arg2 == Events::Tray::RUp) mainWindow->menuTray.Open();
		break;
	}
	case Events::Window::Drag: { // 拖放事件
		if (mainWindow->CurrentPage == 0) mainWindow->ProgramDragFiles((Drag::DragPath)arg2, arg1); // 添加项目
		else if (mainWindow->CurrentPage == 4) mainWindow->FileDragFiles((Drag::DragPath)arg2, arg1);
		break;
	}
	}
	return 0;
}

// 初始化资源
void InitRes() noexcept {
	ByteSet bs;

	bs = Resource::Get(1000, L"LAYOUT"); res->Layout.Main = Code::From(bs);
	bs = Resource::Get(1001, L"LAYOUT"); res->Layout.Toast = Code::From(bs);
	bs = Resource::Get(1002, L"LAYOUT"); res->Layout.Settings = Code::From(bs);
	bs = Resource::Get(1100, L"LAYOUT"); res->Layout.MenuGroup = Code::From(bs);
	bs = Resource::Get(1101, L"LAYOUT"); res->Layout.MenuItem = Code::From(bs);
	bs = Resource::Get(1102, L"LAYOUT"); res->Layout.MenuTree = Code::From(bs);
	bs = Resource::Get(1103, L"LAYOUT"); res->Layout.MenuPlugin = Code::From(bs);
	bs = Resource::Get(1104, L"LAYOUT"); res->Layout.MenuTray = Code::From(bs);
	bs = Resource::Get(1105, L"LAYOUT"); res->Layout.MenuTreeDisk = Code::From(bs);
	bs = Resource::Get(1106, L"LAYOUT"); res->Layout.MenuFile = Code::From(bs);
	bs = Resource::Get(1200, L"LAYOUT"); res->Layout.pageProgram = Code::From(bs);
	bs = Resource::Get(1201, L"LAYOUT"); res->Layout.pageSystem = Code::From(bs);
	bs = Resource::Get(1202, L"LAYOUT"); res->Layout.pageTree = Code::From(bs);
	bs = Resource::Get(1203, L"LAYOUT"); res->Layout.pagePlugin = Code::From(bs);
	bs = Resource::Get(1204, L"LAYOUT"); res->Layout.pageFile = Code::From(bs);

	bs = Resource::Get(1000, L"DATA"); res->Data.About = Code::From(bs);
	bs = Resource::Get(1001, L"DATA"); res->Data.Update = Code::From(bs);
	bs = Resource::Get(1002, L"DATA"); res->Data.Version = Code::From(bs);
	bs = Resource::Get(1003, L"DATA"); res->Data.PreviewMap = Code::From(bs);
	bs = Resource::Get(1004, L"DATA"); res->Data.TypeMap = Code::From(bs);
	bs = Resource::Get(1005, L"DATA"); res->Data.DefaultSettings.assign(bs.content, bs.length);

	bs = Resource::Get(1000, L"SKIN"); res->Skin.Edit = Bin(bs.content, bs.length);
	bs = Resource::Get(1010, L"SKIN"); res->Skin.Group = Bin(bs.content, bs.length);
	bs = Resource::Get(1020, L"SKIN"); res->Skin.IconButton = Bin(bs.content, bs.length);
	bs = Resource::Get(1021, L"SKIN"); res->Skin.IconButton2 = Bin(bs.content, bs.length);
	bs = Resource::Get(1030, L"SKIN"); res->Skin.Picture = Bin(bs.content, bs.length);
	bs = Resource::Get(1040, L"SKIN"); res->Skin.SuperList = Bin(bs.content, bs.length);
	bs = Resource::Get(1041, L"SKIN"); res->Skin.SuperList2 = Bin(bs.content, bs.length);
	bs = Resource::Get(1050, L"SKIN"); res->Skin.Menu = Bin(bs.content, bs.length);
	bs = Resource::Get(1060, L"SKIN"); res->Skin.Button = Bin(bs.content, bs.length);
	bs = Resource::Get(1070, L"SKIN"); res->Skin.Choice = Bin(bs.content, bs.length);
	bs = Resource::Get(1080, L"SKIN"); res->Skin.Slider = Bin(bs.content, bs.length);
	bs = Resource::Get(1090, L"SKIN"); res->Skin.ColorPick = Bin(bs.content, bs.length);
	bs = Resource::Get(1100, L"SKIN"); res->Skin.IconList = Bin(bs.content, bs.length);
	bs = Resource::Get(1101, L"SKIN"); res->Skin.IconList2 = Bin(bs.content, bs.length);
	bs = Resource::Get(1110, L"SKIN"); res->Skin.Progress = Bin(bs.content, bs.length);

	bs = Resource::Get(100); res->Image.Icon = Bin(bs.content, bs.length);
	bs = Resource::Get(1000); res->Image.Search = Bin(bs.content, bs.length);
	bs = Resource::Get(1001); res->Ico.Settings = ICO(bs.content, bs.length);
	res->Image.Settings = res->Ico.Settings.ToBin();
	bs = Resource::Get(1002); res->Image.Close = Bin(bs.content, bs.length);
	bs = Resource::Get(1003); res->Image.Info = Bin(bs.content, bs.length);

	bs = Resource::Get(1100); res->Ico.Tab.Start = ICO(bs.content, bs.length);
	bs = Resource::Get(1101); res->Ico.Tab.Tool = ICO(bs.content, bs.length);
	bs = Resource::Get(1102); res->Ico.Tab.Folder = ICO(bs.content, bs.length);
	bs = Resource::Get(1103); res->Ico.Tab.Plugin = ICO(bs.content, bs.length);
	bs = Resource::Get(1104); res->Ico.Tab.File = ICO(bs.content, bs.length);

	bs = Resource::Get(1200); res->Ico.Tree.Return = ICO(bs.content, bs.length);
	bs = Resource::Get(1201); res->Ico.Tree.NewFolder = ICO(bs.content, bs.length);
	bs = Resource::Get(1202); res->Ico.Tree.Desktop = ICO(bs.content, bs.length);

	bs = Resource::Get(1300); res->Ico.Choice.Off = ICO(bs.content, bs.length);
	bs = Resource::Get(1301); res->Ico.Choice.On = ICO(bs.content, bs.length);

	for (int i = 0; i < 7; ++i) {
		bs = Resource::Get(1400 + i);
		res->Ico.Drive[i] = ICO(bs.content, bs.length);
		res->Image.Drive[i] = res->Ico.Drive[i].ToBin();
	}

	for (int i = 0; i < 15; ++i) {
		bs = Resource::Get(1000 + i, L"FICO");
		res->Ico.Default[i] = ICO(bs.content, bs.length);
	}

	bs = Resource::Get(1000, L"MICO"); res->Ico.Menu.Admin = ICO(bs.content, bs.length);
	bs = Resource::Get(1001, L"MICO"); res->Ico.Menu.Delete = ICO(bs.content, bs.length);
	bs = Resource::Get(1002, L"MICO"); res->Ico.Menu.Edit = ICO(bs.content, bs.length);
	bs = Resource::Get(1003, L"MICO"); res->Ico.Menu.Exit = ICO(bs.content, bs.length);
	bs = Resource::Get(1004, L"MICO"); res->Ico.Menu.Folder = ICO(bs.content, bs.length);
	bs = Resource::Get(1005, L"MICO"); res->Ico.Menu.Path = ICO(bs.content, bs.length);
	bs = Resource::Get(1006, L"MICO"); res->Ico.Menu.Able = ICO(bs.content, bs.length);
	bs = Resource::Get(1007, L"MICO"); res->Ico.Menu.Disable = ICO(bs.content, bs.length);
	bs = Resource::Get(1008, L"MICO"); res->Ico.Menu.Move = ICO(bs.content, bs.length);
	bs = Resource::Get(1009, L"MICO"); res->Ico.Menu.Copy = ICO(bs.content, bs.length);
	bs = Resource::Get(1010, L"MICO"); res->Ico.Menu.Cut = ICO(bs.content, bs.length);
	bs = Resource::Get(1011, L"MICO"); res->Ico.Menu.Paste = ICO(bs.content, bs.length);
	bs = Resource::Get(1012, L"MICO"); res->Ico.Menu.Property = ICO(bs.content, bs.length);
	bs = Resource::Get(1013, L"MICO"); res->Ico.Menu.Left = ICO(bs.content, bs.length);
	bs = Resource::Get(1014, L"MICO"); res->Ico.Menu.Right = ICO(bs.content, bs.length);
	bs = Resource::Get(1015, L"MICO"); res->Ico.Menu.Rename = ICO(bs.content, bs.length);
	bs = Resource::Get(1016, L"MICO"); res->Ico.Menu.Preview = ICO(bs.content, bs.length);
	bs = Resource::Get(1017, L"MICO"); res->Ico.Menu.Save = ICO(bs.content, bs.length);

	res->SystemTools.resize(17);
	bs = Resource::Get(1000, L"SICO");
	res->SystemTools[0] = { ICO(bs.content, bs.length) , {}, {}, {} };
	bs = Resource::Get(1001, L"SICO");
	res->SystemTools[1] = { ICO(bs.content, bs.length) , LS::ToolComputer, L"::{20D04FE0-3AEA-1069-A2D8-08002B30309D}", {} };
	bs = Resource::Get(1002, L"SICO");
	res->SystemTools[2] = { ICO(bs.content, bs.length) , LS::ToolDocument, L"::{450D8FBA-AD25-11D0-98A8-0800361B1103}", {} };
	bs = Resource::Get(1003, L"SICO");
	res->SystemTools[3] = { ICO(bs.content, bs.length) , LS::ToolRecycleBin, L"::{645FF040-5081-101B-9F08-00AA002F954E}", {} };
	bs = Resource::Get(1004, L"SICO");
	res->SystemTools[4] = { ICO(bs.content, bs.length) , LS::ToolControl, L"control.exe", {} };
	bs = Resource::Get(1005, L"SICO");
	res->SystemTools[5] = { ICO(bs.content, bs.length) , LS::ToolCmd, L"cmd.exe", {} };
	bs = Resource::Get(1006, L"SICO");
	res->SystemTools[6] = { ICO(bs.content, bs.length) , LS::ToolPowershell, L"powershell.exe", {} };
	bs = Resource::Get(1007, L"SICO");
	res->SystemTools[7] = { ICO(bs.content, bs.length) , LS::ToolTaskmgr, L"taskmgr.exe", {} };
	bs = Resource::Get(1008, L"SICO");
	res->SystemTools[8] = { ICO(bs.content, bs.length) , LS::ToolCalculator, L"calc.exe", {} };
	bs = Resource::Get(1009, L"SICO");
	res->SystemTools[9] = { ICO(bs.content, bs.length) , LS::ToolNotepad, L"notepad.exe", {} };
	bs = Resource::Get(1010, L"SICO");
	res->SystemTools[10] = { ICO(bs.content, bs.length) , LS::ToolPrinter, L"::{2227a280-3aea-1069-a2de-08002b30309d}", {} };
	bs = Resource::Get(1011, L"SICO");
	res->SystemTools[11] = { ICO(bs.content, bs.length) , LS::ToolRegedit, L"regedit.exe", {} };
	bs = Resource::Get(1012, L"SICO");
	res->SystemTools[12] = { ICO(bs.content, bs.length) , LS::ToolScanner, L"wiaacmgr.exe", {} };
	bs = Resource::Get(1013, L"SICO");
	res->SystemTools[13] = { ICO(bs.content, bs.length) , LS::ToolComputerManager, L"compmgmt.msc", {} };
	bs = Resource::Get(1014, L"SICO");
	res->SystemTools[14] = { ICO(bs.content, bs.length) , LS::ToolService, L"mmc.exe", L" services.msc" };
	bs = Resource::Get(1015, L"SICO");
	res->SystemTools[15] = { ICO(bs.content, bs.length) , LS::ToolSecpol, L"mmc.exe", L" secpol.msc" };
	bs = Resource::Get(1016, L"SICO");
	res->SystemTools[16] = { ICO(bs.content, bs.length) , LS::ToolGpedit, L"gpedit.msc", {} };

	res->Font.MSBlack.S12 = Font(LS::FontMSBlack, 12, Font::Style::Null).Create();
	res->Font.MSBlack.S14 = Font(LS::FontMSBlack, 14, Font::Style::Null).Create();
	res->Font.MSBlack.S16 = Font(LS::FontMSBlack, 16, Font::Style::Null).Create();
	res->Font.MSBlack.SB14 = Font(LS::FontMSBlack, 14, Font::Style::Bold).Create();
	res->Font.MSBlack.SB16 = Font(LS::FontMSBlack, 16, Font::Style::Bold).Create();
	res->Font.MSBlack.SL14 = Font(LS::FontMSBlack, 14, Font::Style::Null).SetRender(Font::Render::LightText, 196612).Create();
	res->Font.MSBlack.SL16 = Font(LS::FontMSBlack, 16, Font::Style::Null).SetRender(Font::Render::LightText, 196612).Create();
}

// 取整数配置
int GetIntConfig(Ini::Section* section, ConstString key, int def = 0) noexcept {
	if (auto iter = &(*section)[key]; !iter->empty()) return StringTo<int>(iter->data());
	return def;
}

// 初始化路径
void InitPath() noexcept {
	Path::MakesureFolder(Con::Path_Config);
	Path::MakesureFile(Con::Path_Config_Data);
	Path::MakesureFile(Con::Path_Config_Settings, res->Data.DefaultSettings);
	Path::MakesureFolder(Con::Path_Plugin);
}

// 初始化配置
void InitConfig() noexcept {
	Ini ini_settings, ini_data;
	ini_settings.LoadFile(Con::Path_Config_Settings);
	ini_data.LoadFile(Con::Path_Config_Data);
	auto& config = var->Config;
	Ini::Section* section1 = &ini_settings[LS::IniSettings], * section2;
	config.AutoStart = GetIntConfig(section1, LS::IniAutoStart, 1);
	config.EffectSpeed = GetIntConfig(section1, LS::IniEffectSpeed, 8);
	config.BackGroundColor = GetIntConfig(section1, LS::IniBackGroundColor, 0);
	config.ListWave = GetIntConfig(section1, LS::IniListWave, 1);
	config.FolderTreeFilter = GetIntConfig(section1, LS::IniTreeFilter, 
		FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_DIRECTORY |
		FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL);
	config.SearchEngine = GetIntConfig(section1, LS::IniSearchEngine, 1);
	config.GroundGlass = GetIntConfig(section1, LS::IniGroundGlass, 1);

	section1 = &ini_settings[LS::IniData];
	UINT groupCount = GetIntConfig(section1, LS::IniCount, 0), itemCount;
	auto& data = var->Data; data.resize(groupCount);
	std::vector<FileEntry>* items;
	String* iter1, * iter2;
	for (UINT i = 0; i < groupCount; ++i) {
		iter1 = &(*section1)[ToString(i)];
		data[i] = GroupEntry{ iter1->data(), {} };
		items = &data[i].files;
		section2 = &ini_data[*iter1];
		itemCount = GetIntConfig(section2, LS::IniCount, 0);
		items->resize(itemCount);
		for (UINT j = 0; j < itemCount; ++j) {
			iter2 = &(*section2)[ToString(j)];
			LoadFileEntry(*iter2, (*items)[j]);
		}
	}
}

// 初始化全局变量
void InitVar() noexcept {
	auto resMap = Layout::InflateMapper(res->Data.TypeMap, {});
	for (auto& [key, value] : resMap) var->TypeMap[key] = StringTo<int>(value);
	var->TypeMap[L""] = 1;
	var->AppData = Path::GetPath(Path::AppData) + LS::Separator + LS::SoftwareName;
	Path::MakesureFolder(var->AppData);
	auto ImageEncoder = System::GetImageEncoder();
	var->GUID_BMP = ImageEncoder[L"image/bmp"];
	var->GUID_JPG = ImageEncoder[L"image/jpeg"];
	var->GUID_PNG = ImageEncoder[L"image/png"];
	InitConfig();
	auto img = Color::SolidBitmap(var->Config.BackGroundColor);
	var->BackGroundImage = Bin(img.data(), img.size());
	var->NewSkinWindow = SkinWindow(SkinWindow::Default()).BackGround(var->BackGroundImage).Create();
}

// 初始化V/D交换机
void InitVDS() noexcept {
	var->vds = {
		{ L"Value.GroundGlass", (Memory)var->Config.GroundGlass },

		{ L"Color.White", (Memory)Color::White },

		{ L"Image.Search", res->Image.Search },
		{ L"Image.Settings", res->Image.Settings },

		{ L"Icon.Tab.Start", res->Ico.Tab.Start },
		{ L"Icon.Tab.Tool", res->Ico.Tab.Tool },
		{ L"Icon.Tab.Folder", res->Ico.Tab.Folder },
		{ L"Icon.Tab.Plugin", res->Ico.Tab.Plugin },
		{ L"Icon.Tab.File", res->Ico.Tab.File },

		{ L"Skin.Window", var->NewSkinWindow },
		{ L"Skin.Edit", res->Skin.Edit },
		{ L"Skin.Button", res->Skin.Button },
		{ L"Skin.Picture", res->Skin.Picture },
		{ L"Skin.IconList", res->Skin.IconList },
		{ L"Skin.IconList2", res->Skin.IconList2 },
		{ L"Skin.Group", res->Skin.Group },
		{ L"Skin.IconButton", res->Skin.IconButton },
		{ L"Skin.IconButton2", res->Skin.IconButton2 },
		{ L"Skin.SuperList", res->Skin.SuperList },
		{ L"Skin.SuperList2", res->Skin.SuperList2 },
		{ L"Skin.Progress", res->Skin.Progress },

		{ L"Font.MSBlack.S12", res->Font.MSBlack.S12 },
		{ L"Font.MSBlack.S14", res->Font.MSBlack.S14 },
		{ L"Font.MSBlack.S16", res->Font.MSBlack.S16 },
		{ L"Font.MSBlack.SL14", res->Font.MSBlack.SL14 },
		{ L"Font.MSBlack.SL16", res->Font.MSBlack.SL16 },
		{ L"Font.MSBlack.SB14", res->Font.MSBlack.SB14 },
		{ L"Font.MSBlack.SB16", res->Font.MSBlack.SB16 },

		{ L"CallBack.Tab", &TabCallBack },
		{ L"CallBack.Search", &SearchCallBack },
		{ L"CallBack.OpenSettings", &OpenSettingsCallBack },
	};
}

void WinUIMain() noexcept {
	// 资源申请
	res = new Res; var = new Var;
	InitRes(); InitPath(); InitVar(); InitVDS();
	// 载入主窗口
	mainWindow = new MainWindow;
	mainWindow->Start(MainCallBack, {}, true, false, true);
	// 资源回收
	mainWindow->FreePlugins();
	delete mainWindow; delete var; delete res;
}