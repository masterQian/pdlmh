#include "screenshot.h"
#include <ShlObj.h>

void SaveGDIImage(ByteSet bs, ConstString filename, const CLSID* clsid) noexcept {
	if (HGLOBAL hImageData = GlobalAlloc(GMEM_MOVEABLE, bs.length)) {
		if (LPVOID pImgData = GlobalLock(hImageData)) {
			memcpy(pImgData, bs.content, bs.length);
			GlobalUnlock(hImageData);
			IStream* istream = nullptr;
			if (HRESULT hResult = CreateStreamOnHGlobal(hImageData, true, &istream); hResult == 0) {
				if (auto pImg = Gdiplus::Image::FromStream(istream)) {
					pImg->Save(filename.data(), clsid, nullptr);
					delete pImg;
				}
				istream->Release();
			}
		}
		GlobalFree(hImageData);
	}
}

Result __stdcall MonitorCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (ClipBoard::GetString().empty()) {
		auto bs = ClipBoard::GetBitmap();
		if (bs.size() > 0) dlg1.picture.Image(Bin(bs));
	}
	return 0;
}

Result __stdcall ScreenShotCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: {
		Layout::InflateWindow(dlg1, res.Layout.screenshot, dlg1.vds);
		dlg1.picture = (Picture)dlg1(L"picture");
		Settings::ReadSettings();
		MonitorCallBack(0, 0, 0, 0, 0, 0);
		dlg1.monitor.Start(dlg1, &MonitorCallBack);
		break;
	}
	case Events::Window::Destroy: {
		dlg1.monitor.Stop();
		dlg1.isOpen = false;
		dlg1.Reset();
	}
	}
	return 0;
}

Result __stdcall PictureCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Control::LDClick: {
		Bin bin = dlg1.picture.Image();
		if (bin) {
			wchar_t desktop[MAX_PATH]{};
			SHGetSpecialFolderPathW(nullptr, desktop, CSIDL_DESKTOPDIRECTORY, false);
			String path = String(desktop) + L"\\" + var.DefaultName + L"." + var.DefaultType;
			CLSID* pGUID;
			if (var.DefaultType == L"bmp") pGUID = var.GUID_BMP;
			else if (var.DefaultType == L"png") pGUID = var.GUID_PNG;
			else pGUID = var.GUID_JPG;
			SaveGDIImage(bin.ToByteSet(), path, pGUID);
			res.Function.Toast(2000, L"保存截图到桌面成功");
		}
		break;
	}
	case Events::Control::RClick: {
		Bin bin = dlg1.picture.Image();
		if (bin) {
			auto fn = FileBox::Save(L"保存截图", {}, {
			{L"JPG图片", L"*.jpg"}, {L"BMP图片", L"*.bmp"}, {L"PNG图片", L"*.png"}
				});
			if (!fn.empty()) {
				wchar_t ext[_MAX_EXT]{};
				_wsplitpath_s(fn.data(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
				CLSID* pGUID;
				if (lstrcmpW(ext, L".bmp") == 0) pGUID = var.GUID_BMP;
				else if (lstrcmpW(ext, L".png") == 0) pGUID = var.GUID_PNG;
				else pGUID = var.GUID_JPG;
				SaveGDIImage(bin.ToByteSet(), fn, pGUID);
			}
		}
		break;
	}
	}
	return 0;
}

void ScreenShot::Open() noexcept {
	dlg1.vds = {
		{ L"Value.GroundGlass", (Memory)res.GroundGlass },
		{ L"Position.Left", (Memory)((Screen::Width >> 1) - 200) },
		{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 215) },
		{ L"Font.MSBlack.S16", *res.Font.MSBlack.S16 },
		{ L"Color.White", (Memory)Color::White },
		{ L"Skin.Window", *res.Skin.Window },
		{ L"Skin.Picture", *res.Skin.Picture },
		{ L"CallBack.Picture", &PictureCallBack },
	};
	dlg1.Start(&ScreenShotCallBack, {}, true, false, true);
}