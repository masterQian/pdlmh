#include "../include/pdlmh.h"

void MainWindow::InitMenu() noexcept {
	VDSwitcher newVds = {
		{ L"Skin.Menu", res->Skin.Menu },
		{ L"Icon.Admin", res->Ico.Menu.Admin },
		{ L"Icon.Delete", res->Ico.Menu.Delete },
		{ L"Icon.Edit", res->Ico.Menu.Edit },
		{ L"Icon.Folder", res->Ico.Menu.Folder },
		{ L"Icon.Path", res->Ico.Menu.Path },
		{ L"Icon.Exit", res->Ico.Menu.Exit },
		{ L"Icon.Able", res->Ico.Menu.Able },
		{ L"Icon.Disable", res->Ico.Menu.Disable },
		{ L"Icon.Move", res->Ico.Menu.Move },
		{ L"Icon.Copy", res->Ico.Menu.Copy },
		{ L"Icon.Cut", res->Ico.Menu.Cut },
		{ L"Icon.Paste", res->Ico.Menu.Paste },
		{ L"Icon.Property", res->Ico.Menu.Property },
		{ L"Icon.Left", res->Ico.Menu.Left },
		{ L"Icon.Right", res->Ico.Menu.Right },
		{ L"Icon.Rename", res->Ico.Menu.Rename },
		{ L"Icon.Preview", res->Ico.Menu.Preview },
		{ L"Icon.Save", res->Ico.Menu.Save },
		{ L"CallBack.MenuGroup", &MainWindow::MenuGroupCallBack },
		{ L"CallBack.MenuItem", &MainWindow::MenuItemCallBack },
		{ L"CallBack.MenuTray", &MainWindow::MenuTrayCallBack },
		{ L"CallBack.MenuTree", &MainWindow::MenuTreeCallBack },
		{ L"CallBack.MenuTreeDisk", &MainWindow::MenuTreeDiskCallBack },
		{ L"CallBack.MenuPlugin", &MainWindow::MenuPluginCallBack },
		{ L"CallBack.MenuFile", &MainWindow::MenuFileCallBack },
	};
	var->vds.merge(newVds);
	Layout::InflateMenu(menuGroup, res->Layout.MenuGroup, var->vds);
	Layout::InflateMenu(menuItem, res->Layout.MenuItem, var->vds);
	Layout::InflateMenu(menuTray, res->Layout.MenuTray, var->vds);
	Layout::InflateMenu(menuTree, res->Layout.MenuTree, var->vds);
	Layout::InflateMenu(menuTreeDisk, res->Layout.MenuTreeDisk, var->vds);
	Layout::InflateMenu(menuPlugin, res->Layout.MenuPlugin, var->vds);
	Layout::InflateMenu(menuFile, res->Layout.MenuFile, var->vds);
	UpdateSubMenu();
}

// 销毁菜单
void MainWindow::DestroyMenu() noexcept {
	menuGroup.Destroy();
	menuItem.Destroy();
	menuTray.Destroy();
	menuTree.Destroy();
	menuTreeDisk.Destroy();
	menuPlugin.Destroy();
	menuFile.Destroy();
}

// 刷新子菜单
void MainWindow::UpdateSubMenu() noexcept {
	auto subItem = menuItem.Child(5);
	auto subCount = subItem.Count();
	for (int i = 0; i < subCount; ++i) subItem.Child(0).Destroy();
	for (int i = 0, l = (int)var->Data.size(); i < l; ++i)
		Menu::Item item(subItem, var->Data[i].name, i + 500, {}, -1, 0, 35, Color::White);
}