#include <Windows.h>
#include <ShlObj.h>
#include <string>
#include <unordered_map>
#include <filesystem>

void(__stdcall* Toast)(int duration, const std::wstring& content) noexcept = nullptr;

wchar_t base_path[MAX_PATH];

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) { return TRUE; }

extern "C" {
    bool __stdcall init(int sys_call, int unused2, int unused3, int unused4) {
        if (std::unordered_map<std::wstring, LPCVOID>* sys = (decltype(sys))sys_call) {
            Toast = (decltype(Toast))sys->at(L"Toast");
            SHGetSpecialFolderPathW(nullptr, base_path, CSIDL_APPDATA, false);
            lstrcatW(base_path, L"\\JetBrains\\");
            return true;
        }
        return false;
    }

    bool __stdcall destroy(int unused1, int unused2, int unused3, int unused4) {
        return true;
    }

    bool __stdcall run(int unused1, int unused2, int unused3, int unused4) {
        using namespace std::filesystem;
        path path(base_path), tmp_path;
        try {
            for (const auto& iter : directory_iterator(path)) {
                if (is_directory(iter.path())) {
                    tmp_path = iter.path() / L"eval";
                    if (exists(tmp_path)) remove_all(tmp_path);
                }
            }
            Toast(2000, L"清除所有jetbrains时间限制成功");
        }
        catch (filesystem_error&) {}
        return true;
    }
}