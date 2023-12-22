#include "qrcodeDlg.h"

std::string MakeQRCode(const std::string& data);

Result __stdcall EditCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (msg == Events::Edit::ContentChange) {
		static ULONGLONG last_clock = 0;
		auto now_clock = GetTickCount64();
		if (now_clock - last_clock > 200U) {
			last_clock = now_clock;
			auto str = Edit(id).Content();
			if (str.empty()) qrcode.picture.Image({});
			else {
				ByteArray bs = Code::To(str, Code::UTF8);
				auto data = MakeQRCode(*(std::string*)&bs);
				qrcode.picture.Image(Bin(data.data(), data.size()));
			}
		}
	}
	return 0;
}

Result __stdcall PicCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	if (msg == Events::Control::RClick) {
		if (auto bin = qrcode.picture.Image()) {
			auto bs = bin.ToByteSet();
			auto fn = FileBox::Save(L"保存二维码", {}, { {L"JPG图片",L"*.jpg"} });
			if (!fn.empty()) {
				if (HGLOBAL hImageData = GlobalAlloc(GMEM_MOVEABLE, bs.length)) {
					if (LPVOID pImgData = GlobalLock(hImageData)) {
						memcpy(pImgData, bs.content, bs.length);
						GlobalUnlock(hImageData);
						IStream* istream = nullptr;
						if (HRESULT hResult = CreateStreamOnHGlobal(hImageData, true, &istream); hResult == 0) {
							if (auto pImg = Gdiplus::Image::FromStream(istream)) {
								pImg->Save(fn.data(), res.GUID_JPG, nullptr);
								delete pImg;
							}
							istream->Release();
						}
					}
					GlobalFree(hImageData);
				}
			}
		}
	}
	return 0;
}

Result __stdcall QrcodeCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: {
		Layout::InflateWindow(qrcode, res.Layout.qrcode, qrcode.vds);
		qrcode.picture = (Picture)qrcode(L"picture");
		break;
	}
	case Events::Window::Destroy: {
		qrcode.isOpen = false;
		qrcode.Reset();
		break;
	}
	}
	return 0;
}

void Qrcode::Open() noexcept {
	qrcode.vds = {
		{ L"Value.GroundGlass", (Memory)res.GroundGlass },
		{ L"Position.Left", (Memory)((Screen::Width >> 1) - 150) },
		{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 180) },
		{ L"Font.MSBlack.S16", *res.Font.MSBlack.S16 },
		{ L"Color.White", (Memory)Color::White },
		{ L"Skin.Window", *res.Skin.Window },
		{ L"Skin.Edit", *res.Skin.Edit },
		{ L"Skin.Picture", *res.Skin.Picture },
		{ L"CallBack.Edit", &EditCallBack },
		{ L"CallBack.Pic", &PicCallBack },
	};
	qrcode.Start(&QrcodeCallBack, {}, true, false, true);
}