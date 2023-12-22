#include "unlockDlg.h"

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
        unlock.hDll = hModule;
        wchar_t buf[MAX_PATH]{}, s1[_MAX_DRIVE]{}, s2[_MAX_DIR]{};
        GetModuleFileNameW(hModule, buf, MAX_PATH);
        _wsplitpath_s(buf, s1, _MAX_DRIVE, s2, _MAX_DIR, nullptr, 0, nullptr, 0);
        res.CurrentPath = s1; res.CurrentPath += s2;
    }
    return TRUE;
}

extern "C" {
    bool __stdcall init(int sys_call, int unused2, int unused3, int unused4) {
        if (WinUI::Initialize()) {
            if (std::unordered_map<String, Memory>* sys = (decltype(sys))sys_call) {
                res.Font.MSBlack.S16 = (Bin*)sys->at(L"Font.MSBlack.S16");
                res.Skin.Window = (Bin*)sys->at(L"NewSkinWindow");
                res.Skin.Edit = (Bin*)sys->at(L"Skin.Edit");
                res.GroundGlass = (bool)sys->at(L"GroundGlass");
                res.Function.Toast = (decltype(res.Function.Toast))sys->at(L"Toast");
                res.Layout.unlock = Code::From(Resource::Get(unlock.hDll, 1000, L"LAYOUT"));
                return true;
            }
        }
        return false;
    }

    bool __stdcall destroy(int unused1, int unused2, int unused3, int unused4) {
        if (unlock.isOpen) unlock.Destroy();
        return true;
    }

    bool __stdcall run(int unused1, int unused2, int unused3, int unused4) {
        if (!unlock.isOpen) {
            unlock.isOpen = true;
            unlock.Open();
        }
        return true;
    }
}