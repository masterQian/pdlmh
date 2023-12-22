#pragma once
#include "winui_base.h"

namespace winui {
	// 环境
	class Environment final {
		Environment() = delete;
	public:
		static ULONGLONG StartTime;
		static String CurrentFileName;
		static String CurrentFullName;
		static String CurrentPath;
	};

	class WinUI final {
		WinUI() = delete;
	private:
		static bool needFree;
		static HMODULE hDll;
		static unsigned long gdiplusToken;
		static BinManager binManager;
	private:
		static void init_environment() noexcept;
		static void init_internal(HMODULE hDll) noexcept;
		static void init_binManager() noexcept;
	public:
		struct Version { int first, second, other; };
	public:
		// 取UI库句柄
		static constexpr HMODULE Lib() noexcept { return hDll; }
		// 是否初始化
		static constexpr bool IsInitialize() noexcept { return hDll != nullptr; }
		// 初始化
		static bool Initialize(ConstString path = {}) noexcept;
		// 结束
		static int End() noexcept;
		// 取全局字节集
		static Bin GetBin(ConstString name) noexcept;
		// 取库版本
		static Version GetVersion() noexcept;
	};
}