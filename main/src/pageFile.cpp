#include "../include/pdlmh.h"
#include "../include/util.h"
#include <filesystem>

// 载入文件池
void LoadFileCache() noexcept {
	namespace fs = std::filesystem;
	try {
		for (auto& item : fs::directory_iterator(mainWindow->File.basePath)) {
			if (item.is_regular_file()) {
				auto fn = item.path().filename().wstring();
				mainWindow->File.cache[fn] = GetFileExtraTypeIcon(item.path().wstring());
			}
		}
	}
	catch (fs::filesystem_error&) {}
}

// 部分匹配模糊查询
constexpr bool PartMatchSearch(ConstString key, ConstString keyword) noexcept {
	return key.find(keyword) != String::npos;
}

// 模糊查询文件池
void SearchAmbiguousFileCache(ConstString keyword, decltype(&PartMatchSearch) cmp = nullptr) noexcept {
	SuperList& list = mainWindow->File.list;
	list.LockUpdate();
	int pos = 0, size = list.ItemCount();
	for (auto& [key, ico] : mainWindow->File.cache) {
		if (cmp && !cmp(key, keyword)) continue;
		if (pos >= size) list.InsertItem();
		list.ItemIcon(pos, 0, ico);
		list.ItemTitle(pos, 1, key);
		list.ItemFontColor(pos, 1, Color::White);
		++pos;
	}
	if (pos < size) list.DeleteItem(pos, size - pos);
	list.UnlockUpdate();
}

// 查询文件池
void SearchFileCache(ConstString key = {}) noexcept {
	if (mainWindow->File.mutex) {
		mainWindow->File.mutex = false;
		if (key.empty()) SearchAmbiguousFileCache(key);
		else SearchAmbiguousFileCache(key, &PartMatchSearch);
		mainWindow->File.mutex = true;
	}
}

// 获得拖拽文件
void MainWindow::FileDragFiles(Drag::DragPath paths, int count) noexcept {
	if (mainWindow->File.mutex) {
		mainWindow->File.mutex = false;
		mainWindow->File.list.LockUpdate();
		int sameCount = 0, folderCount = 0;
		for (int i = 0; i < count; ++i) {
			auto fn = paths[i]; int type;
			auto ico = GetFileExtraTypeIcon(fn, &type);
			if (type != 2) {
				wchar_t name[_MAX_FNAME]{}, ext[_MAX_EXT]{};
				_wsplitpath_s(fn, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
				lstrcatW(name, ext);
				if (CopyFileW(fn, (mainWindow->File.basePath + name).data(), true)) {
					mainWindow->File.cache[name] = ico;
					auto pos = mainWindow->File.list.InsertItem();
					mainWindow->File.list.ItemIcon(pos, 0, ico);
					mainWindow->File.list.ItemTitle(pos, 1, name);
					mainWindow->File.list.ItemFontColor(pos, 1, Color::White);
				}
				else ++sameCount;
			}
			else ++folderCount;
		}
		mainWindow->File.list.UnlockUpdate();
		if (sameCount || folderCount)
			Toast(2000, ToString(L"已过滤", sameCount, L"个重复文件,", folderCount, L"个文件夹"));
		mainWindow->File.mutex = true;
	}
	else Toast(2000, L"引擎正在处理,请稍后再添加文件");
}

Result __stdcall FileInfoCallBack(ID id, Event msg, Arg, Arg, Arg, Arg) {
	if (msg == Events::Control::LClick) {
		mainWindow->Absorb.Can = false;
		MsgBox::Start(LS::SoftwareNameString, LS::Tip_FileCache, { L"确定" }, res->Image.Icon);
		mainWindow->Absorb.Can = true;
	}
	return 0;
}

Result __stdcall FileSearchCallBack(ID id, Event msg, Arg, Arg, Arg, Arg) {
	if (msg == Events::Edit::ContentChange) SearchFileCache(Edit(id).Content());
	return 0;
}

Result __stdcall FileListCallBack(ID id, Event msg, Arg row, Arg col, Arg, Arg source) {
	if (source == Attrs::ListEventSource::Item) {
		switch (msg) {
		case Events::SuperList::ItemLDCLick: {
			Process::Execute(mainWindow->File.basePath +
				mainWindow->File.list.ItemTitle(row, 1));
			break;
		}
		case Events::SuperList::ItemRCLick: {
			mainWindow->File.list.CurrentItem(row);
			mainWindow->menuFile.Open();
			break;
		}
		case Events::SuperList::ItemMouseIn: {
			if (var->Config.ListWave) mainWindow->File.list.ItemHeight(row, LS::ListDefaultWaveHeight);
			break;
		}
		case Events::SuperList::ItemMouseOut: {
			if (var->Config.ListWave) mainWindow->File.list.ItemHeight(row, LS::ListDefaultHeight);
			break;
		}
		}
	}
	return 0;
}

void __stdcall MainWindow::MenuFileCallBack(Menu::Item item, Event msg, short tag) {
	if (msg == Events::Menu::Open) { mainWindow->Absorb.Can = false; return; }
	else if (msg == Events::Menu::Close) { mainWindow->Absorb.Can = true; return; }
	else if (msg == Events::Menu::ItemLCLick) {
		auto& list = mainWindow->File.list;
		auto index = list.CurrentItem();
		auto title = list.ItemTitle(index, 1);
		switch (tag) {
		case 0: { // 删除
			if (DeleteFileW((mainWindow->File.basePath + title).data())) {
				mainWindow->File.cache.erase(title);
				list.DeleteItem(index);
			}
			break;
		}
		case 1: { // 重命名
			mainWindow->Absorb.Can = false;
			auto newName = list.InputAt(index, 1, Attrs::ItemAlign::Center,
				res->Font.MSBlack.S16, Color::Black, res->Skin.Edit);
			mainWindow->Absorb.Can = true;
			if (!newName.empty() && newName != title) {
				MoveFileW((mainWindow->File.basePath + title).data(),
					(mainWindow->File.basePath + newName).data());
				auto node = mainWindow->File.cache.extract(title);
				node.key() = newName;
				mainWindow->File.cache.insert(std::move(node));
				list.ItemTitle(index, 1, newName);
			}
			break;
		}
		case 2: { // 引用到剪贴板
			ClipBoard::SetFile({ mainWindow->File.basePath + title });
			break;
		}
		case 3: { // 另存为
			auto fn = mainWindow->File.basePath + title;
			wchar_t ext[_MAX_EXT] = { L'*', 0 };
			_wsplitpath_s(fn.data(), nullptr, 0, nullptr, 0, nullptr, 0, ext + 1, _MAX_EXT);
			mainWindow->Absorb.Can = false;
			auto newFn = FileBox::Save(L"另存为文件", {}, { {ext, ext}});
			mainWindow->Absorb.Can = true;
			if (!newFn.empty()) CopyFileW(fn.data(), newFn.data(), false);
			break;
		}
		case 4: { // 提取
			auto fn = mainWindow->File.basePath + title;
			wchar_t ext[_MAX_EXT] = { L'*', 0 };
			_wsplitpath_s(fn.data(), nullptr, 0, nullptr, 0, nullptr, 0, ext + 1, _MAX_EXT);
			mainWindow->Absorb.Can = false;
			auto newFn = FileBox::Save(L"提取文件", {}, { {ext, ext} });
			mainWindow->Absorb.Can = true;
			if (!newFn.empty()) {
				if (MoveFileW(fn.data(), newFn.data())) {
					mainWindow->File.cache.erase(title);
					list.DeleteItem(index);
				}
			}
			break;
		}
		}
	}
}

void MainWindow::LazyLoadPageFile() noexcept {
	mainWindow->LockUpdate();
	var->vds[L"CallBack.FileInfo"] = &FileInfoCallBack;
	var->vds[L"CallBack.FileSearch"] = &FileSearchCallBack;
	var->vds[L"CallBack.FileList"] = &FileListCallBack;
	var->vds[L"Image.Info"] = res->Image.Info;
	mainWindow->Tabs[4] = Group(Layout::InflateControl(*mainWindow, res->Layout.pageFile, var->vds));
	mainWindow->File.mutex = true;
	auto list = (SuperList)mainWindow->Tabs[4](L"FileList");
	mainWindow->File.list = list;
	list.InsertColumn(-1, {}, 0, 40, Attrs::ItemAlign::Center, 32, 32);
	list.InsertColumn(-1, {}, Color::White, 395, Attrs::ItemAlign::Center, 0, 0, res->Font.MSBlack.SL16);
	mainWindow->File.basePath = var->AppData + LS::Separator + L"FileCache" + LS::Separator;
	Path::MakesureFolder(mainWindow->File.basePath);
	LoadFileCache();
	mainWindow->UnlockUpdate();
	SearchFileCache();
}

void MainWindow::UpdatePageFile() noexcept { }