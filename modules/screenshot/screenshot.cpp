#include "screenshot.h"

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        wchar_t buf[MAX_PATH]{}, s1[_MAX_DRIVE]{}, s2[_MAX_DIR]{};
        GetModuleFileNameW(hModule, buf, MAX_PATH);
        _wsplitpath_s(buf, s1, _MAX_DRIVE, s2, _MAX_DIR, nullptr, 0, nullptr, 0);
        var.CurrentPath = s1; var.CurrentPath += s2;
        var.hDll = hModule;
    }
    return TRUE;
}

extern "C" {
    bool __stdcall init(int sys_call, int unused2, int unused3, int unused4) {
        if (WinUI::Initialize()) {
            if (std::unordered_map<String, Memory>* sys = (decltype(sys))sys_call) {
                var.GUID_JPG = (CLSID*)sys->at(L"GUID_JPG");
                var.GUID_BMP = (CLSID*)sys->at(L"GUID_BMP");
                var.GUID_PNG = (CLSID*)sys->at(L"GUID_PNG");
                res.Font.MSBlack.S16 = (Bin*)sys->at(L"Font.MSBlack.S16");
                res.Skin.Picture = (Bin*)sys->at(L"Skin.Picture");
                res.Skin.Choice = (Bin*)sys->at(L"Skin.Choice");
                res.Skin.Edit = (Bin*)sys->at(L"Skin.Edit");
                res.Skin.Button = (Bin*)sys->at(L"Skin.Button");
                res.Skin.Window = (Bin*)sys->at(L"NewSkinWindow");
                res.GroundGlass = (bool)sys->at(L"GroundGlass");
                res.Function.Toast = (decltype(res.Function.Toast))sys->at(L"Toast");
                res.Layout.screenshot = Code::From(Resource::Get(var.hDll, 1000, L"LAYOUT"));
                res.Layout.settings = Code::From(Resource::Get(var.hDll, 1001, L"LAYOUT"));
                return true;
            }
        }
        return false;
    }

    bool __stdcall destroy(int unused1, int unused2, int unused3, int unused4) {
        if (dlg2.isOpen) dlg2.Destroy();
        if (dlg1.isOpen) dlg1.Destroy();
        return true;
    }

    bool __stdcall run(int unused1, int unused2, int unused3, int unused4) {
        if (!dlg1.isOpen) {
            dlg1.isOpen = true;
            dlg1.Open();
        }
        return true;
    }

    bool __stdcall settings(int unused1, int unused2, int unused3, int unused4) {
        if (!dlg2.isOpen) {
            dlg2.isOpen = true;
            dlg2.Open();
        }
        return true;
    }
}