#include "proxyDlg.h"

Result __stdcall SBCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (msg == Events::Switch::SelectChange) {
		bool result = arg1 == 0;
		proxy.IP.Disabled(result);
		proxy.PORT.Disabled(result);
		proxy.BLOCK.Disabled(result);
	}
	return 0;
}

Result __stdcall ButtonCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (msg == Events::Control::LClick) {
		proxy.reg.SetNumberValue(L"ProxyEnable", (DWORD)proxy.SB.Select());
		proxy.reg.SetStringValue(L"ProxyServer", proxy.IP.Content() + L":" + proxy.PORT.Content());
		proxy.reg.SetStringValue(L"ProxyOverride", proxy.BLOCK.Content());
		proxy.Destroy();
	}
	return 0;
}

Result __stdcall ProxyCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: {
		Layout::InflateWindow(proxy, res.Layout.proxy, proxy.vds);
		proxy.SB = (Switch)proxy(L"SB");
		proxy.IP = (Edit)proxy(L"IP");
		proxy.PORT = (Edit)proxy(L"Port");
		proxy.BLOCK = (Edit)proxy(L"Block");
		break;
	}
	case Events::Window::Destroy: {
		proxy.reg.Close();
		proxy.isOpen = false;
		proxy.Reset();
		break;
	}
	}
	return 0;
}

void Proxy::Open() noexcept {
	reg.Open(Reg::CurrentUser, L"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
	if (reg.isOpen()) {
		auto ProxyEnable = reg.GetNumberValue(L"ProxyEnable");
		auto server = reg.GetStringValue(L"ProxyServer");
		auto pos = server.find(L':');
		auto ip = server.substr(0, pos);
		auto port = server.substr(pos + 1);
		auto ProxyOverride = reg.GetStringValue(L"ProxyOverride");
		proxy.vds = {
			{ L"Position.Left", (Memory)((Screen::Width >> 1) - 220) },
			{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 170) },
			{ L"Font.MSBlack.S16", *res.Font.MSBlack.S16 },
			{ L"Color.White", (Memory)Color::White },
			{ L"Skin.Window", *res.Skin.Window },
			{ L"Skin.Edit", *res.Skin.Edit },
			{ L"Skin.Button", *res.Skin.Button },
			{ L"CallBack.SB", &SBCallBack },
			{ L"CallBack.Button", &ButtonCallBack },
			{ L"Value.ProxyEnable", (Memory)ProxyEnable },
			{ L"Value.NotProxyEnable", (Memory)(ProxyEnable == 0) },
			{ L"Value.IP", &ip },
			{ L"Value.Port", &port },
			{ L"Value.Override", &ProxyOverride },
			{ L"Value.GroundGlass", (Memory)res.GroundGlass },
		};
		proxy.Start(&ProxyCallBack, {}, true, false, true);
	}
	else {
		proxy.isOpen = false;
		res.Function.Toast(2000, L"查询注册表失败");
	}
}