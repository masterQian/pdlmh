#pragma once

#include "winui_lib.h"
#include "winui_util.h"
#include <iostream>

namespace winui {
	enum class LogTag { TagInfo, TagError, TagWarning };

	constexpr LogTag Info = LogTag::TagInfo;
	constexpr LogTag Error = LogTag::TagError;
	constexpr LogTag Warning = LogTag::TagWarning;

	class Log {
		static constexpr HANDLE InvalidFile = INVALID_HANDLE_VALUE;
		HANDLE hFile = InvalidFile;
		Code::CodePage cp = Code::UTF8;
	private:
		static constexpr ConstStr TagHeader[3] = { L"[# Info] ", L"[! Error] ", L"[- Warning] " };
	private:
		template<LogTag tag>
		static void WriteConsoleHeader() noexcept { std::wcout << TagHeader[static_cast<UINT>(tag)]; }

		template<LogTag tag>
		static void WriteFileHeader(HANDLE hFile, Code::CodePage cp) noexcept {
			ByteArray header = Code::To(TagHeader[static_cast<UINT>(tag)], cp);
			WriteFile(hFile, header.data(), header.size(), nullptr, nullptr);
		}

		static void WriteConsoleEndline() noexcept { std::wcout << std::endl; }

		static void WriteFileEndline(HANDLE hFile) noexcept {
			WriteFile(hFile, "\r\n", 2, nullptr, nullptr);
		}

		template<typename... Args>
		static void WriteConsoleImpl(Args&&... args) noexcept {
			std::wcout << ToString(std::forward<Args>(args)...).data();
		}

		template<typename... Args>
		static void WriteFileImpl(HANDLE hFile, Code::CodePage cp, Args&&... args) noexcept {
			ByteArray data = Code::To(ToString(std::forward<Args>(args)...), cp);
			WriteFile(hFile, data.data(), data.size(), nullptr, nullptr);
		}
	public:
		Log(ConstString filename = {}, Code::CodePage codePage = Code::UTF8) noexcept {
			cp = codePage;
			if (!filename.empty()) {
				hFile = CreateFileW(filename.data(), GENERIC_WRITE, 0, nullptr,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
			}
		}
		~Log() noexcept {
			if (hFile != InvalidFile) CloseHandle(hFile);
		}
		Log(const Log&) noexcept = delete;
		Log(Log&&) noexcept = delete;
		Log& operator = (const Log&) noexcept = delete;
		Log& operator = (Log&&) noexcept = delete;
		constexpr bool IsConsole() const noexcept { return hFile == InvalidFile; }
		constexpr bool IsFile() const noexcept { return hFile != InvalidFile; }
		template<LogTag tag = LogTag::TagInfo, typename... Args>
		void Write(Args&&... args) const noexcept {
			if (hFile == InvalidFile) {
				WriteConsoleHeader<tag>();
				WriteConsoleImpl(std::forward<Args>(args)...);
				WriteConsoleEndline();
			}
			else {
				WriteFileHeader<tag>(hFile, cp);
				WriteFileImpl(hFile, cp, std::forward<Args>(args)...);
				WriteFileEndline(hFile);
			}
		}
	};
}