#pragma once

struct MainWindow : Window {
	int CurrentPage = 0; // 当前页面
	int CurrentGroup = 0; // 当前分组

	struct {
		Clock Clk; // 吸附时钟
		volatile bool Mutex = false; // 吸附锁
		volatile bool Can = false; // 是否能吸附
		volatile bool Is = false; // 是否已吸附
	}Absorb; // 吸附

	struct __ItemTip {
		IconList TipList;
		Clock Clk; // 提示时钟
		TipBox Tip = TipBox(200, 50); // 提示框
		bool TipShow = false; // 是否提示
		int TipIndex = 0; // 提示索引
		void StartClock() noexcept;
	}ItemTip;

	struct {
		std::unordered_map<String, int> PreviewMap; // 文件预览映射
		String currentNode; // 目录树当前位置
		String currentCopy; // 目录树当前拷贝路径
		bool currentCopyX = false; // 目录树拷贝是否剪切
		IconList list; // 目录树列表
		Group Property; // 属性框
		bool isShowProperty = false; // 是否显示属性
	}Tree;

	struct __Plugin {
		std::vector<Plugin> data; // 插件组
		SystemCall sys; // 系统调用
		SuperList list; // 插件列表
		Clock Clk; // 提示时钟
		TipBox Tip = TipBox(250, 100); // 提示框
		bool TipShow = false; // 是否提示
		int TipIndex = 0; // 提示索引
		void StartClock() noexcept;
	}Plugin;

	struct __File {
		String basePath; // 根目录
		std::unordered_map<String, ICO> cache; // 文件池缓存
		SuperList list; // 文件列表
		volatile bool mutex = true; // 互斥锁
	}File;

	Tray TrayObject; // 托盘
	Drag DragObject; // 拖放

	Menu menuGroup, menuItem; // 分组菜单, 项目菜单
	Menu menuTray; // 托盘菜单
	Menu menuTree, menuTreeDisk; // 目录树菜单, 目录树驱动器菜单
	Menu menuPlugin; // 插件菜单
	Menu menuFile; // 文件菜单

	IconList Tab; // Tab栏
	std::vector<Group> Tabs; // Tab组
	std::vector<void(*)()> lazyFun; // 懒加载向量表
	SuperList SLGroup; // 分组列表
	IconList SLItem; // 项目列表
	
	struct {
		Group EditGroup; // 编辑项目框
		bool isModify = false; // 是否正在修改
		FileEntry* entry = nullptr; // 正在修改的文件
		int index = -1; // 文件索引
	}Modify;

	IconList SLSystem; // 系统工具列表

	void InitMenu() noexcept; // 初始化菜单
	void DestroyMenu() noexcept; // 销毁菜单
	void UpdateSubMenu() noexcept; // 刷新子菜单
	bool CanModifyGroupName(ConstString oldName, ConstString newName) const noexcept; // 能否修改分组名
	void UpdateItemList() noexcept; // 刷新项目列表
	void ProgramDragFiles(Drag::DragPath paths, int count) noexcept; // 程序页面获得拖拽文件
	void FreePlugins() noexcept; // 释放插件

	void FileDragFiles(Drag::DragPath paths, int count) noexcept; // 文件页面获得拖拽文件

	static void __stdcall MenuTrayCallBack(Menu::Item item, Event msg, short tag);
	static void __stdcall MenuGroupCallBack(Menu::Item item, Event msg, short tag);
	static void __stdcall MenuItemCallBack(Menu::Item item, Event msg, short tag);
	static void __stdcall MenuTreeCallBack(Menu::Item item, Event msg, short tag);
	static void __stdcall MenuTreeDiskCallBack(Menu::Item item, Event msg, short tag);
	static void __stdcall MenuPluginCallBack(Menu::Item item, Event msg, short tag);
	static void __stdcall MenuFileCallBack(Menu::Item item, Event msg, short tag);

	static void LazyLoadPageProgram() noexcept; // 懒加载程序页面
	static void UpdatePageProgram() noexcept; // 更新程序页面
	static void LazyLoadPageSystem() noexcept; // 懒加载系统页面
	static void UpdatePageSystem() noexcept; // 更新系统页面
	static void LazyLoadPageTree() noexcept; // 懒加载目录树页面
	static void UpdatePageTree() noexcept; // 更新系统页面
	static void LazyLoadPagePlugin() noexcept; // 懒加载插件页面
	static void UpdatePagePlugin() noexcept; // 更新系统页面
	static void LazyLoadPageFile() noexcept; // 懒加载文件集页面
	static void UpdatePageFile() noexcept; // 更新文件集页面
};