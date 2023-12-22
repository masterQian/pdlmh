#pragma once
#include "winui_main.h"

#define DELETE_ALL_CONSTRUCT(name) \
name() = delete; \
name(const name&) = delete; \
name(name&&) = delete; \
name& operator = (const name&) = delete; \
name& operator = (name&&) = delete

#define CON_EX_BEGIN(name) class name final { \
name() = delete; \
public:
#define CON_EX_END(name) };

#define SKIN_CONSTRUCT(name) \
Skin##name(const Bin& bin) noexcept : Skin{ bin } { } \
static Bin Default() noexcept { \
return WinUI::GetBin(L"Skin"#name); \
} \
DELETE_ALL_CONSTRUCT(Skin##name)

#define ATTR(name, value, comment) constexpr static Attr name = value

namespace winui {
	class Skin {
	public:
		// 绘画模式
		CON_EX_BEGIN(DrawMode)
		ATTR(Src, 0, "素材"); ATTR(Null, -1, "无");
		ATTR(Rectange, -2, "矩形"); ATTR(AngleRectange, -3, "圆角矩形");
		ATTR(TriAngle, -4, "三角形"); ATTR(Line, -5, "直线");
		ATTR(ShadowRectange, -102, "阴影矩形"); ATTR(ShadowAngleRectange, -103, "阴影圆角矩形");
		ATTR(ShadowTriAngle, -104, "阴影三角形");
		CON_EX_END(DrawMode)
	protected:
		struct ResInfo final {
			int drawMode; // 绘画模式
			int cutLeft; // 裁剪区左
			int cutTop; // 裁剪区顶
			int cutWidth; // 裁剪区宽
			int cutHeight; // 裁剪区高
			int left; // 九宫左
			int top; // 九宫上
			int right; // 九宫右
			int bottom; // 九宫下
			int version; // 版本
			int shadowWidth; // 阴影宽度
			int shadowColor; // 阴影色
			int shadowAngle; // 阴影圆角
			int shadowLineWidth; // 阴影边线宽度
			int shadowLineColor; // 阴影边线色
		};
		struct SkinInfo final {
			int version; // 版本
			int type; // 类型
			int resCount; // 资源数
			int srcCount; // 素材数
			int valueCount; // 附加数据数
			int nameLen; // 名称长度
			int authorLen; // 作者长度
			wchar_t* name; // 名称
			wchar_t* author; // 作者
			int* value; // 附加数据
			ResInfo* res; // 资源
			int* srcSize; // 素材尺寸数组
			void** srcBegin; // 素材指针起始
		};
	protected:
		SkinInfo* mInfo = nullptr;
	public:
		DELETE_ALL_CONSTRUCT(Skin);
		Skin(const Bin& bin) noexcept;
		~Skin() noexcept;
		Bin Create() noexcept;
	};

	class SkinWindow : public Skin {
	public:
		SKIN_CONSTRUCT(Window);
		// 置背景
		SkinWindow& BackGround(const Bin& bin) noexcept;
		// 置圆角
		SkinWindow& Angle(int angle) noexcept;
	};

	class SkinEdit : public Skin {
	public:
		SKIN_CONSTRUCT(Edit);
	};

	class SkinButton : public Skin {
	public:
		SKIN_CONSTRUCT(Button);
	};

	class SkinPicture : public Skin {
	public:
		SKIN_CONSTRUCT(Picture);
		// 透明化
		SkinPicture& Transparent() noexcept;
	};

	class SkinGroup : public Skin {
	public:
		SKIN_CONSTRUCT(Group);
	};

	class SkinRadio : public Skin {
	public:
		SKIN_CONSTRUCT(Radio);
	};

	class SkinChoice : public Skin {
	public:
		SKIN_CONSTRUCT(Choice);
	};

	class SkinSwitch : public Skin {
	public:
		SKIN_CONSTRUCT(Switch);
	};

	class SkinProgress : public Skin {
	public:
		SKIN_CONSTRUCT(Progress);
	};

	class SkinSlider : public Skin {
	public:
		SKIN_CONSTRUCT(Slider);
	};

	class SkinScroll : public Skin {
	public:
		SKIN_CONSTRUCT(Scroll);
	};

	class SkinCombo : public Skin {
	public:
		SKIN_CONSTRUCT(Combo);
	};

	class SkinIconButton : public Skin {
	public:
		SKIN_CONSTRUCT(IconButton);
	};

	class SkinList : public Skin {
	public:
		SKIN_CONSTRUCT(List);
	};

	class SkinIconList : public Skin {
	public:
		SKIN_CONSTRUCT(IconList);
	};

	class SkinSuperList : public Skin {
	public:
		SKIN_CONSTRUCT(SuperList);
	};

	class SkinSelector : public Skin {
	public:
		SKIN_CONSTRUCT(Selector);
	};

	class SkinCalendar : public Skin {
	public:
		SKIN_CONSTRUCT(Calendar);
	};

	class SkinColorPick : public Skin {
	public:
		SKIN_CONSTRUCT(ColorPick);
	};
}

namespace winui {
	class SkinMenu : public Skin {
	public:
		SKIN_CONSTRUCT(Menu);
	};
}

namespace winui {
	class SkinMsgBox : public Skin {
	public:
		SKIN_CONSTRUCT(MsgBox);
	};

	class SkinInputBox : public Skin {
	public:
		SKIN_CONSTRUCT(InputBox);
	};
}

#undef ATTR
#undef SKIN_CONSTRUCT
#undef CON_EX_BEGIN
#undef CON_EX_END
#undef DELETE_ALL_CONSTRUCT