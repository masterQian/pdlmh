#include "../include/pdlmh.h"
#include "../include/util.h"

// 能否修改分组名
bool MainWindow::CanModifyGroupName(ConstString oldName, ConstString newName) const noexcept {
	if (oldName != newName && newName != Con::AddSign && !newName.empty()) {
		for (auto& i : var->Data)
			if (i.name == newName) return false;
		return true;
	}
	return false;
}

// 刷新项目列表
void MainWindow::UpdateItemList() noexcept {
	auto index = CurrentGroup;
	if (index >= 0 && index < static_cast<int>(var->Data.size())) {
		auto& groupEntry = var->Data[index].files;
		int listCount = SLItem.ItemCount();
		int actualCount = groupEntry.size();
		SLItem.LockUpdate();
		if (listCount > actualCount) { // 列表项目多,改写后删除
			for (int i = 0; i < actualCount; ++i) {
				SLItem.ItemIcon(i, groupEntry[i].ico);
				SLItem.ItemTitle(i, groupEntry[i].name);
			}
			SLItem.DeleteItem(actualCount, listCount - actualCount);
		}
		else { // 列表项目少,改写后添加
			for (int i = 0; i < listCount; ++i) {
				SLItem.ItemIcon(i, groupEntry[i].ico);
				SLItem.ItemTitle(i, groupEntry[i].name);
			}
			for (int i = 0; i < actualCount - listCount; ++i)
				SLItem.InsertItem(-1, groupEntry[i + listCount].name, groupEntry[i + listCount].ico, Color::White);
		}
		SLItem.CurrentItem(-1);
		SLItem.UnlockUpdate();
	}
}

// 获得拖拽文件
void MainWindow::ProgramDragFiles(Drag::DragPath paths, int count) noexcept {
	auto& group = var->Data[CurrentGroup];
	wchar_t fileName[_MAX_FNAME]{}, ext[_MAX_EXT]{};
	String filePath;
	SLItem.LockUpdate();
	Ini ini; ini.LoadFile(Con::Path_Config_Data);
	auto& section = ini[var->Data[CurrentGroup].name];
	for (int i = 0; i < count; ++i) {
		filePath = paths[i];
		group.files.push_back({});
		FileEntry& entry = group.files.back();
		_wsplitpath(filePath.data(), nullptr, nullptr, fileName, ext);
		if (lstrcmpW(ext, L".lnk") == 0) { // 提取快捷方式指向
			filePath = Path::GetShortCutTarget(filePath);
			_wsplitpath(filePath.data(), nullptr, nullptr, fileName, ext);
		}
		entry.name = fileName; entry.path = filePath;
		entry.arg = LS::Space; entry.ico = GetFileExtraTypeIcon(filePath, &entry.type);
		auto index = SLItem.InsertItem(-1, entry.name, entry.ico, Color::White);
		// [写磁盘]
		section[ToString(index)] = SaveFileEntry(entry);
	}
	section[LS::IniCount] = ToString(group.files.size());
	ini.SaveFile(Con::Path_Config_Data);
	SLItem.UnlockUpdate();
}

// 编辑项目
void ModifyItem() noexcept {
	auto& EditGroup = mainWindow->Modify.EditGroup;
	if (!mainWindow->Modify.isModify) {
		mainWindow->Modify.isModify = true;
		EditGroup.Visual(true);
		mainWindow->SLGroup.Visual(false);
		mainWindow->SLItem.Visual(false);
		auto& entry = mainWindow->Modify.entry;
		Edit edit = (Edit)EditGroup(L"EditName"); edit.Content(entry->name);
		edit = (Edit)EditGroup(L"EditPath"); edit.Content(entry->path);
		edit = (Edit)EditGroup(L"EditArg"); edit.Content(entry->arg);
		((Choice)EditGroup(L"ChoiceAdmin")).Select(entry->admin);
		((Picture)EditGroup(L"EditPic")).Image(entry->ico.ToBin());
	}
}

// 编辑按钮回调
Result __stdcall EditButtonCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (msg == Events::Control::LClick) {
		auto& EditGroup = mainWindow->Modify.EditGroup;
		if (mainWindow->Modify.isModify) {
			Button button(id); int index = StringTo<int>(button.Name());
			if (index == 0) {
				String name = ((Edit)EditGroup(L"EditName")).Content();
				String arg = ((Edit)EditGroup(L"EditArg")).Content();
				bool admin = ((Choice)EditGroup(L"ChoiceAdmin")).Select();
				if (arg.empty()) arg.push_back(LS::CSpace);
				if (name.empty()) {
					Toast(2000, LS::Tip_EmptyName);
					return 0;
				}
				else {
					bool isModify = false;
					auto& entry = mainWindow->Modify.entry;
					auto& SLItem = mainWindow->SLItem;
					int index = mainWindow->Modify.index;
					if (name != entry->name) {
						isModify = true;
						entry->name = name;
						SLItem.ItemTitle(index, name);
					}
					if (arg != entry->arg) {
						isModify = true;
						entry->arg = arg;
					}
					if (admin != entry->admin) {
						isModify = true;
						entry->admin = admin;
					}
					if (isModify) {
						// [写磁盘]
						Ini ini; ini.LoadFile(Con::Path_Config_Data);
						ini[var->Data[mainWindow->CurrentGroup].name][ToString(index)] = SaveFileEntry(*entry);
						ini.SaveFile(Con::Path_Config_Data);
					}
				}
			}
			mainWindow->Modify.entry = nullptr;
			mainWindow->Modify.isModify = false;
			mainWindow->Modify.index = -1;
			EditGroup.Visual(false);
			mainWindow->SLGroup.Visual(true);
			mainWindow->SLItem.Visual(true);
		}
	}
	return 0;
}

// 渐隐渐显回调
Result __stdcall VisualCallBack(ID, Event msg, Arg, Arg result, Arg, Arg data) {
	if (msg == Events::Gradient::Result) Control((ID)data).Transparency(result);
	return 0;
}

// 分组超列回调
Result __stdcall SLGroupCallBack(ID id, Event msg, Arg row, Arg, Arg, Arg source) {
	if (source == Attrs::ListEventSource::Item) {
		int size = static_cast<int>(var->Data.size()),
			speed = static_cast<int>(40 / var->Config.EffectSpeed);
		static Mutex animateMutex;
		switch (msg) {
		case Events::SuperList::ItemLCLick: { // 左键单击
			if (row != mainWindow->CurrentGroup) {
				if (animateMutex.lock()) {
					mainWindow->CurrentGroup = row;
					Gradient::Start(VisualCallBack, Gradient::Task().Add(255, 10, Gradient::Mode::SinInOut), speed, true, (ID)mainWindow->SLItem);
					if (mainWindow->CurrentGroup < size) mainWindow->UpdateItemList();
					else mainWindow->SLItem.ClearItem();
					Gradient::Start(VisualCallBack, Gradient::Task().Add(10, 255, Gradient::Mode::SinInOut), speed, true, (ID)mainWindow->SLItem);
					animateMutex.unlock();
				}
			}
			break;
		}
		case Events::SuperList::ItemRCLick: { // 右键单击
			if (row != size) {
				if (row != mainWindow->CurrentGroup) {
					static Mutex mutex;
					if (mutex.lock()) {
						mainWindow->CurrentGroup = row;
						mainWindow->SLGroup.CurrentItem(row);
						mainWindow->UpdateItemList();
						mutex.unlock();
					}
				}
				mainWindow->menuGroup.Open();
			}
			break;
		}
		case Events::SuperList::ItemLDCLick: { // 左键双击
			if (animateMutex.lock()) {
				auto& SLGroup = mainWindow->SLGroup;
				mainWindow->Absorb.Can = false;
				auto oldName = SLGroup.ItemTitle(row, 0);
				auto newName = mainWindow->SLGroup.InputAt(row, 0, Attrs::ItemAlign::Center,
					res->Font.MSBlack.S16, Color::Black, res->Skin.Edit);
				mainWindow->Absorb.Can = true;
				if (mainWindow->CanModifyGroupName(oldName, newName)) {
					SLGroup.LockUpdate();
					if (row == size) { // 添加新分组
						SLGroup.ItemTitle(row, 0, newName);
						var->Data.push_back({ newName, {} });
						auto newIndex = SLGroup.InsertItem();
						SLGroup.ItemTitle(newIndex, 0, Con::AddSign);
						SLGroup.ItemFontColor(newIndex, 0, Color::White);
						// [写磁盘]
						Ini ini; ini.LoadFile(Con::Path_Config_Settings);
						auto newCount = ToString(newIndex);
						ini[LS::IniData][LS::IniCount] = newCount;
						ini[LS::IniData][ToString(newIndex - 1)] = newName;
						ini.SaveFile(Con::Path_Config_Settings);
						ini.LoadFile(Con::Path_Config_Data);
						ini[newName][LS::IniCount] = L"0";
						ini.SaveFile(Con::Path_Config_Data);
					}
					else { // 重命名分组
						var->Data[row].name = newName;
						SLGroup.ItemTitle(row, 0, newName);
						// [写磁盘]
						Ini ini; ini.LoadFile(Con::Path_Config_Settings);
						ini[LS::IniData][ToString(row)] = newName;
						ini.SaveFile(Con::Path_Config_Settings);
						ini.LoadFile(Con::Path_Config_Data);
						auto nh = ini.group.extract(oldName);
						nh.key() = newName;
						ini.group.insert(std::move(nh));
						ini.SaveFile(Con::Path_Config_Data);
					}
					SLGroup.UnlockUpdate();
					mainWindow->UpdateSubMenu();
				}
				animateMutex.unlock();
			}
			break;
		}
		case Events::SuperList::ItemMouseIn: { // 项目鼠标进入
			if (var->Config.ListWave)
				mainWindow->SLGroup.ItemHeight(row, LS::ListDefaultWaveHeight);
			break;
		}
		case Events::SuperList::ItemMouseOut: { // 项目鼠标离开
			if (var->Config.ListWave)
				mainWindow->SLGroup.ItemHeight(row, LS::ListDefaultHeight);
			break;
		}
		}
	}
	return 0;
}

// 项目列表框回调
Result __stdcall SLItemCallBack(ID id, Event msg, Arg index, Arg, Arg, Arg) {
	switch (msg) {
	case Events::IconList::ItemLDCLick: { // 左键双击
		auto& group = var->Data[mainWindow->CurrentGroup].files;
		Process::Execute(group[index].path, group[index].arg, group[index].admin);
		break;
	}
	case Events::IconList::ItemRCLick: { // 右键单击
		mainWindow->SLItem.CurrentItem(index);
		mainWindow->menuItem.Open();
		break;
	}
	case Events::IconList::ItemMouseIn: { // 鼠标进入
		if (!mainWindow->ItemTip.TipShow) {
			mainWindow->ItemTip.TipList = id;
			mainWindow->ItemTip.TipIndex = index;
			mainWindow->ItemTip.Clk.Start(1000);
		}
		break;
	}
	case Events::IconList::ItemMouseOut: { // 鼠标离开
		mainWindow->ItemTip.Clk.Stop();
		if (mainWindow->ItemTip.TipShow) {
			mainWindow->ItemTip.TipList = 0;
			mainWindow->ItemTip.Tip.Start(0);
			mainWindow->ItemTip.TipShow = false;
		}
		break;
	}
	}
	return 0;
}

// 分组菜单回调
void __stdcall MainWindow::MenuGroupCallBack(Menu::Item item, Event msg, short tag) {
	if (msg == Events::Menu::Open) { mainWindow->Absorb.Can = false; return; }
	else if (msg == Events::Menu::Close) { mainWindow->Absorb.Can = true; return; }
	else [[likely]] if (msg == Events::Menu::ItemLCLick) {
		int index = mainWindow->CurrentGroup;
		auto& SLGroup = mainWindow->SLGroup;
		auto& SLItem = mainWindow->SLItem;
		switch (tag) {
		case 0: { // 删除
			String name = var->Data[index].name;
			var->Data.erase(var->Data.cbegin() + index);
			int size = var->Data.size();
			SLGroup.DeleteItem(index);
			SLGroup.CurrentItem(0);
			if (size > 0) {
				mainWindow->CurrentGroup = 0;
				mainWindow->UpdateItemList();
			}
			else {
				mainWindow->CurrentGroup = -1;
				SLItem.ClearItem();
			}
			mainWindow->UpdateSubMenu();
			// [写磁盘]
			Ini ini; ini.LoadFile(Con::Path_Config_Settings);
			auto& section = ini[LS::IniData];
			for (int i = index; i < size; ++i)
				std::swap(section[ToString(i)], section[ToString(i + 1)]);
			auto size_str = ToString(size);
			section.erase(size_str);
			section[LS::IniCount] = size_str;
			ini.SaveFile(Con::Path_Config_Settings);
			ini.LoadFile(Con::Path_Config_Data);
			ini.group.erase(name);
			ini.SaveFile(Con::Path_Config_Data);
			break;
		}
		case 1: { // 上移
			if (index > 0) {
				std::swap(var->Data[index - 1], var->Data[index]);
				SLGroup.ItemTitle(index - 1, 0, var->Data[index - 1].name);
				SLGroup.ItemTitle(index, 0, var->Data[index].name);
				mainWindow->CurrentGroup = index - 1;
				SLGroup.CurrentItem(index - 1);
				mainWindow->UpdateSubMenu();
				// [写磁盘]
				Ini ini; ini.LoadFile(Con::Path_Config_Settings);
				auto& section = ini[LS::IniData];
				section[ToString(index - 1)] = var->Data[index - 1].name;
				section[ToString(index)] = var->Data[index].name;
				ini.SaveFile(Con::Path_Config_Settings);
			}
			break;
		}
		case 2: { // 下移
			if (index >= 0 && index < var->Data.size() - 1) {
				std::swap(var->Data[index], var->Data[index + 1]);
				SLGroup.ItemTitle(index, 0, var->Data[index].name);
				SLGroup.ItemTitle(index + 1, 0, var->Data[index + 1].name);
				mainWindow->CurrentGroup = index + 1;
				SLGroup.CurrentItem(index + 1);
				mainWindow->UpdateSubMenu();
				// [写磁盘]
				Ini ini; ini.LoadFile(Con::Path_Config_Settings);
				auto& section = ini[LS::IniData];
				section[ToString(index)] = var->Data[index].name;
				section[ToString(index + 1)] = var->Data[index + 1].name;
				ini.SaveFile(Con::Path_Config_Settings);
			}
			break;
		}
		}
	}
}

// 项目菜单回调
void __stdcall MainWindow::MenuItemCallBack(Menu::Item item, Event msg, short tag) {
	if (msg == Events::Menu::Open) { mainWindow->Absorb.Can = false; return; }
	else if (msg == Events::Menu::Close) { mainWindow->Absorb.Can = true; return; }
	else [[likely]] if (msg == Events::Menu::ItemLCLick) {
		auto& group = var->Data[mainWindow->CurrentGroup].files;
		auto& SLItem = mainWindow->SLItem;
		auto index = SLItem.CurrentItem();
		switch (tag) {
		case 0: { // 管理员身份运行
			Process::Execute(group[index].path, group[index].arg, group[index].admin);
			break;
		}
		case 1: { // 打开文件位置
			auto pos = group[index].path.rfind(LS::Separator);
			Process::Execute(group[index].path.substr(0, pos));
			break;
		}
		case 2: { // 复制完整路径
			ClipBoard::SetString(group[index].path);
			Toast(2000, LS::Tip_CopyPathOK);
			break;
		}
		case 3: { // 编辑
			mainWindow->Modify.index = index;
			mainWindow->Modify.entry = &group[index];
			ModifyItem();
			break;
		}
		case 4: { // 删除
			group.erase(group.cbegin() + index);
			int size = group.size();
			SLItem.LockUpdate();
			SLItem.DeleteItem(index);
			if (size > 0) SLItem.CurrentItem(0);
			SLItem.UnlockUpdate();
			// [写磁盘]
			Ini ini; ini.LoadFile(Con::Path_Config_Data);
			auto& section = ini[var->Data[mainWindow->CurrentGroup].name];
			for (int i = index; i < size; ++i)
				std::swap(section[ToString(i)], section[ToString(i + 1)]);
			auto size_str = ToString(size);
			section.erase(size_str);
			section[LS::IniCount] = size_str;
			ini.SaveFile(Con::Path_Config_Data);
			break;
		}
		case 5: break; // 移动到其他分组
		case 6: { // 前移
			if (index > 0) {
				std::swap(group[index - 1], group[index]);
				SLItem.ItemIcon(index - 1, group[index - 1].ico);
				SLItem.ItemTitle(index - 1, group[index - 1].name);
				SLItem.ItemIcon(index, group[index].ico);
				SLItem.ItemTitle(index, group[index].name);
				SLItem.CurrentItem(index - 1);
				// [写磁盘]
				Ini ini; ini.LoadFile(Con::Path_Config_Data);
				auto& section = ini[var->Data[mainWindow->CurrentGroup].name];
				section[ToString(index - 1)] = SaveFileEntry(group[index - 1]);
				section[ToString(index)] = SaveFileEntry(group[index]);
				ini.SaveFile(Con::Path_Config_Data);
			}
			break;
		}
		case 7: { // 后移
			if (index >= 0 && index < group.size() - 1) {
				std::swap(group[index], group[index + 1]);
				SLItem.ItemIcon(index, group[index].ico);
				SLItem.ItemTitle(index, group[index].name);
				SLItem.ItemIcon(index + 1, group[index + 1].ico);
				SLItem.ItemTitle(index + 1, group[index + 1].name);
				SLItem.CurrentItem(index + 1);
				// [写磁盘]
				Ini ini; ini.LoadFile(Con::Path_Config_Data);
				auto& section = ini[var->Data[mainWindow->CurrentGroup].name];
				section[ToString(index)] = SaveFileEntry(group[index]);
				section[ToString(index + 1)] = SaveFileEntry(group[index + 1]);
				ini.SaveFile(Con::Path_Config_Data);
			}
			break;
		}
		default: { // 移动到其他分组(子菜单)
			if (int pos = tag - 500; pos != mainWindow->CurrentGroup) {
				auto& newGroup = var->Data[pos].files;
				newGroup.push_back({}); auto& newEntry = newGroup.back();
				auto& oldEntry = group[index];
				std::swap(newEntry, oldEntry);
				group.erase(group.cbegin() + index);
				int size = group.size(), newSize = newGroup.size();
				SLItem.LockUpdate();
				SLItem.DeleteItem(index);
				if (size > 0) SLItem.CurrentItem(0);
				SLItem.UnlockUpdate();
				// [写磁盘]
				Ini ini; ini.LoadFile(Con::Path_Config_Data);
				auto& section = ini[var->Data[mainWindow->CurrentGroup].name];
				auto& newSection = ini[var->Data[pos].name];
				for (int i = index; i < size; ++i)
					std::swap(section[ToString(i)], section[ToString(i + 1)]);
				auto size_str = ToString(size);
				newSection[ToString(newSize - 1)] = section[size_str];
				newSection[LS::IniCount] = ToString(newSize);
				section.erase(size_str);
				section[LS::IniCount] = size_str;
				ini.SaveFile(Con::Path_Config_Data);
			}
			break;
		}
		}
	}
}

void MainWindow::LazyLoadPageProgram() noexcept {
	var->vds[L"CallBack.EditButton"] = &EditButtonCallBack;
	var->vds[L"CallBack.SLGroup"] = &SLGroupCallBack;
	var->vds[L"CallBack.SLItem"] = &SLItemCallBack;
	auto id = Group(Layout::InflateControl(*mainWindow, res->Layout.pageProgram, var->vds));
	mainWindow->Tabs[0] = id;
	mainWindow->CurrentGroup = 0;
	mainWindow->SLGroup = (SuperList)id(L"SLGroup");
	auto SLGroup = mainWindow->SLGroup;
	SLGroup.InsertColumn(-1, {}, Color::White, SLGroup.Width(), Attrs::ItemAlign::Center, 0, 0, res->Font.MSBlack.S16);
	for (GroupEntry& i : var->Data) SLGroup.ItemTitle(SLGroup.InsertItem(), 0, i.name);
	SLGroup.ItemTitle(mainWindow->SLGroup.InsertItem(), 0, Con::AddSign);
	SLGroup.ItemFontColor(-1, -1, Color::White);
	SLGroup.CurrentItem(0);
	mainWindow->Modify.EditGroup = (Group)id(L"EditGroup");
	mainWindow->Modify.isModify = false;
	mainWindow->Modify.entry = nullptr;
	mainWindow->Modify.index = -1;
	mainWindow->SLItem = (IconList)id(L"SLItem");
	mainWindow->UpdateItemList();
	mainWindow->ItemTip.Tip.FontColor(Color::White).Font(res->Font.MSBlack.SL16)
		.Align(Attrs::Align::Start_Center_Mul).Transparency(200);
}

void MainWindow::UpdatePageProgram() noexcept { }