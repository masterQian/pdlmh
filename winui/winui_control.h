#pragma once
#include "winui_attr.h"
#include "winui_base.h"

#define DEFAULT_CONSTRUCT_COPY_MOVE(name) \
name(const name&) = default; \
name(name&&) = default; \
name& operator = (const name&) = default; \
name& operator = (name&&) = default

#define CONTROL_CONSTRUCT(name) \
name() noexcept = default; \
name(ID id_) noexcept : Control(id_) {} \
DEFAULT_CONSTRUCT_COPY_MOVE(name)

#define ATTR_BOOL(cl, attr) bool attr() const noexcept; \
void attr(bool attr##_) noexcept
#define ATTR_INT(cl, attr) int attr() const noexcept; \
void attr(int attr##_) noexcept
#define ATTR_ARGB(cl, attr) ARGB attr() const noexcept; \
void attr(ARGB attr##_) noexcept
#define ATTR_ATTR(cl, attr) Attr attr() const noexcept; \
void attr(Attr attr##_) noexcept
#define ATTR_STR(cl, attr) String attr() const noexcept; \
void attr(ConstString attr##_) noexcept
#define ATTR_ICO(cl, attr) ICO attr() const noexcept; \
void attr(const ICO& attr##_) noexcept
#define ATTR_BIN(cl, attr) Bin attr() const noexcept; \
void attr(const Bin& attr##_) noexcept

namespace winui {
	class Window;
	// 子控件组
	using Children = std::unordered_map<String, ID>;
	// 附加信息
	using ExtraInfo = std::unordered_map<String, Memory>;
	// 组件标记
	struct SignControl {
		Children children;
		Call callback = nullptr;
		String name;
		ExtraInfo* info = nullptr;
	};
	// 窗口组件标记
	struct SignWindow : public SignControl {
		Window* pWindow = nullptr;
		HWND winHwnd = nullptr;
		int left = 0, top = 0;
		bool initialize = false;
		bool notShow = false;
	};
	// 控件基类
	class Control {
	protected:
		ID id = 0;
	protected:
		bool CheckName(const Children& children, ConstString name) noexcept;
		static void Release(ID id, SignControl* sign) noexcept;
		static Result __stdcall __ControlCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4);
	public:
		Control() noexcept = default;
		Control(ID id) noexcept { this->id = id; }
		DEFAULT_CONSTRUCT_COPY_MOVE(Control);
#define Method_Control(name, type) type name() const noexcept; \
void name(const type& name##_) noexcept
		Method_Control(Left, int);
		Method_Control(Top, int);
		Method_Control(Width, int);
		Method_Control(Height, int);
		Method_Control(Visual, bool);
		Method_Control(Disabled, bool);
		Method_Control(Penetrate, int);
		Method_Control(Transparency, int);
		Method_Control(FocusWeight, int);
		Method_Control(FocusControl, bool);
#undef Method_Control
		Bin Cursor() const noexcept;
		void Cursor(const Bin& cursor) noexcept;
		Rectangle Rect() const noexcept;
		void Rect(const Rectangle& rect) noexcept;
		int Type() const noexcept;
		void Destroy() noexcept;
		void Repaint() noexcept;
		void LockUpdate() noexcept;
		void UnlockUpdate() noexcept;
		Call CallBack() const noexcept;
		void CallBack(Call callback) noexcept;
		String Name() const noexcept;
		ID Parent() const noexcept;
		Children& Child() const noexcept;
		Control operator () (ConstString name) const noexcept;
		LRESULT SendEvent(Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) noexcept;
		void PostEvent(Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) noexcept;
		SignControl* Sign() const noexcept;
		constexpr operator ID() const noexcept { return id; }
		static constexpr Call GetDefaultCallBack() noexcept { return __ControlCallBack; }
		constexpr void From(ID id) noexcept { this->id = id; }
	};

	// 窗口
	class Window : public Control {
	public:
		CONTROL_CONSTRUCT(Window);
		void Start(Call callback, ExtraInfo info = {}, bool alwaysTop = false,
			bool taskBarShow = false, bool notShow = false, ConstString name = {},
			int left = 100, int top = 100, int width = 480, int height = 300,
			ConstString title = {}) noexcept;
		HWND GetWinHwnd() const noexcept;
		void Destroy() noexcept;
		ATTR_BIN(Window, Skin);
		ATTR_BIN(Window, Icon);
		ATTR_STR(Window, Title);
		ATTR_BIN(Window, Font);
		ATTR_ARGB(Window, FontColor);
		ATTR_INT(Window, LayeredTransparency);
		ATTR_INT(Window, DragMode);
		int Left() const noexcept;
		void Left(int left) noexcept;
		int Top() const noexcept;
		void Top(int top) noexcept;
		int Width() const noexcept;
		void Width(int width) noexcept;
		int Height() const noexcept;
		void Height(int height) noexcept;
		Rectangle Rect() const noexcept;
		void Rect(const Rectangle& rect) noexcept;
		bool CanMove() const noexcept;
		void CanMove(bool sizeMode) noexcept;
		Attr ControlButton() const noexcept;
		void ControlButton(Attr attr) noexcept;
		bool GroundGlass(bool effect = true) noexcept;
		static bool AddWinEvent(Event msg) noexcept;
	};

	// 标签
	class Label : public Control {
	public:
		CONTROL_CONSTRUCT(Label);
		Label(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, ConstString str = {},
			ARGB fontColor = Color::Black, const Bin& font = {}, ARGB backColor = Color::Null,
			Attr align = Attrs::Align::Start_Center_Mul) noexcept;
		ATTR_STR(Label, Title);
		ATTR_BIN(Label, Font);
		ATTR_ATTR(Label, Align);
		ATTR_ARGB(Label, BackColor);
		ATTR_ARGB(Label, FontColor);
	};

	// 编辑框
	class Edit : public Control {
	public:
		CONTROL_CONSTRUCT(Edit);
		Edit(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, bool noMenu = false) noexcept;
		ATTR_BIN(EditboxEx, Skin);
		ATTR_STR(EditboxEx, Content);
		ATTR_ATTR(EditboxEx, ItemAlign);
		ATTR_ATTR(EditboxEx, InputMode);
		ATTR_INT(EditboxEx, MaxLen);
		ATTR_STR(EditboxEx, PwdSub);
		ATTR_ARGB(EditboxEx, CursorColor);
		ATTR_BIN(EditboxEx, Font);
		ATTR_ARGB(EditboxEx, FontColor);
		ATTR_ARGB(EditboxEx, SelectFontColor);
		ATTR_ARGB(EditboxEx, SelectBackColor);
		ATTR_INT(EditboxEx, LeftReservation);
		ATTR_INT(EditboxEx, RightReservation);
		ATTR_BOOL(EditboxEx, MultiLine);
		ATTR_BOOL(EditboxEx, AutoLine);
		ATTR_ATTR(EditboxEx, ScrollBarMode);
	};

	// 按钮
	class Button : public Control {
	public:
		CONTROL_CONSTRUCT(Button);
		Button(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, ConstString title = {}) noexcept;
		ATTR_BIN(Button, Skin);
		ATTR_STR(Button, Title);
		ATTR_BIN(Button, Font);
		ATTR_ARGB(Button, FontColor);
	};

	// 图片框
	class Picture : public Control {
	public:
		CONTROL_CONSTRUCT(Picture);
		Picture(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, const Bin& image = {},
			Attr mapMode = Attrs::MapMode::UpperLeft) noexcept;
		ATTR_BIN(PictureBoxEx, Skin);
		ATTR_BIN(PictureBoxEx, Image);
		ATTR_ATTR(PictureBoxEx, MapMode);
		ATTR_INT(PictureBoxEx, Angle);
		ATTR_BOOL(PictureBoxEx, PlayAnimation);
		ATTR_INT(PictureBoxEx, CurrentFrame);
		int AllFrame() const noexcept;
	};

	// 分组框
	class Group : public Control {
	public:
		CONTROL_CONSTRUCT(Group);
		Group(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40,
			ConstString title = {}, ARGB fontColor = Color::Black,
			const Bin& icon = {}, int iconWidth = 0, int iconHeight = 0) noexcept;
		ATTR_BIN(MinutesboxEx, Skin);
		ATTR_BIN(MinutesboxEx, Icon);
		ATTR_INT(MinutesboxEx, IconWidth);
		ATTR_INT(MinutesboxEx, IconHeight);
		ATTR_STR(MinutesboxEx, Title);
		ATTR_ATTR(MinutesboxEx, Align);
		ATTR_BIN(MinutesboxEx, Font);
		ATTR_ARGB(MinutesboxEx, FontColor);
	};

	// 单选框
	class Radio : public Control {
	public:
		CONTROL_CONSTRUCT(Radio);
		Radio(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, bool select = false,
			ConstString title = {}, ARGB fontColor = Color::Black) noexcept;
		ATTR_BIN(RadiobuttonEx, Skin);
		ATTR_BOOL(RadiobuttonEx, Select);
		ATTR_STR(RadiobuttonEx, Title);
		ATTR_BIN(RadiobuttonEx, Font);
		ATTR_ARGB(RadiobuttonEx, FontColor);
	};

	// 复选框
	class Choice : public Control {
	public:
		CONTROL_CONSTRUCT(Choice);
		Choice(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, bool select = false,
			ConstString title = {}, ARGB fontColor = Color::Black) noexcept;
		ATTR_BIN(ChoiceboxEx, Skin);
		ATTR_BOOL(ChoiceboxEx, Select);
		ATTR_STR(ChoiceboxEx, Title);
		ATTR_BIN(ChoiceboxEx, Font);
		ATTR_ARGB(ChoiceboxEx, FontColor);
	};

	// 开关
	class Switch : public Control {
	public:
		CONTROL_CONSTRUCT(Switch);
		Switch(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, bool select = false) noexcept;
		ATTR_BIN(SlideButtonEx, Skin);
		ATTR_BOOL(SlideButtonEx, Select);
	};

	// 进度条
	class Progress : public Control {
	public:
		CONTROL_CONSTRUCT(Progress);
		Progress(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, int pos = 0,
			int minPos = 0, int maxPos = 100, Attr style = Attrs::ProgressStyle::Bar,
			Attr direction = Attrs::ProgressDirection::Right) noexcept;
		ATTR_BIN(ProgressbarEx, Skin);
		ATTR_INT(ProgressbarEx, Pos);
		ATTR_INT(ProgressbarEx, MinPos);
		ATTR_INT(ProgressbarEx, MaxPos);
		ATTR_ATTR(ProgressbarEx, Style);
		ATTR_ATTR(ProgressbarEx, Direction);
	};

	// 滑块条
	class Slider : public Control {
	public:
		CONTROL_CONSTRUCT(Slider);
		Slider(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, int pos = 0,
			int minPos = 0, int maxPos = 100, bool dragTrace = false, bool direction = false) noexcept;
		ATTR_BIN(SliderbarEx, Skin);
		ATTR_INT(SliderbarEx, Pos);
		ATTR_INT(SliderbarEx, MinPos);
		ATTR_INT(SliderbarEx, MaxPos);
		ATTR_INT(SliderbarEx, ClickStep);
		ATTR_BOOL(SliderbarEx, DragTrace);
		ATTR_BOOL(SliderbarEx, Direction);
	};

	// 滚动条
	class Scroll : public Control {
	public:
		CONTROL_CONSTRUCT(Scroll);
		Scroll(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, int pos = 0,
			int minPos = 0, int maxPos = 100, bool direction = false) noexcept;
		ATTR_BIN(ScrollbarEx, Skin);
		ATTR_INT(ScrollbarEx, Pos);
		ATTR_INT(ScrollbarEx, MinPos);
		ATTR_INT(ScrollbarEx, MaxPos);
		ATTR_INT(ScrollbarEx, BarSize);
		ATTR_INT(ScrollbarEx, ButtonStep);
		ATTR_INT(ScrollbarEx, ClickStep);
		ATTR_BOOL(ScrollbarEx, Direction);
	};

	// 组合框
	class Combo : public Control {
	public:
		CONTROL_CONSTRUCT(Combo);
		Combo(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, const Bin& font = {}) noexcept;
		ATTR_BIN(ComboboxEx, Skin);
		ATTR_ATTR(ComboboxEx, Align);
		ATTR_ARGB(ComboboxEx, CursorColor);
		ATTR_BIN(ComboboxEx, Font);
		ATTR_ARGB(ComboboxEx, FontColor);
		ATTR_ARGB(ComboboxEx, SelectFontColor);
		ATTR_ARGB(ComboboxEx, SelectBackColor);
		ATTR_INT(ComboboxEx, LeftReservation);
		ATTR_INT(ComboboxEx, RightReservation);
		ATTR_INT(ComboboxEx, ListWidth);
		ATTR_INT(ComboboxEx, ListHeight);
		ATTR_INT(ComboboxEx, IconWidth);
		ATTR_INT(ComboboxEx, IconHeight);
		ATTR_BIN(ComboboxEx, ListFont);
		ATTR_BOOL(ComboboxEx, AlternateColor);
		ATTR_INT(ComboboxEx, ListTransparency);
		int CurrentItem() const noexcept;
		void CurrentItem(int index) const noexcept;
		bool isOpen() const noexcept;
		void Open() const noexcept;
		void Close() const noexcept;
		int InsertItem(int index = -1, ConstString title = {}, const ICO& icon = {},
			ARGB fontColor = Color::Black, int height = 35, int data = 0) noexcept;
		void DeleteItem(int index) noexcept;
		void ClearItem() noexcept;
		int ItemCount() const noexcept;
		String ItemTitle(int index) const noexcept;
		void ItemTitle(int index, ConstString title) noexcept;
		ICO ItemIcon(int index) const noexcept;
		void ItemIcon(int index, const ICO& icon) noexcept;
		ARGB ItemFontColor(int index) const noexcept;
		void ItemFontColor(int index, ARGB color) noexcept;
		int ItemHeight(int index) const noexcept;
		void ItemHeight(int index, int height) noexcept;
		int ItemData(int index) const noexcept;
		void ItemData(int index, int data) noexcept;
	};

	// 图标按钮
	class IconButton : public Control {
	public:
		CONTROL_CONSTRUCT(IconButton);
		IconButton(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40, ConstString title = {},
			const Bin& icon = {}, int iconWidth = 0, int iconHeight = 0) noexcept;
		ATTR_BIN(SuperbuttonEx, Skin);
		ATTR_BIN(SuperbuttonEx, Icon);
		ATTR_INT(SuperbuttonEx, IconWidth);
		ATTR_INT(SuperbuttonEx, IconHeight);
		ATTR_BOOL(SuperbuttonEx, IconUp);
		ATTR_STR(SuperbuttonEx, Title);
		ATTR_BIN(SuperbuttonEx, Font);
		ATTR_ARGB(SuperbuttonEx, FontColor);
	};

	// 列表框
	class List : public Control {
	public:
		CONTROL_CONSTRUCT(List);
		List(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40) noexcept;
		ATTR_BIN(ListboxEx, Skin);
		ATTR_INT(ListboxEx, CurrentItem);
		ATTR_INT(ListboxEx, IconWidth);
		ATTR_INT(ListboxEx, IconHeight);
		ATTR_BIN(ListboxEx, Font);
		ATTR_BOOL(ListboxEx, AlternateColor);
		ATTR_ATTR(ListboxEx, ScrollBarMode);
		int InsertItem(int index = -1, ConstString title = {}, const ICO& icon = {},
			ARGB fontColor = Color::Black, int height = 35, int data = 0) noexcept;
		void DeleteItem(int index) noexcept;
		void ClearItem() noexcept;
		int ItemCount() const noexcept;
		String ItemTitle(int index) const noexcept;
		void ItemTitle(int index, ConstString title) noexcept;
		ICO ItemIcon(int index) const noexcept;
		void ItemIcon(int index, const ICO& icon) noexcept;
		int ItemData(int index) const noexcept;
		void ItemData(int index, int data) noexcept;
		ARGB ItemFontColor(int index) const noexcept;
		void ItemFontColor(int index, ARGB color) noexcept;
		int ItemHeight(int index) const noexcept;
		void ItemHeight(int index, int height) noexcept;
	};

	// 图标列表框
	class IconList : public Control {
	public:
		CONTROL_CONSTRUCT(IconList);
		IconList(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40) noexcept;
		ATTR_BIN(IcoListboxEx, Skin);
		ATTR_INT(IcoListboxEx, CurrentItem);
		ATTR_INT(IcoListboxEx, ItemWidth);
		ATTR_INT(IcoListboxEx, ItemHeight);
		ATTR_INT(IcoListboxEx, HSpace);
		ATTR_INT(IcoListboxEx, VSpace);
		ATTR_INT(IcoListboxEx, IconWidth);
		ATTR_INT(IcoListboxEx, IconHeight);
		ATTR_BIN(IcoListboxEx, Font);
		ATTR_BOOL(IcoListboxEx, IconUp);
		ATTR_ATTR(IcoListboxEx, ScrollBarMode);
		int InsertItem(int index = -1, ConstString title = {}, const ICO& icon = {},
			ARGB fontColor = Color::Black, int data = 0) noexcept;
		void DeleteItem(int index, int num = 1) noexcept;
		void ClearItem() noexcept;
		int ItemCount() const noexcept;
		String ItemTitle(int index) const noexcept;
		void ItemTitle(int index, ConstString title) noexcept;
		ICO ItemIcon(int index) const noexcept;
		void ItemIcon(int index, const ICO& icon) noexcept;
		int ItemData(int index) const noexcept;
		void ItemData(int index, int data) noexcept;
		ARGB ItemFontColor(int index) const noexcept;
		void ItemFontColor(int index, ARGB color) noexcept;
	};

	// 超级列表框
	class SuperList : public Control {
	public:
		CONTROL_CONSTRUCT(SuperList);
		SuperList(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40) noexcept;
		ATTR_BIN(SuperListboxEx, Skin);
		ATTR_INT(SuperListboxEx, CurrentItem);
		ATTR_INT(SuperListboxEx, HeadHeight);
		ATTR_ATTR(SuperListboxEx, HeadMode);
		ATTR_BOOL(SuperListboxEx, AlternateColor);
		ATTR_ATTR(SuperListboxEx, LineMode);
		ATTR_ATTR(SuperListboxEx, ScrollBarMode);
		int InsertColumn(int index, ConstString title, ARGB fontColor = Color::Black,
			int width = 40, Attr itemAlign = Attrs::ItemAlign::Left, int iconWidth = 0,
			int iconHeight = 0, const Bin& font = {}) noexcept;
		void DeleteColumn(int index) noexcept;
		void ClearColumn() noexcept;
		int ColumnCount() const noexcept;
		int InsertItem(int index = -1, int height = 35, int data = 0, int num = 1) noexcept;
		void DeleteItem(int index, int num = 1) noexcept;
		void ClearItem() noexcept;
		int ItemCount() const noexcept;
		String ItemTitle(int index, int col) const noexcept;
		void ItemTitle(int index, int col, ConstString title) noexcept;
		ICO ItemIcon(int index, int col) const noexcept;
		void ItemIcon(int index, int col, const ICO& icon) noexcept;
		int ItemData(int index) const noexcept;
		void ItemData(int index, int data) noexcept;
		ARGB ItemFontColor(int index, int col) const noexcept;
		void ItemFontColor(int index, int col, ARGB color) noexcept;
		int ItemHeight(int index) const noexcept;
		void ItemHeight(int index, int height) noexcept;
		String InputAt(int index, int col, Attr align = Attrs::Align::Start_Start_Mul,
			const Bin& font = {}, ARGB fontColor = Color::Black, const Bin& skin = {}) noexcept;
	};

	// 选择夹
	class Selector : public Control {
	public:
		CONTROL_CONSTRUCT(Selector);
		Selector(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40) noexcept;
		ATTR_BIN(SelectthefolderEx, Skin);
		ATTR_INT(SelectthefolderEx, CurrentItem);
		ATTR_INT(SelectthefolderEx, ItemHeight);
		ATTR_ATTR(SelectthefolderEx, TabDirection);
		ATTR_INT(SelectthefolderEx, Space);
		ATTR_INT(SelectthefolderEx, IconWidth);
		ATTR_INT(SelectthefolderEx, IconHeight);
		ATTR_BIN(SelectthefolderEx, Font);
		int InsertItem(int index = -1, ConstString title = {}, const ICO& icon = {},
			ARGB fontColor = Color::Black, int width = 80, int data = 0) noexcept;
		void DeleteItem(int index) noexcept;
		void ClearItem() noexcept;
		int ItemCount() const noexcept;
		String ItemTitle(int index) const noexcept;
		void ItemTitle(int index, ConstString title) noexcept;
		ICO ItemIcon(int index) const noexcept;
		void ItemIcon(int index, const ICO& icon) noexcept;
		int ItemData(int index) const noexcept;
		void ItemData(int index, int data) noexcept;
		ARGB ItemFontColor(int index) const noexcept;
		void ItemFontColor(int index, ARGB color) noexcept;
		int ItemHeight(int index) const noexcept;
		void ItemHeight(int index, int width) noexcept;
		bool Add(int index, const Control& control) noexcept;
	};

	// 日历
	class Calendar : public Control {
	public:
		struct Date final { int year, month, day; };
	public:
		CONTROL_CONSTRUCT(Calendar);
		Calendar(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40) noexcept;
		ATTR_BIN(CalendarBoxEx, Skin);
		ATTR_BOOL(CalendarBoxEx, OnlyThisMonth);
		ATTR_INT(CalendarBoxEx, TitleHeight);
		ATTR_INT(CalendarBoxEx, WeekHeight);
		Date CurrentDate() const noexcept;
		void CurrentDate(int year, int month, int day) noexcept;
		void CurrentDate(const Date& date) noexcept;
		void Font(const Bin& titleFont, const Bin& weekFont, const Bin& dayFont) noexcept;
		void FontColor(ARGB title, ARGB week, ARGB weekend, ARGB day, ARGB weekendDay, ARGB otherMonth) noexcept;
	};

	// 选色板
	class ColorPick : public Control {
	public:
		CONTROL_CONSTRUCT(ColorPick);
		ColorPick(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40) noexcept;
		ATTR_BIN(ColorPick, Skin);
		ATTR_BIN(ColorPick, Font);
		ATTR_ARGB(ColorPick, FontColor);
		ATTR_ARGB(ColorPick, CurrentColor);
		ATTR_BOOL(ColorPick, DragTrace);
		ATTR_BOOL(ColorPick, useRGB);
		ATTR_INT(ColorPick, RegulatorHeight);
	};

	// 画板
	class Draw : public Control {
	public:
		CONTROL_CONSTRUCT(Draw);
		Draw(Call callback, const Control& parent, ConstString name = {},
			int left = 0, int top = 0, int width = 80, int height = 40,
			ARGB backColor = Color::White) noexcept;
		ATTR_ARGB(DrawPanelEx, BackColor);
		ATTR_ARGB(DrawPanelEx, BroderColor);
		void Line(int x1, int y1, int x2, int y2, ARGB color = Color::Black,
			int width = 1, Attr lineStyle = Attrs::LineStyle::Solid) noexcept;
		void Arc(int x1, int y1, int x2, int y2, int start, int end, ARGB color = Color::Black,
			int width = 1, Attr lineStyle = Attrs::LineStyle::Solid) noexcept;
		void Rectange(int x1, int y1, int x2, int y2, ARGB color = Color::Black,
			ARGB effectColor = Color::Null, int width = 1, Attr brushStyle = Attrs::BrushStyle::Null) noexcept;
		void Circle(int x, int y, int r, ARGB color = Color::Black, ARGB effectColor = Color::Null,
			int width = 1, Attr brushStyle = Attrs::BrushStyle::Null) noexcept;
		void Ellipse(int x, int y, int a, int b, ARGB color = Color::Black, ARGB effectColor = Color::Null,
			int width = 1, Attr brushStyle = Attrs::BrushStyle::Null) noexcept;
		void Pie(int x1, int y1, int x2, int y2, int start, int end, ARGB color = Color::Black,
			ARGB effectColor = Color::Null, int width = 1, Attr brushStyle = Attrs::BrushStyle::Null) noexcept;
		void Text(ConstString text, int left, int top, ARGB color = Color::Black, const Bin& font = {}) noexcept;
		void Image(const ICO& image, int left = 0, int top = 0, int width = -1, int height = -1,
			int srcLeft = 0, int srcTop = 0, int srcWidth = -1, int srcHeight = -1, int transparency = 255) noexcept;
		void Effect(Attr smoothMode, Attr algorithmMode, Attr offsetMode) noexcept;
		void Clear() noexcept;
		void Update() noexcept;
	};
}

#undef ATTR_INT
#undef ATTR_ARGB
#undef ATTR_ATTR
#undef ATTR_STR
#undef ATTR_BIN
#undef CONTROL_CONSTRUCT
#undef DEFAULT_CONSTRUCT_COPY_MOVE