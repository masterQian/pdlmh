#pragma once

#include "winui_def.h"

#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <functional>

namespace winui {
	// 字符串
	using String = std::wstring;
	using ConstString = const std::wstring&;

	using __WinCall = LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM);
}

namespace winui {
	template<typename T>
	concept __ConstructString = requires(T t) {
		{ std::wstring(t) } -> std::same_as<String>;
	};

	template<typename T>
	concept __CastString = requires(T t) {
		{ std::to_wstring(t) } -> std::same_as<String>;
	};

	template<typename T>
	concept __UserString = requires(T t) {
		{ TransformString(t) } -> std::same_as<String>;
	};

	template<typename T>
	concept __GetString = __ConstructString<T> || __CastString<T> || __UserString<T>;

	template<typename T>
	concept __Int = std::is_same_v<std::remove_reference_t<T>, int>;

	template<typename T>
	concept __Double = std::is_same_v<std::remove_reference_t<T>, double>;

	// 转字符串
	template<typename T, typename... V>
	requires __GetString<T>
	inline constexpr String ToString(T&& t, V&&... v) noexcept {
		if constexpr (sizeof...(V) == 0) {
			if constexpr (std::is_same_v<std::remove_cvref_t<T>, String>) return t;
			else if constexpr (__UserString<T>) return TransformString(t);
			else if constexpr (__CastString<T>) return std::to_wstring(t);
			else if constexpr (__ConstructString<T>) return String(t);
		}
		else return ToString(t) + ToString(std::forward<V>(v)...);
	}

	// 字符串转
	template<typename T>
	requires __Int<T> || __Double<T>
	inline T StringTo(ConstString s) noexcept {
		if constexpr (__Int<T>) return _wtoi(s.data());
		else if constexpr (__Double<T>) return _wtof(s.data());
	}

	// 合并整数
	inline constexpr int MergeInt(int high, int low) noexcept { return (high << 0x10) | (low & 0xFFFF); }

	// 分离整数低位
	inline constexpr int SeparateLow(int value) noexcept { return value & 0xFFFF; }

	// 分离整数高位
	inline constexpr int SeparateHigh(int value) noexcept { return value >> 0x10; }
}

namespace winui {
	inline constexpr String TransformString(const Rectangle& rect) noexcept {
		 return ToString(L"[", rect.left, L",", rect.top, L",", rect.width, L",", rect.height, L"]");
	}
}