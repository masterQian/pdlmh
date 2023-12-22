#include "proxyDlg.h"

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) proxy.hDll = hModule;
    return TRUE;
}

extern "C" {
    bool __stdcall init(int sys_call, int unused2, int unused3, int unused4) {
        if (WinUI::Initialize()) {
            if (std::unordered_map<String, Memory>* sys = (decltype(sys))sys_call) {
                res.Font.MSBlack.S16 = (Bin*)sys->at(L"Font.MSBlack.S16");
                res.Skin.Edit = (Bin*)sys->at(L"Skin.Edit");
                res.Skin.Button = (Bin*)sys->at(L"Skin.Button");
                res.Skin.Window = (Bin*)sys->at(L"NewSkinWindow");
                res.GroundGlass = (bool)sys->at(L"GroundGlass");
                res.Function.Toast = (decltype(res.Function.Toast))sys->at(L"Toast");
                res.Layout.proxy = Code::From(Resource::Get(proxy.hDll, 1000, L"LAYOUT"));
                return true;
            }
        }
        return false;
    }

    bool __stdcall destroy(int unused1, int unused2, int unused3, int unused4) {
        if (proxy.isOpen) proxy.Destroy();
        return true;
    }

    bool __stdcall run(int unused1, int unused2, int unused3, int unused4) {
        if (!proxy.isOpen) {
            proxy.isOpen = true;
            proxy.Open();
        }
        return true;
    }
}