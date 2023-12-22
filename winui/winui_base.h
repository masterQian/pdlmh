#pragma once
#include "winui_api.h"

#define CON_EX_BEGIN(name) class name final { \
name() = delete; \
public:
#define CON_EX_END(name) };

#define ATTR(name, value, comment) constexpr static Attr name = value

namespace winui {
	// 字节数组
	class ByteArray final : protected std::basic_string<Byte> {
	public:
		constexpr ByteArray() noexcept = default;
		constexpr ByteArray(UINT len) noexcept : std::basic_string<Byte>(len, '\0') {}
		constexpr ByteArray(ConstMemory data, UINT len) noexcept : std::basic_string<Byte>((ConstBytes)data, len) {}
		constexpr UINT size() const noexcept { return std::basic_string<Byte>::size(); }
		constexpr Bytes data() noexcept { return std::basic_string<Byte>::data(); }
		constexpr ConstBytes data() const noexcept { return std::basic_string<Byte>::data(); }
		constexpr void resize(UINT size) noexcept { std::basic_string<Byte>::resize(size); }
		constexpr void assign(ConstMemory data, UINT len) noexcept { std::basic_string<Byte>::assign((ConstBytes)data, len); }
		constexpr Byte& operator [] (UINT index) noexcept { return std::basic_string<Byte>::operator[](index); }
		constexpr Byte operator [] (UINT index) const noexcept { return std::basic_string<Byte>::operator[](index); }
	};

	// 字节流
	class ByteSet final {
	public:
		int length = 0;
		ConstMemory content = nullptr;
		constexpr ByteSet() noexcept = default;
		constexpr ByteSet(ConstMemory data, int len) noexcept : length{ len }, content{ data }{}
		static constexpr ByteSet FromEByteSet(ConstMemory data) noexcept { return ByteSet(data, *((int*)data - 1)); }
	};

	// 内存字节流
	using MemoryBytes = struct { int ref; int length; }*;

	// 字节集
	class Bin final {
	protected:
		PBin pBin = nullptr;
		bool isMem = false;
	public:
		~Bin() noexcept;
		constexpr Bin() noexcept = default;
		Bin(ConstMemory data, int len) noexcept;
		Bin(ConstString s) noexcept;
		Bin(const std::initializer_list<BYTE>& data) noexcept;
		Bin(const ByteArray& data) noexcept;
		Bin(const ByteSet& data) noexcept;
		constexpr Bin(const Bin& bin) noexcept : pBin{ bin.pBin }, isMem{ false } {}
		constexpr Bin(Bin&& bin) noexcept : pBin{ bin.pBin }, isMem{ bin.isMem }{ bin.pBin = nullptr; bin.isMem = false; }
		Bin& operator = (const Bin& bin) noexcept;
		constexpr Bin& operator = (Bin&& bin) noexcept {
			std::swap(pBin, bin.pBin);
			std::swap(isMem, bin.isMem);
			return *this;
		}
		static Bin Src(PBin bin, bool mem) noexcept;
		static Bin FromEByteSet(ConstMemory data) noexcept;
		constexpr int Size() const noexcept { return pBin ? *((int*)pBin + 1) : 0; }
		constexpr Memory Data() const noexcept { return pBin ? (Byte*)pBin + 8 : pBin; }
		constexpr ByteSet ToByteSet() const noexcept {
			if (pBin) return { (Byte*)pBin + 8 , *((int*)pBin + 1) };
			return { nullptr, 0 };
		}
		constexpr operator PBin () const noexcept { return pBin; }
		constexpr operator String() const noexcept { return pBin ? String((Str)pBin + 4) : String(); }
	};

	// 静态字节集管理器
	class BinManager final {
		std::unordered_map<String, Bin> manager;
	public:
		bool Set(ConstString name, Bin&& bin) noexcept;
		Bin operator [] (ConstString name) const noexcept;
		void Clear() noexcept;
	};

	// 位图
	class ICO {
	protected:
		PICO pICO = nullptr;
		bool isMem = false;
	public:
		~ICO() noexcept;
		constexpr ICO() noexcept = default;
		ICO(ConstMemory data, int len) noexcept;
		constexpr ICO(const ICO& ico) noexcept : pICO{ ico.pICO }, isMem{ false } {}
		constexpr ICO(ICO&& ico) noexcept : pICO{ ico.pICO }, isMem{ ico.isMem }{ ico.pICO = 0; ico.isMem = false; }
		ICO& operator = (const ICO& ico) noexcept;
		ICO& operator = (ICO&& ico) noexcept;
		static ICO Src(PICO ico, bool mem) noexcept;
		static ICO FromEByteSet(ConstMemory data) noexcept;
		int Width() const noexcept;
		int Height() const noexcept;
		Bin ToBin() const noexcept;
		constexpr operator PICO () const noexcept { return pICO; }
	};

	// 资源
	class Resource final {
		Resource() = delete;
	public:
		static ByteSet Get(HMODULE hModule, int id, ConstString type = L"R") noexcept;
		static ByteSet Get(int id, ConstString type = L"R") noexcept;
	};

	// 字体
	class Font final {
		String mFont;
		int mSize, mRenderArg = 0;
		Attr mStyle = 0, mRender = 0;
		ARGB mRenderColor = 0;
	public:
		// 字体风格(支持位或)
		CON_EX_BEGIN(Style)
		ATTR(Null, 0, "无"); ATTR(Bold, 1, "加粗");
		ATTR(Italic, 2, "倾斜"); ATTR(Underline, 4, "下划线");
		ATTR(Strike, 8, "删除线");
		CON_EX_END(Style)
		// 字体渲染模式
		CON_EX_BEGIN(Render)
		ATTR(Default, 0, "默认");
		ATTR(Sign_Hinting, 1, "符号位图和Hinting技术"); ATTR(Sign, 2, "符号位图");
		ATTR(AntiSawTooth_Hinting, 3, "抗锯齿和Hinting技术"); ATTR(AntiSawTooth, 4, "抗锯齿");
		ATTR(ClearText_Hinting, 5, "清晰文本和Hinting技术"); ATTR(LightText, 6, "发光字");
		ATTR(Stroke, 7, "描边"); ATTR(Shadow, 8, "阴影");
		ATTR(Change, 9, "渐变"); ATTR(Hollow, 10, "镂空");
		CON_EX_END(Render)
	public:
		constexpr Font(ConstString font, int size = 12, Attr fontStyle = 0) noexcept
			: mFont{ font }, mSize{ size }, mStyle{ fontStyle }{}
		constexpr Font& SetName(ConstString font) noexcept { mFont = font; return *this; }
		constexpr Font& SetSize(int size) noexcept { mSize = size; return *this; }
		constexpr Font& SetStyle(Attr style) noexcept { mStyle = style; return *this; }
		constexpr Font& SetRender(Attr render, int renderArg = 0, ARGB renderColor = 0) noexcept {
			mRender = render; mRenderArg = renderArg; mRenderColor = renderColor;
			return *this;
		}
		Bin Create() noexcept;
	};

	// 颜色
	class Color final {
		Color() = delete;
	public:
#define COLOR(name, value, comment) constexpr static ARGB name = value
		COLOR(Null, 0, "透明"); COLOR(White, -1, "白色");
		COLOR(Black, -16777216, "黑色"); COLOR(Red, -65536, "红色");
		COLOR(Orange, -23296, "橙色"); COLOR(Yellow, -256, "黄色");
		COLOR(Green, -16744448, "绿色"); COLOR(Cyan, -16711681, "青色");
		COLOR(Blue, -16776961, "蓝色"); COLOR(Purple, -8388480, "紫色");
		COLOR(Gray, -8355712, "灰色"); COLOR(Brown, -5952982, "棕色");
		COLOR(Pink, -16181, "紫色");
#undef COLOR
	public:
		static constexpr ARGB RGB_ARGB(int r, int g, int b, int alpha = 255) noexcept { return b | (g << 8) | (r << 16) | (alpha << 24); }
		static constexpr ARGB RGB_ARGB(COLORREF rgb, int alpha = 255) noexcept { return RGB_ARGB(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb), alpha); }
		static constexpr COLORREF ARGB_RGB(ARGB argb) noexcept { return RGB(GetBValue(argb), GetGValue(argb), GetRValue(argb)); }
		static ByteArray SolidBitmap(COLORREF color) noexcept;
	};
}

#undef ATTR
#undef CON_EX_BEGIN
#undef CON_EX_END