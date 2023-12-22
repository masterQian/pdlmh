#include "unlockDlg.h"

Result __stdcall SwitchCallBack(ID id, Event msg, Arg arg1, Arg, Arg, Arg) {
	if (msg == Events::Switch::SelectChange) unlock.isKill = arg1;
	return 0;
}

Result __stdcall UnlockCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: {
		Layout::InflateWindow(unlock, res.Layout.unlock, unlock.vds);
		unlock.edit = (Edit)unlock(L"edit");
		unlock.isKill = false;
		unlock.drag.Bind(unlock);
		break;
	}
	case Events::Window::Destroy: {
		unlock.drag.Destroy();
		unlock.isKill = false;
		unlock.isOpen = false;
		unlock.Reset();
		break;
	}
	case Events::Window::Drag: {
		if (arg1 == 1) {
			auto files = ((Drag::DragPath)arg2)[0];
			String cmdLine = res.CurrentPath + L"unlock.exe" + (unlock.isKill ?
				L" -k" : L" -u") + L" -sm -x \"" + files + L"\"";
			DWORD exitCode = 0;
			PROCESS_INFORMATION pInfo{};
			STARTUPINFO sInfo{}; sInfo.cb = sizeof(STARTUPINFO);
			if (CreateProcessW(nullptr, cmdLine.data(), nullptr, nullptr,
				false, 0, nullptr, nullptr, &sInfo, &pInfo)) {
				WaitForSingleObject(pInfo.hProcess, INFINITE);
				if (GetExitCodeProcess(pInfo.hProcess, &exitCode) && exitCode == 0)
					res.Function.Toast(2000, L"解锁成功");
				else res.Function.Toast(2000, L"解锁失败");
				CloseHandle(pInfo.hProcess);
				CloseHandle(pInfo.hThread);
				auto log = res.CurrentPath + L"LockHunter.log.txt";
				unlock.edit.Content(File::ReadString(log));
				DeleteFileW(log.data());
			}
			else res.Function.Toast(2000, L"插件启动失败");
		}
		else res.Function.Toast(2000, L"最多支持同时解锁一个文件或目录");
		break;
	}
	}
	return 0;
}

void Unlock::Open() noexcept {
	unlock.vds = {
		{ L"Value.GroundGlass", (Memory)res.GroundGlass },
		{ L"Position.Left", (Memory)((Screen::Width >> 1) - 150) },
		{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 125) },
		{ L"Font.MSBlack.S16", *res.Font.MSBlack.S16 },
		{ L"Color.White", (Memory)Color::White },
		{ L"Skin.Window", *res.Skin.Window },
		{ L"Skin.Edit", *res.Skin.Edit },
		{ L"CallBack.Switch", &SwitchCallBack },
	};
	unlock.Start(&UnlockCallBack, {}, true, false, true);
}