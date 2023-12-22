#pragma once
#include "winui_control.h"
#include "winui_menu.h"

namespace winui {
	using VDSwitcher = std::unordered_map<String, Memory>; // View/Data交换机
	namespace layout {
		enum class LayoutNodeType {
			Text = 0, // 文本
			Array = 1, // 数组
			Object = 2, // 对象
		};

		struct LayoutNode;
		using LayoutArray = std::vector<LayoutNode*>;
		using LayoutObject = std::unordered_map<String, LayoutNode*>;
		// 布局结点
		struct LayoutNode {
			LayoutNodeType type{}; // 类型
			union LayoutNodeData {
				String* str; // 文本
				LayoutArray* arr; // 数组
				LayoutObject* obj; // 对象
			}data{};
		};

		// 提取字符串
		String InflateString(ConstString key, const layout::LayoutObject* obj, const VDSwitcher& map, ConstString def = {}, bool isNotEmpty = false) noexcept;
		// 提取逻辑值
		bool InflateBool(ConstString key, const layout::LayoutObject* obj, const VDSwitcher& map, bool def = false) noexcept;
		// 提取整数
		int InflateInt(ConstString key, const layout::LayoutObject* obj, const VDSwitcher& map, int def = 0) noexcept;
		// 提取浮点数
		float InflateFloat(ConstString key, const layout::LayoutObject* obj, const VDSwitcher& map, float def = 0.0F) noexcept;
		// 提取映射对象
		bool InflateVDMap(ConstString key, const layout::LayoutObject* obj, const VDSwitcher& map, Memory& mem) noexcept;
		// 提取字节集
		Bin InflateBin(ConstString key, const layout::LayoutObject* obj, const VDSwitcher& map) noexcept;
	}
}

namespace winui {
	// 布局加载器
	class Layout final {
		Layout() = delete;
	public:
		// 布局映射函数
		using InflateFunc = ID(*)(ID, const layout::LayoutObject*, const VDSwitcher&) noexcept;
	private:
		// 默认布局映射
		static std::unordered_map<String, InflateFunc> InflateMap;
	public:
		// 取布局映射
		static const std::unordered_map<String, InflateFunc>& GetInflateMap() noexcept { return InflateMap; }
		// 映射数组结构
		static std::vector<String> InflateArray(ConstString data, const VDSwitcher& map) noexcept;
		// 映射映射结构
		static std::unordered_map<String, String> InflateMapper(ConstString data, const VDSwitcher& map) noexcept;
		// 映射窗口布局
		static void InflateWindow(Window& windowEx, ConstString data, const VDSwitcher& map) noexcept;
		// 映射控件布局
		static ID InflateControl(ID parent, ConstString data, const VDSwitcher& map) noexcept;
		// 映射菜单布局
		static void InflateMenu(Menu& menu, ConstString data, const VDSwitcher& map) noexcept;
		// 注册布局映射函数
		static bool Register(ConstString type, InflateFunc func);
	};
}

/* [窗口布局]
	左边 int Left = 100
	顶边 int Top = 100
	宽度 int Width = 480
	高度 int Height = 300
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	皮肤 @Bin Skin = {}
	图标 @Bin Icon = {}
	字体 @Bin Font = {}
	标题 String Title = ""
	字体色 ARGB FontColor = @Color::Black
	分层透明 int LayeredTransparency = 256
	拖动模式 Attr DragMode = @Attrs::DragMode::Title
	自由移动 bool CanMove = true
	控制钮 Attr ControlButton = @Attrs::ControlButton::Min_Max_Close
	毛玻璃 bool GroundGlass = false
	子控件数组 Array<Object> Children = {}
*/

/* [菜单布局]
	皮肤 @Bin Skin = {}
	菜单回调 @MenuCall CallBack = nullptr
	图标宽度 int IconWidth = 0
	图标高度 int IconHeight = 0
	字体 @Bin Font = {}
	鼠标指针 @Bin Cursor = {}
	透明度 int Transparency = 255
	子菜单宽度 int ChildWidth = 60
	子菜单数组 Array<Object> Items = {}
*/

/* [菜单项布局]
	是否是分割线 bool Separate = false
	<分割线 Separate = true>
		高度 int Height = 10
	<菜单项 Separate = false>
		高度 int Height = 35
		子菜单宽度 int ChildWidth = 60
		标记 short Tag = 0
		图标 @Bin Icon = {}
		标题 String Title = ""
		字体色 ARGB FontColor = @Color::Black
		禁止字体色 ARGB DisabledFontColor = @Color::Gray
		禁止 bool Disabled = false
		子菜单数组 Array<Object> Items = {}
*/

/* [标签布局]
	类型 String Type == Label
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	标题 String Title = ""
	对齐方式 Attr Align = @Attrs::Align::Start_Center_Mul
	背景色 ARGB BackColor = @Color::Null
	字体 @Bin Font = {}
	字体色 ARGB FontColor = @Color::Black
*/

/* [编辑框布局]
	类型 String Type == Edit
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	内容 String Content = ""
	密码掩盖符 String PwdSub = "*"
	无右键菜单 bool NoMenu = false
	内容对齐方式 Attr ItemAlign = @Attrs::ItemAlign::Left
	输入模式 Attr InputMode = @Attrs::InputMode::Normal
	最大输入长度 int MaxLen = 0
	光标色 ARGB CursorColor = -33554432
	字体 @Bin Font = {}
	字体色 ARGB FontColor = -33554432
	选中字体色 ARGB SelectFontColor = @Color::Black
	选中背景色 ARGB SelectBackColor = -436172545
	左预留 int LeftReservation = 0
	右预留 int LeftReservation = 0
	多行显示 bool MultiLine = false
	自动换行 bool AutoLine = false
	滚动条模式 Attr ScrollBarMode = @Attrs::ScrollBarMode::HorVec
*/

/* [按钮布局]
	类型 String Type == Button
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	标题 String Title = ""
	字体 @Bin Font = {}
	字体色 ARGB FontColor = @Color::Black
*/

/* [图片框布局]
	类型 String Type == Picture
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	图片 @Bin Image = {}
	底图模式 Attr MapMode = @Attrs::MapMode::UpperLeft
	旋转角度 int Angle = 0
	播放动画 bool PlayAnimation = false
	当前帧 int CurrentFrame = 0
*/

/* [分组框布局]
	类型 String Type == Group
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	图标 @Bin Icon = {}
	图标宽度 int IconWidth = 0
	图标高度 int IconHeight = 0
	标题 String Title = ""
	对齐方式 Attr Align = @Attrs::Align::Start_Start_Mul
	字体 @Bin Font = {}
	字体色 ARGB FontColor = @Color::Black
*/

/* [单选框布局]
	类型 String Type == Radio
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	选中 bool Select = false
	标题 String Title = ""
	字体 @Bin Font = {}
	字体色 ARGB FontColor = @Color::Black
*/

/* [复选框布局]
	类型 String Type == Choice
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	选中 bool Select = false
	标题 String Title = ""
	字体 @Bin Font = {}
	字体色 ARGB FontColor = @Color::Black
*/

/* [开关布局]
	类型 String Type == Switch
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	选中 bool Select = false
*/

/* [进度条布局]
	类型 String Type == Progress
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	位置 int Pos = 0
	最小位置 int MinPos = 0
	最大位置 int MaxPos = 100
	风格 Attr Style = @Attrs::ProgressStyle::Bar
	方向 Attr Direction = @Attrs::ProgressDirection::Right
*/

/* [滑块条布局]
	类型 String Type == Slider
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	位置 int Pos = 0
	最小位置 int MinPos = 0
	最大位置 int MaxPos = 100
	点击步长 int ClickStep = 3
	拖动跟踪 bool DragTrace = false
	纵向显示 bool Direction = false
*/

/* [滚动条布局]
	类型 String Type == Scroll
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	位置 int Pos = 0
	最小位置 int MinPos = 0
	最大位置 int MaxPos = 100
	滚动条长 int BarSize = (#MaxPos - #MinPos) / 4
	按钮点击步长 int ButtonStep = 10
	点击步长 int ClickStep = 5
	纵向显示 bool Direction = false
*/

/* [组合框布局]
	类型 String Type == Combo
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	对齐方式 Attr Align = @Attrs::Align::Start_Start_Mul
	光标色 ARGB CursorColor = -33554432
	字体 @Bin Font = {}
	选中字体色 ARGB CursorColor = @Color::Black
	选中背景色 ARGB CursorColor = -436172545
	左预留 int LeftReservation = 0
	右预留 int LeftReservation = 0
	列表宽度 int ListWidth = 0
	列表高度 int ListHeight = #Height * 5
	图标宽度 int IconWidth = 0
	图标高度 int IconHeight = 0
	项目字体 @Bin ListFont = {}
	隔行换色 bool AlternateColor = false
	列表透明度 int ListTransparency = 255
	当前选中项 int CurrentItem = -1
	列表数据 Array<String> Data = {}
*/

/* [图标按钮布局]
	类型 String Type == IconButton
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	图标 @Bin Icon = {}
	图标宽度 int IconWidth = 0
	图标高度 int IconHeight = 0
	图标居上 bool IconUp = false
	标题 String Title = ""
	字体 @Bin Font = {}
	字体色 ARGB FontColor = @Color::Black
*/

/* [列表框布局]
	类型 String Type == List
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	字体 @Bin Font = {}
	图标宽度 int IconWidth = 0
	图标高度 int IconHeight = 0
	隔行换色 bool AlternateColor = false
	滚动条模式 Attr ScrollBarMode = @Attrs::ScrollBarMode::HorVec
	当前选中项 int CurrentItem = -1
	列表数据 Array<String> Data = {}
*/

/* [图标列表框布局]
	类型 String Type == IconList
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	字体 @Bin Font = {}
	项目宽度 int ItemWidth = 120
	项目高度 int ItemHeight = 90
	图标宽度 int IconWidth = 30
	图标高度 int IconHeight = 30
	横向间距 int HSpace = 5
	纵向间距 int VSpace = 5
	图标居上 bool IconUp = false
	滚动条模式 Attr ScrollBarMode = @Attrs::ScrollBarMode::HorVec
	当前选中项 int CurrentItem = -1
	列表数据 Array<Array<String = {}, ICO = {}, ARGB = @Color.Black, int = 0>>
*/

/* [超级列表框布局]
	类型 String Type == SuperList
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	表头高度 int HeadHeight = 40
	表头模式 Attr HeadMode = @Attrs::HeadMode::Event
	隔行换色 bool AlternateColor = false
	表格线模式 Attr LineMode = 31
	滚动条模式 Attr ScrollBarMode = @Attrs::ScrollBarMode::HorVec
*/

/* [选择夹布局]
	类型 String Type == Selector
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	皮肤 @Bin Skin = {}
	项目高度 int IconHeight = 36
	项目方向 Attr TabDirection = @Attrs::TabDirection::TopHor
	项目间距 int Space = 3
	图标宽度 int IconWidth = 20
	图标高度 int IconHeight = 20
	字体 @Bin Font = {}
	项目名称数组 Array<String> Tabs = {"默认子夹"}
	子夹数组 Array<Array<Object>> Children = {}
*/

/* [日历布局]
	类型 String Type == CalanderEx
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	仅显示当月 bool OnlyThisMonth = false
	标题高度 int TitleHeight = 30
	星期栏高度 int WeekHeight = 30
*/

/* [选色板布局]
	类型 String Type == ColorPick
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	皮肤 @Bin Skin = {}
	字体 @Bin Font = {}
	字体色 ARGB FontColor = -33554432
	当前选中色 ARGB CurrentColor = -12171448
	拖动跟踪 bool DragTrace = false
	RGB模式 bool useRGB = false
	调节器高度 int RegulatorHeight = #Height / 6
*/

/* [画板布局]
	类型 String Type == Draw
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	可视 bool Visual = true
	禁止 bool Disabled = false
	焦点控件 bool FocusControl = false
	鼠标穿透 int Penetrate = 0
	焦点权重 int FocusWeight = 0
	透明度 int Transparency = 255
	鼠标指针 @Bin Cursor = {}
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	背景色 ARGB BackColor = @Color::White
	边框色 ARGB BorderColor = @Color::Null
*/

/* [拓展::唱片布局]
	类型 String Type == plus::Record
	左边 int Left = 0
	顶边 int Top = 0
	宽度 int Width = 80
	高度 int Height = 40
	名称 String Name = #id
	回调函数 @Call CallBack = nullptr
	子控件数组 Array<Object> Children = {}
	图片 @Bin Image = {}
*/