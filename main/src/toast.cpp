#include "../include/pdlmh.h"

// 提示窗口回调
Result __stdcall ToastCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (!ToastWindow::instance) return 0;
	switch (msg) {
	case Events::Window::Create: {
		VDSwitcher vds = {
			{ L"Position.Left", (Memory)Screen::Width },
			{ L"Position.Top", (Memory)(Screen::Height - Screen::TaskBarHeight - 120) },
			{ L"Value.GroundGlass", (Memory)var->Config.GroundGlass },
			{ L"Value.Content", &ToastWindow::instance->content },
			{ L"Skin.Window", var->NewSkinWindow },
			{ L"Color.White", (Memory)Color::White },
			{ L"Font.MSBlack.SL16", res->Font.MSBlack.SL16 },
		};
		// 反射布局
		Layout::InflateWindow(*ToastWindow::instance, res->Layout.Toast, vds);
		ToastWindow::instance->clock.Bind(*ToastWindow::instance, 10);
		break;
	}
	case Events::Window::Destroy: {
		ToastWindow::instance->clock.Destroy();
		break;
	}
	case Events::Window::Clock: {
		static Mutex mutex;
		if (mutex.lock()) {
			auto left = ToastWindow::instance->Left();
			if (ToastWindow::instance->mode == 0) { // 左滑模式
				if (left <= Screen::Width - 350) {
					ToastWindow::instance->clock.Start(ToastWindow::instance->duration);
					ToastWindow::instance->mode = 1;
				}
				else ToastWindow::instance->Left(left - 30);
			}
			else if (ToastWindow::instance->mode == 1) { // 停留模式
				ToastWindow::instance->clock.Start(10);
				ToastWindow::instance->mode = 2;
			}
			else { // 右滑模式
				if (left < Screen::Width) ToastWindow::instance->Left(left + 30);
				else ToastWindow::instance->Destroy();
			}
			mutex.unlock();
		}
		break;
	}
	}
	return 0;
}

ToastWindow* ToastWindow::instance = nullptr;

// 弹出提示
void __stdcall Toast(int duration, ConstString content) noexcept {
	static Mutex mutex;
	if (mutex.lock()) { // 锁防止连续点击
		if (ToastWindow::instance) { // 提示存在时销毁它然后创建新提示
			ToastWindow::instance->Destroy();
			ToastWindow::instance = nullptr;
		}
		ToastWindow toastWindow(duration, content);
		ToastWindow::instance = &toastWindow;
		mutex.unlock();
		toastWindow.Start(ToastCallBack, {}, true, false, true);
		ToastWindow::instance = nullptr;
	}
}

void ToastWindow::Release() noexcept {
	if (ToastWindow::instance) ToastWindow::instance->Destroy();
}