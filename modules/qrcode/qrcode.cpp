#include "qrcodeDlg.h"

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) qrcode.hDll = hModule;
    return TRUE;
}

extern "C" {
    bool __stdcall init(int sys_call, int unused2, int unused3, int unused4) {
        if (WinUI::Initialize()) {
            if (std::unordered_map<String, Memory>* sys = (decltype(sys))sys_call) {
                res.Font.MSBlack.S16 = (Bin*)sys->at(L"Font.MSBlack.S16");
                res.Skin.Window = (Bin*)sys->at(L"NewSkinWindow");
                res.Skin.Edit = (Bin*)sys->at(L"Skin.Edit");
                res.Skin.Picture = (Bin*)sys->at(L"Skin.Picture");
                res.GUID_JPG = (CLSID*)sys->at(L"GUID_JPG");
                res.GroundGlass = (bool)sys->at(L"GroundGlass");
                res.Layout.qrcode = Code::From(Resource::Get(qrcode.hDll, 1000, L"LAYOUT"));
                return true;
            }
        }
        return false;
    }

    bool __stdcall destroy(int unused1, int unused2, int unused3, int unused4) {
        if (qrcode.isOpen) qrcode.Destroy();
        return true;
    }

    bool __stdcall run(int unused1, int unused2, int unused3, int unused4) {
        if (!qrcode.isOpen) {
            qrcode.isOpen = true;
            qrcode.Open();
        }
        return true;
    }
}