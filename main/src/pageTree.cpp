#include "../include/pdlmh.h"
#include "../include/util.h"

#include <ShlObj.h>
#include <queue>
#include <filesystem>

// 更新驱动器目录树
void UpdateDiskTreeList() noexcept {
	auto& treeList = mainWindow->Tree.list;
	auto ls = System::GetDriversList();
	mainWindow->Tree.currentNode.clear();
	treeList.LockUpdate();
	treeList.ClearItem();
	for (auto& i : ls) {
		UINT driveType = GetDriveTypeW((i + LS::Separator).data());
		treeList.InsertItem(-1, i, res->Ico.Drive[driveType], Color::White, 0);
	}
	treeList.UnlockUpdate();
}

// 更新目录树
void UpdateTreeList() noexcept {
	constexpr auto ALL_ATTRIBUTE = 
		FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_DIRECTORY |
		FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL |
		FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM;
	auto& treeList = mainWindow->Tree.list;
	treeList.LockUpdate();
	int pos = 0, size = treeList.ItemCount();
	try {
		std::filesystem::path pt(mainWindow->Tree.currentNode);
		for (auto& subPathEntry : std::filesystem::directory_iterator(pt)) {
			auto& subPath = subPathEntry.path();
			if (DWORD attr = GetFileAttributesW(subPath.c_str());
				attr != INVALID_FILE_ATTRIBUTES) {
				if ((attr & var->Config.FolderTreeFilter) &&
					!(attr & (ALL_ATTRIBUTE - var->Config.FolderTreeFilter))) {
					if (pos >= size) treeList.InsertItem();
					if ((attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY) {
						treeList.ItemIcon(pos, res->Ico.Default[2]);
						treeList.ItemData(pos, 2);
					}
					else {
						treeList.ItemIcon(pos, GetFileExtraTypeIcon(subPath.wstring()));
						treeList.ItemData(pos, 1);
					}
					treeList.ItemTitle(pos, subPath.filename().wstring());
					++pos;
				}
			}
		}
		if (pos < size) treeList.DeleteItem(pos, size - pos);
		treeList.ItemFontColor(-1, Color::White);
	}
	catch (std::filesystem::filesystem_error&) {}
	treeList.UnlockUpdate();
}

// 文件时间转字符串
String TimeToString(time_t time) noexcept {
	tm ttt;
	_localtime64_s(&ttt, &time);
	return ToString(1900 + ttt.tm_year, L"年", 1 + ttt.tm_mon, L"月", ttt.tm_mday, L"日",
		ttt.tm_hour, L"时", ttt.tm_min, L"分", ttt.tm_sec, L"秒");
}

// 文件大小转字符串
String SizeToString(uintmax_t size) noexcept {
	String sizeBStr = ToString(L" (", size, L"字节)");
	auto fSize = static_cast<long double>(size);
	String sizeStr = ToString(size) + L"B";
	if (fSize > 1024.0L) { fSize /= 1024.0L; sizeStr = ToString(fSize) + L"KB"; }
	if (fSize > 1024.0L) { fSize /= 1024.0L; sizeStr = ToString(fSize) + L"MB"; }
	if (fSize > 1024.0L) { fSize /= 1024.0L; sizeStr = ToString(fSize) + L"GB"; }
	return sizeStr + sizeBStr;
}

// 取文件夹目录数/文件数/大小
auto GetFolderCountAndSize(ConstString dir) noexcept {
	using namespace std::filesystem;
	uintmax_t size = 0ull; int dirCount = 0, fileCount = 0; bool over = false;
	std::queue<path, std::list<path>> dirQueue;
	dirQueue.push(dir);
	while (!dirQueue.empty()) {
		auto& p = dirQueue.front();
		if (is_directory(p)) {
			for (auto& i : directory_iterator(p)) dirQueue.push(i);
			++dirCount;
		}
		else {
			size += file_size(p);
			++fileCount;
		}
		dirQueue.pop();
		if (dirCount > 2000 || fileCount > 12000 || size > 2ull * 1024ull * 1024ull * 1024ull) {
			over = true;
			break;
		}
	}
	return std::make_tuple(dirCount - 1, fileCount, size, over);
}

// 取驱动器属性
auto GetDirverInfo(ConstString drive) {
	static const String driveTypeMap[] = { L"未知磁盘类型", L"无此驱动器", L"可移动磁盘",
		L"本地磁盘", L"网络磁盘", L"光驱", L"RAM" };
	UINT driveType = GetDriveTypeW(drive.data());
	wchar_t fileSystem[MAX_PATH]{}, driveName[MAX_PATH]{};
	GetVolumeInformationW(drive.data(), driveName, MAX_PATH, nullptr, nullptr,
		nullptr, fileSystem, MAX_PATH);
	ULONG sector{}, bytes{}, cluster{}, all_cluster{};
	GetDiskFreeSpaceW(drive.data(), &sector, &bytes, &cluster, &all_cluster);
	double m = bytes / 1024.0 * sector;
	return std::make_tuple(String(driveName), String(fileSystem), driveType,
		driveTypeMap[driveType], all_cluster * m / 1024 / 1024, cluster * m / 1024 / 1024);
}

// 显示文件属性
void ShowFileProperty(ConstString name, ConstString path, int type, ICO ico) noexcept {
	namespace fs = std::filesystem;
	auto& group = mainWindow->Tabs[2];
	mainWindow->Tree.Property = (Group)group(ToString(type));
	auto& Property = mainWindow->Tree.Property;
	mainWindow->Tree.isShowProperty = true;
	mainWindow->Tree.list.Visual(false);
	group(L"TreeTab").Visual(false);
	Property.LockUpdate();
	switch (type) {
	case 0: { // 驱动器
		auto [driveName, fileSystem, driveType, typeStr, totalSize, freeSize]
			= GetDirverInfo(path + LS::Separator);
		((Picture)Property(L"DriveIcon")).Image(res->Image.Drive[driveType]);
		((Label)Property(L"DriveName")).Title(path + L"    " + driveName);
		((Label)Property(L"DriveFileSystem")).Title(L"文件系统:      " + fileSystem);
		((Label)Property(L"DriveType")).Title(L"磁盘类型:      " + typeStr);
		((Label)Property(L"DriveTotalSize")).Title(ToString(L"磁盘容量:    ", totalSize, L"G"));
		((Label)Property(L"DriveFreeSize")).Title(ToString(L"剩余容量:    ", freeSize, L"G"));
		((Progress)Property(L"DriveProgress")).Pos(static_cast<int>((totalSize - freeSize) * 100 / totalSize));
		break;
	}
	case 1: { // 文件
		((Picture)Property(L"FileIcon")).Image(ico.ToBin());
		((Label)Property(L"FileName")).Title(name);
		((Label)Property(L"FilePath")).Title(path);
		try {
			((Label)Property(L"FileSize")).Title(SizeToString(fs::file_size(path)));
		}
		catch (fs::filesystem_error&) {}
		struct _stat64 t; _wstat64(path.data(), &t);
		((Label)Property(L"FileCreateTime")).Title(TimeToString(t.st_ctime));
		((Label)Property(L"FileModifyTime")).Title(TimeToString(t.st_mtime));
		((Label)Property(L"FileAccessTime")).Title(TimeToString(t.st_atime));
		break;
	}
	case 2: { // 目录
		((Picture)Property(L"FileIcon")).Image(ico.ToBin());
		((Label)Property(L"FileName")).Title(name);
		((Label)Property(L"FilePath")).Title(path);
		try {
			auto [dirCount, fileCount, size, over] = GetFolderCountAndSize(path);
			((Label)Property(L"FileContain")).Title(
				ToString(over ? L"超过" : L"", fileCount, L"个文件, ",
					over ? L"超过" : L"", dirCount, L"个文件夹"));
			((Label)Property(L"FileSize")).Title(
				ToString(over ? L"超过" : L"", SizeToString(size)));
		}
		catch (fs::filesystem_error&) {}
		struct _stat64 t; _wstat64(path.data(), &t);
		((Label)Property(L"FileCreateTime")).Title(TimeToString(t.st_ctime));
		((Label)Property(L"FileModifyTime")).Title(TimeToString(t.st_mtime));
		((Label)Property(L"FileAccessTime")).Title(TimeToString(t.st_atime));
		break;
	}
	}
	Property.Visual(true);
	Property.UnlockUpdate();
}

// 预览文本文件
void PreviewTextFile(ConstString path, Group group) noexcept {
	bool result = false;
	uintmax_t size = 0ull;
	try {
		size = std::filesystem::file_size(path);
		if (size > 0ull && size < 1024ull * 1024ull) result = true;
	}
	catch (std::filesystem::filesystem_error&) { }
	Edit edit = (Edit)group(L"text");
	if (result) edit.Content(File::ReadString(path));
	else if (size == 0ull) edit.Content({});
	else edit.Content(L"文本过长不支持预览...");
}

// 预览图片文件
void PreviewImageFile(ConstString path, Group group) noexcept {
	bool result = false;
	try {
		auto size = std::filesystem::file_size(path);
		if (size > 0ull && size < 1024ull * 1024ull * 4ull) result = true;
	}
	catch (std::filesystem::filesystem_error&) {}
	Picture pic = (Picture)group(L"image");
	if (result) pic.Image(File::ReadBin(path));
	else {
		pic.Image({});
		Toast(2000, L"图片太大不支持预览");
	}
}

// 预览文件
void PreviewFile(ConstString path) noexcept {
	static const std::tuple<decltype(&PreviewTextFile), String> PreviewArray[] = {
		{ &PreviewTextFile, L"PreviewTextFile" },
		{ &PreviewImageFile, L"PreviewImageFile" },
	};
	wchar_t ext[_MAX_EXT]{};
	_wsplitpath_s(path.data(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
	if (auto iter = mainWindow->Tree.PreviewMap.find(ext);
		iter != mainWindow->Tree.PreviewMap.cend()) {
		if (auto index = iter->second; index < sizeof(PreviewArray) / sizeof(decltype(*PreviewArray))) {
			auto& [PreviewFunc, PreviewId] = PreviewArray[index];
			auto& group = mainWindow->Tabs[2];
			Group Property = (Group)group(PreviewId);
			mainWindow->Tree.Property = Property;
			mainWindow->Tree.isShowProperty = true;
			mainWindow->Tree.list.Visual(false);
			group(L"TreeTab").Visual(false);
			Property.LockUpdate();
			PreviewFunc(path, Property);
			Property.Visual(true);
			Property.UnlockUpdate();
		}
	}
	else Toast(2000, L"此格式文件暂不支持预览");
}

// 属性取消回调
Result __stdcall CancelPropertyCallBack(ID id, Event msg, Arg, Arg, Arg, Arg) {
	if (msg == Events::Control::LClick) {
		if (mainWindow->Tree.Property) {
			mainWindow->Tree.isShowProperty = false;
			mainWindow->Tree.Property.Visual(false);
			mainWindow->Tree.Property = 0;
			mainWindow->Tree.list.Visual(true);
			mainWindow->Tabs[2](L"TreeTab").Visual(true);
		}
	}
	return 0;
}

// 目录树快捷按钮回调
Result __stdcall TreeButtonCallBack(ID id, Event msg, Arg index, Arg, Arg, Arg) {
	switch (msg) {
	case Events::IconList::ItemLCLick: {
		static Mutex mutex;
		if (mutex.lock()) {
			IconList list(id);
			list.CurrentItem(-1);
			auto& treeList = mainWindow->Tree.list;
			auto& currentNode = mainWindow->Tree.currentNode;
			switch (index) {
			case 0: { // 返回上一级
				if (!currentNode.empty()) {
					auto i = currentNode.rfind(LS::Separator, currentNode.size() - 2);
					if (i == String::npos) UpdateDiskTreeList();
					else {
						currentNode = currentNode.substr(0, i + 1);
						UpdateTreeList();
					}
				}
				break;
			}
			case 1: { // 新建文件夹
				if (!currentNode.empty()) {
					mainWindow->Absorb.Can = false;
					auto name = InputBox::Start(LS::SoftwareNameString, LS::Tip_InputFolderName,
						{ LS::ButtonTitleOK, LS::ButtonTitleCancel }, res->Image.Icon);
					mainWindow->Absorb.Can = true;
					if (!name.empty() && name.find(LS::Separator) == String::npos) {
						std::filesystem::path newDir(currentNode + name);
						if (std::filesystem::exists(newDir)) Toast(2000, LS::Tip_FolderExists);
						else {
							std::filesystem::create_directory(newDir);
							treeList.LockUpdate();
							treeList.InsertItem(-1, name, res->Ico.Default[1], Color::White, 2);
							treeList.CurrentItem(0);
							treeList.UnlockUpdate();
						}
					}
				}
				break;
			}
			case 2: { // 定位桌面目录
				currentNode = Path::GetPath(Path::Desktop) + LS::Separator;
				UpdateTreeList();
				break;
			}
			}
			mutex.unlock();
		}
		break;
	}
	}
	return 0;
}

// 目录树列表按钮回调
Result __stdcall TreeListCallBack(ID id, Event msg, Arg index, Arg, Arg, Arg) {
	IconList treeList(id);
	switch (msg) {
	case Events::IconList::ItemLDCLick: {
		static Mutex mutex;
		if (mutex.lock()) {
			String path = mainWindow->Tree.currentNode + treeList.ItemTitle(index);
			if (treeList.ItemData(index) == 1) Process::Execute(path);
			else {
				mainWindow->Tree.currentNode = path + LS::Separator;
				UpdateTreeList();
			}
			mutex.unlock();
		}
		break;
	}
	case Events::IconList::ItemRCLick: {
		treeList.CurrentItem(index);
		auto data = treeList.ItemData(index);
		if (data > 0) mainWindow->menuTree.Open();
		else if (data == 0) mainWindow->menuTreeDisk.Open();
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

// 目录树菜单回调
void __stdcall MainWindow::MenuTreeCallBack(Menu::Item item, Event msg, short tag) {
	if (msg == Events::Menu::Open) { mainWindow->Absorb.Can = false; return; }
	else if (msg == Events::Menu::Close) { mainWindow->Absorb.Can = true; return; }
	else [[likely]] if (msg == Events::Menu::ItemLCLick) {
		namespace fs = std::filesystem;
		auto& treeList = mainWindow->Tree.list;
		auto index = treeList.CurrentItem();
		auto& currentNode = mainWindow->Tree.currentNode;
		auto& currentCopy = mainWindow->Tree.currentCopy;
		auto& currentCopyX = mainWindow->Tree.currentCopyX;
		switch (tag) {
		case 0: { // 预览
			if (!mainWindow->Tree.isShowProperty && treeList.ItemData(index) == 1)
				PreviewFile(currentNode + treeList.ItemTitle(index));
			break;
		}
		case 1: Process::Execute(currentNode); break; // 打开文件位置
		case 2: { // 复制完整路径
			ClipBoard::SetString(currentNode + treeList.ItemTitle(index));
			Toast(2000, LS::Tip_CopyPathOK);
			break;
		}
		case 3: { // 复制
			currentCopy = currentNode + treeList.ItemTitle(index);
			currentCopyX = false;
			break;
		}
		case 4: { // 剪切
			currentCopy = currentNode + treeList.ItemTitle(index);
			currentCopyX = true;
			break;
		}
		case 5: { // 粘贴进此目录
			if (!currentCopy.empty()) {
				auto pasteDir = currentNode + treeList.ItemTitle(index);
				if (fs::exists(pasteDir) && fs::is_directory(pasteDir)) {
					try {
						fs::path copyPath(currentCopy);
						fs::path pastePath(pasteDir / copyPath.filename());
						bool doTask = true, overwrite = false, needUpdate = false;
						if (fs::exists(pastePath)) {
							mainWindow->Absorb.Can = false;
							auto msgResult = MsgBox::Start(LS::SoftwareNameString,
								LS::Tip_OverwriteExists, { LS::ButtonTitleOK,
								LS::ButtonTitleCancel }, res->Image.Icon);
							mainWindow->Absorb.Can = true;
							if (msgResult != 0) doTask = false;
							else overwrite = true;
						}
						if (doTask) {
							if (fs::is_directory(copyPath)) {
								std::error_code code;
								fs::copy(copyPath, pastePath, (overwrite ? fs::copy_options::overwrite_existing
									: fs::copy_options::none) | fs::copy_options::recursive, code);
								if (!code && currentCopyX) {
									fs::remove_all(copyPath);
									needUpdate = true;
								}
							}
							else {
								if (currentCopyX) {
									fs::rename(copyPath, pastePath);
									needUpdate = true;
								}
								else {
									fs::copy_file(copyPath, pastePath, overwrite ?
										fs::copy_options::overwrite_existing : fs::copy_options::none);
								}
							}
							if (needUpdate) {
								String sourcePath = currentNode;
								if (sourcePath.back() == LS::Separator) sourcePath.pop_back();
								String parentPath = copyPath.parent_path().wstring();
								if (parentPath.back() == LS::Separator) parentPath.pop_back();
								if (sourcePath == parentPath) UpdateTreeList();
							}
						}
					}
					catch (fs::filesystem_error&) { Toast(2000, LS::Tip_FileError); }
					currentCopy.clear();
					currentCopyX = false;
				}
				else Toast(2000, LS::Tip_ChooseFolder);
			}
			else Toast(2000, LS::Tip_NoCopyTarget);
			break;
		}
		case 6: { // 重命名
			auto data = treeList.ItemData(index);
			if (data == 1 || data == 2) {
				try {
					auto oldName = treeList.ItemTitle(index);
					auto newName = InputBox::Start(LS::SoftwareNameString, LS::Tip_InputName,
						{ LS::ButtonTitleOK, LS::ButtonTitleCancel }, res->Image.Icon,
						{}, {}, oldName, Attrs::InputMode::BeginCursorTail);
					if (!newName.empty() && newName != oldName) {
						fs::rename(currentNode + oldName, currentNode + newName);
						treeList.ItemTitle(index, newName);
					}
				}
				catch (fs::filesystem_error&) { Toast(2000, LS::Tip_FileError); }
			}
			break;
		}
		case 7: { // 删除
			auto data = treeList.ItemData(index);
			auto str = currentNode + treeList.ItemTitle(index);
			try {
				fs::path fn(str);
				if (data == 1) {
					fs::remove(fn);
					treeList.DeleteItem(index);
				}
				else if (data == 2) {
					mainWindow->Absorb.Can = false;
					if (MsgBox::Start(LS::SoftwareNameString, LS::Tip_ConfirmDelete + str,
						{ LS::ButtonTitleOK, LS::ButtonTitleCancel }, res->Image.Icon) == 0) {
						fs::remove_all(fn);
						treeList.DeleteItem(index);
					}
					mainWindow->Absorb.Can = true;
				}
			}
			catch (fs::filesystem_error&) { Toast(2000, LS::Tip_FileError); }
			break;
		}
		case 8: { // 属性
			if (!mainWindow->Tree.isShowProperty) {
				String name = treeList.ItemTitle(index);
				ShowFileProperty(name, currentNode + name,
					treeList.ItemData(index), treeList.ItemIcon(index));
			}
			break;
		}
		}
	}
}

// 目录树驱动器菜单回调
void __stdcall MainWindow::MenuTreeDiskCallBack(Menu::Item item, Event msg, short tag) {
	if (msg == Events::Menu::Open) { mainWindow->Absorb.Can = false; return; }
	else if (msg == Events::Menu::Close) { mainWindow->Absorb.Can = true; return; }
	else [[likely]] if (msg == Events::Menu::ItemLCLick) {
		auto& treeList = mainWindow->Tree.list;
		auto index = treeList.CurrentItem();
		switch (tag) {
		case 0: {
			if (!mainWindow->Tree.isShowProperty)
				ShowFileProperty({}, treeList.ItemTitle(index), 0, {});
			break; // 属性
		}
		}
	}
}

void MainWindow::LazyLoadPageTree() noexcept {
	var->vds[L"Image.Close"] = res->Image.Close;
	var->vds[L"CallBack.TreeButton"] = &TreeButtonCallBack;
	var->vds[L"CallBack.TreeList"] = &TreeListCallBack;
	var->vds[L"CallBack.CancelProperty"] = &CancelPropertyCallBack;
	var->vds[L"Icon.Tree.Return"] = res->Ico.Tree.Return;
	var->vds[L"Icon.Tree.NewFolder"] = res->Ico.Tree.NewFolder;
	var->vds[L"Icon.Tree.Desktop"] = res->Ico.Tree.Desktop;
	mainWindow->LockUpdate();
	mainWindow->Tabs[2] = Layout::InflateControl(*mainWindow, res->Layout.pageTree, var->vds);
	mainWindow->UnlockUpdate();
	auto resMap = Layout::InflateMapper(res->Data.PreviewMap, {});
	for (auto& [key, value] : resMap) mainWindow->Tree.PreviewMap[key] = StringTo<int>(value);
	mainWindow->Tree.list = (IconList)mainWindow->Tabs[2](L"TreeList");
	mainWindow->Tree.currentCopyX = false;
	mainWindow->Tree.isShowProperty = false;
	UpdateDiskTreeList();
}

void MainWindow::UpdatePageTree() noexcept { }