#include "../include/pdlmh.h"

// 系统工具列表回调
Result __stdcall SystemListCallBack(ID id, Event msg, Arg index, Arg, Arg, Arg) {
	switch (msg) {
	case Events::IconList::ItemLDCLick: {
		Process::Execute(res->SystemTools[index + 1].path, res->SystemTools[index + 1].arg,
			index == 4); // cmd
		break;
	}
	case Events::IconList::ItemRCLick: {
		switch (index) {
		case 0: Process::Execute(L"SystemPropertiesAdvanced", {}, true); break;
		case 2: {
			mainWindow->Absorb.Can = false;
			RecycleBin::Clear();
			auto i = RecycleBin::IsEmpty() ? 3 : 0;
			mainWindow->SLSystem.ItemIcon(2, res->SystemTools[i].ico);
			mainWindow->Absorb.Can = true;
			break;
		}
		}
		break;
	}
	}
	return 0;
}

void MainWindow::LazyLoadPageSystem() noexcept {
	mainWindow->LockUpdate();
	var->vds[L"CallBack.SystemList"] = &SystemListCallBack;
	auto id = Group(Layout::InflateControl(*mainWindow, res->Layout.pageSystem, var->vds));
	mainWindow->Tabs[1] = id;
	mainWindow->SLSystem = (IconList)id(L"List");
	for (UINT i = 1, l = res->SystemTools.size(); i < l; ++i)
		mainWindow->SLSystem.InsertItem(-1, res->SystemTools[i].name, res->SystemTools[i].ico, Color::White);
	constexpr int hasRightMenu[] = { 0, 2 };
	for (auto& i : hasRightMenu) mainWindow->SLSystem.ItemFontColor(i, Color::Red);
	mainWindow->SLSystem.CurrentItem(-1);
	mainWindow->UnlockUpdate();
}

void MainWindow::UpdatePageSystem() noexcept {
	static Mutex mutex;
	if (mutex.lock()) {
		auto index = RecycleBin::IsEmpty() ? 3 : 0;
		mainWindow->SLSystem.ItemIcon(2, res->SystemTools[index].ico);
		mutex.unlock();
	}
}