#pragma once
#include "winui_base.h"

namespace winui {
	// 对话框基类
	class AbstractDialog {
	protected:
		static String MakeButtonName(const std::vector<String>& buttons) noexcept;
	};

	// 信息框
	class MsgBox final : public AbstractDialog {
		MsgBox() = delete;
	public:
		// 未选择
		static constexpr auto NullChoice = -1;
		// 弹出信息框
		static int Start(ConstString title = {}, ConstString content = {},
			const std::vector<String>& buttons = {}, const Bin& icon = {},
			const Bin& image = {}, const Bin& skin = {}) noexcept;
	};

	// 输入框
	class InputBox final : public AbstractDialog {
		InputBox() = delete;
	public:
		// 弹出输入框
		static String Start(ConstString title = {}, ConstString content = {},
			const std::vector<String>& buttons = {}, const Bin& icon = {},
			const Bin& image = {}, const Bin& skin = {}, ConstString hInt = {},
			Attr inputMode = 0, int maxLen = 0) noexcept;
	};

	// 悬停提示框
	class TipBox : public AbstractDialog {
	private:
		ICO icon;
		Bin content, font;
		int width, height, angle, borderWidth, transparency;
		ARGB fontColor, backColor, borderColor;
		Attr align;
	public:
		constexpr TipBox(int tipWidth, int tipHeight) noexcept : width(tipWidth), height(tipHeight),
			angle(tipHeight >> 3), borderWidth(1), transparency(255), fontColor(Color::Black),
			backColor(Color::White), borderColor(Color::Black), align(4) {}
		TipBox(ConstString str, const ICO& ico = {}, int tipWidth = 120, int tipHeight = 60) noexcept
			: content(str), icon(ico), width(tipWidth), height(tipHeight), angle(tipHeight >> 3),
			borderWidth(1), transparency(255), fontColor(Color::Black), backColor(Color::White),
			borderColor(Color::Black), align(4) {}
		// 置内容
		TipBox& Content(ConstString str) noexcept { content = Bin(str); return *this; }
		// 置图标
		TipBox& Icon(const ICO& icon_) noexcept { icon = icon_; return *this; }
		// 置字体
		TipBox& Font(const Bin& font_) noexcept { font = font_; return *this; }
		// 置字体色
		constexpr TipBox& FontColor(ARGB color) noexcept { fontColor = color; return *this; }
		// 置背景色
		constexpr TipBox& BackColor(ARGB color) noexcept { backColor = color; return *this; }
		// 置对齐方式
		constexpr TipBox& Align(Attr align_) noexcept { align = align_; return *this; }
		// 置尺寸
		constexpr TipBox& Size(int width_, int height_) noexcept { width = width_; height = height_; return *this; }
		// 置圆角
		constexpr TipBox& Angle(int angle_) noexcept { angle = angle_; return *this; }
		// 置边框
		constexpr TipBox& Border(int width_, ARGB color) noexcept { borderWidth = width_; borderColor = color; return *this; }
		// 置透明度
		constexpr TipBox& Transparency(int transparency_) noexcept { transparency = transparency_; return *this; }
		// 悬浮提示(在控件鼠标进入或离开事件中使用)
		void Start(Arg arg1) noexcept;
	};

	// 文件框
	class FileBox final : public AbstractDialog {
		FileBox() = delete;
	public:
		struct Filter final { String name = L"所有文件(*.*)", filter = L"*.*"; };
	public:
		// 打开文件
		static String Open(ConstString title = {}, ConstString initDir = {},
			std::vector<Filter> filters = { {} }) noexcept;
		// 保存文件
		static String Save(ConstString title = {}, ConstString initDir = {},
			std::vector<Filter> filters = { {} }) noexcept;
		// 打开文件夹
		static String OpenFolder(ConstString hInt = {}, bool showEdit = true) noexcept;
	};
}