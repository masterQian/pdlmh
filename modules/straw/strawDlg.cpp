#include "strawDlg.h"

void hexWork(Byte v, String& s) {
	static wchar_t buf[3] = { 0,0,0 };
	buf[0] = buf[1] = buf[2] = 0; _itow_s(v, buf, 3, 16);
	if (!buf[1]) { buf[1] = buf[0]; buf[0] = L'0'; }
	if (IsCharLowerW(buf[0])) buf[0] ^= 32;
	if (IsCharLowerW(buf[1])) buf[1] ^= 32;
	s += buf;
}

Result __stdcall SLCallBack(ID id, Event msg, Arg row, Arg, Arg, Arg source) {
	if (msg == Events::SuperList::ItemLDCLick && source == Attrs::ListEventSource::Item) {
		ClipBoard::SetString(straw.SL.ItemTitle(row, 1));
		res.Function.Toast(2000, L"复制颜色值到剪贴板成功");
	}
	return 0;
}

Result __stdcall StrawCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: {
		Layout::InflateWindow(straw, res.Layout.straw, straw.vds);
		straw.SL = (SuperList)straw(L"SL");
		straw.CL = (Label)straw(L"CL");
		straw.SL.InsertColumn(-1, {}, Color::White, 100, Attrs::ItemAlign::Center, 0, 0, *res.Font.MSBlack.S16);
		straw.SL.InsertColumn(-1, {}, Color::White, 180, Attrs::ItemAlign::Center, 0, 0, *res.Font.MSBlack.S16);
		straw.SL.InsertItem(-1, 48, 0, 5);
		straw.SL.ItemTitle(0, 0, L"R"); straw.SL.ItemTitle(1, 0, L"G"); straw.SL.ItemTitle(2, 0, L"B");
		straw.SL.ItemTitle(3, 0, L"十进制"); straw.SL.ItemTitle(4, 0, L"十六进制");
		straw.SL.ItemFontColor(-1, -1, Color::White);
		straw.isListen = false;
		straw.Clk.Bind(straw, 200);
		straw.HK.Bind(straw, VK_F2);
		break;
	}
	case Events::Window::Destroy: {
		straw.Clk.Destroy();
		straw.HK.Destroy();
		straw.isOpen = false;
		straw.Reset();
		break;
	}
	case Events::Window::Clock: {
		static volatile bool mutex_response = true;
		if (straw.Clk.Check(arg1)) {
			if (mutex_response) {
				mutex_response = false;
				POINT pos; GetCursorPos(&pos);
				HDC hDC = GetDC(nullptr);
				COLORREF color = GetPixel(hDC, pos.x, pos.y);
				ReleaseDC(nullptr, hDC);
				if (color != straw.CurrentColor) {
					Byte r = GetRValue(color), g = GetGValue(color), b = GetBValue(color);
					String color16 = L"#";
					hexWork(r, color16); hexWork(g, color16); hexWork(b, color16);
					straw.SL.LockUpdate();
					straw.SL.ItemTitle(0, 1, ToString(r));
					straw.SL.ItemTitle(1, 1, ToString(g));
					straw.SL.ItemTitle(2, 1, ToString(b));
					straw.SL.ItemTitle(3, 1, ToString(color));
					straw.SL.ItemTitle(4, 1, color16);
					straw.CL.BackColor(Color::RGB_ARGB(color));
					straw.SL.UnlockUpdate();
					straw.CurrentColor = color;
				}
				mutex_response = true;
			}
		}
		break;
	}
	case Events::Window::HotKey: {
		if (straw.HK.Check(arg1)) {
			if (straw.isListen) straw.Clk.Stop();
			else straw.Clk.Start(200);
			straw.isListen = !straw.isListen;
		}
		break;
	}
	}
	return 0;
}

void Straw::Open() noexcept {
	straw.vds = {
		{ L"Value.GroundGlass", (Memory)res.GroundGlass },
		{ L"Position.Left", (Memory)((Screen::Width >> 1) - 200) },
		{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 140) },
		{ L"Font.MSBlack.S16", *res.Font.MSBlack.S16 },
		{ L"Color.White", (Memory)Color::White },
		{ L"Skin.Window", *res.Skin.Window },
		{ L"Skin.SuperList2", *res.Skin.SuperList2 },
		{ L"CallBack.SL", &SLCallBack },
	};
	straw.Start(&StrawCallBack, {}, true, false, true);
}