#include "strawDlg.h"

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) straw.hDll = hModule;
    return TRUE;
}

extern "C" {
    bool __stdcall init(int sys_call, int unused2, int unused3, int unused4) {
        if (WinUI::Initialize()) {
            if (std::unordered_map<String, Memory>* sys = (decltype(sys))sys_call) {
                res.Font.MSBlack.S16 = (Bin*)sys->at(L"Font.MSBlack.S16");
                res.Skin.Window = (Bin*)sys->at(L"NewSkinWindow");
                res.Skin.SuperList2 = (Bin*)sys->at(L"Skin.SuperList2");
                res.GroundGlass = (bool)sys->at(L"GroundGlass");
                res.Function.Toast = (decltype(res.Function.Toast))sys->at(L"Toast");
                res.Layout.straw = Code::From(Resource::Get(straw.hDll, 1000, L"LAYOUT"));
                return true;
            }
        }
        return false;
    }

    bool __stdcall destroy(int unused1, int unused2, int unused3, int unused4) {
        if (straw.isOpen) straw.Destroy();
        return true;
    }

    bool __stdcall run(int unused1, int unused2, int unused3, int unused4) {
        if (!straw.isOpen) {
            straw.isOpen = true;
            straw.Open();
        }
        return true;
    }
}