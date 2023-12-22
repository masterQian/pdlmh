#pragma once
#include "winui_def.h"

#define CON_EX_BEGIN(name) class name final { \
name() = delete; \
public:
#define CON_EX_END(name) };

#define ATTR(name, value, comment) constexpr static Attr name = value

namespace winui {
	class Attrs final {
		Attrs() = delete;
	public:
		CON_EX_BEGIN(__Private)
		ATTR(Skin_WindowEx, 7, "皮肤"); ATTR(Icon_WindowEx, 8, "图标");
		ATTR(Title_WindowEx, 9, "标题"); ATTR(Font_WindowEx, 10, "字体");
		ATTR(FontColor_WindowEx, 11, "字体色");
		ATTR(LayeredTransparency_WindowEx, 12, "分层透明");
		ATTR(DragMode_WindowEx, 13, "拖动模式");
		ATTR(SizeMode_WindowEx, 14, "尺寸调整模式");

		ATTR(Title_LabelEx, 7, "标题"); ATTR(Align_LabelEx, 8, "对齐方式");
		ATTR(BackColor_LabelEx, 9, "背景色"); ATTR(Font_LabelEx, 10, "字体");
		ATTR(FontColor_LabelEx, 11, "字体色");

		ATTR(Skin_EditboxEx, 7, "皮肤"); ATTR(Content_EditboxEx, 8, "内容");
		ATTR(ItemAlign_EditboxEx, 9, "对齐方式"); ATTR(InputMode_EditboxEx, 10, "输入模式");
		ATTR(MaxLen_EditboxEx, 11, "最大允许长度"); ATTR(PwdSub_EditboxEx, 12, "密码掩盖符");
		ATTR(CursorColor_EditboxEx, 13, "光标色"); ATTR(Font_EditboxEx, 14, "字体");
		ATTR(FontColor_EditboxEx, 15, "字体色"); ATTR(SelectFontColor_EditboxEx, 16, "选中字体色");
		ATTR(SelectBackColor_EditboxEx, 17, "选中背景色"); ATTR(LeftReservation_EditboxEx, 18, "左边预留");
		ATTR(RightReservation_EditboxEx, 19, "右边预留"); ATTR(MultiLine_EditboxEx, 20, "允许多行");
		ATTR(AutoLine_EditboxEx, 21, "自动换行"); ATTR(ScrollBarMode_EditboxEx, 22, "滚动条模式");

		ATTR(Skin_ButtonEx, 7, "皮肤"); ATTR(Title_ButtonEx, 8, "标题");
		ATTR(Font_ButtonEx, 9, "字体"); ATTR(FontColor_ButtonEx, 10, "字体色");

		ATTR(Skin_PictureBoxEx, 7, "皮肤"); ATTR(Image_PictureBoxEx, 8, "图片");
		ATTR(MapMode_PictureBoxEx, 9, "底图模式"); ATTR(Angle_PictureBoxEx, 10, "圆角度");
		ATTR(PlayAnimation_PictureBoxEx, 11, "播放动画"); ATTR(AllFrame_PictureBoxEx, 12, "总帧数");
		ATTR(CurrentFrame_PictureBoxEx, 13, "当前帧");

		ATTR(Skin_MinutesboxEx, 7, "皮肤"); ATTR(Icon_MinutesboxEx, 8, "图标");
		ATTR(IconWidth_MinutesboxEx, 9, "图标宽度"); ATTR(IconHeight_MinutesboxEx, 10, "图标高度");
		ATTR(Title_MinutesboxEx, 11, "标题"); ATTR(Align_MinutesboxEx, 12, "标题对齐方式");
		ATTR(Font_MinutesboxEx, 13, "字体"); ATTR(FontColor_MinutesboxEx, 14, "字体色");

		ATTR(Skin_RadiobuttonEx, 7, "皮肤"); ATTR(Select_RadiobuttonEx, 8, "选中");
		ATTR(Title_RadiobuttonEx, 9, "标题"); ATTR(Font_RadiobuttonEx, 10, "字体");
		ATTR(FontColor_RadiobuttonEx, 11, "字体色");

		ATTR(Skin_ChoiceboxEx, 7, "皮肤"); ATTR(Select_ChoiceboxEx, 8, "选中");
		ATTR(Title_ChoiceboxEx, 9, "标题"); ATTR(Font_ChoiceboxEx, 10, "字体");
		ATTR(FontColor_ChoiceboxEx, 11, "字体色");

		ATTR(Skin_SlideButtonEx, 7, "皮肤"); ATTR(Select_SlideButtonEx, 8, "选中");

		ATTR(Skin_ProgressbarEx, 7, "皮肤"); ATTR(Pos_ProgressbarEx, 8, "位置");
		ATTR(MinPos_ProgressbarEx, 9, "最小位置"); ATTR(MaxPos_ProgressbarEx, 10, "最大位置");
		ATTR(Style_ProgressbarEx, 11, "进度条样式"); ATTR(Direction_ProgressbarEx, 12, "进度条方向");

		ATTR(Skin_SliderbarEx, 7, "皮肤"); ATTR(Pos_SliderbarEx, 8, "位置");
		ATTR(MinPos_SliderbarEx, 10, "最小位置"); ATTR(MaxPos_SliderbarEx, 11, "最大位置");
		ATTR(ClickStep_SliderbarEx, 12, "点击步长"); ATTR(DragTrace_SliderbarEx, 14, "拖动跟踪");
		ATTR(Direction_SliderbarEx, 15, "滑块条方向");

		ATTR(Skin_ScrollbarEx, 7, "皮肤"); ATTR(Pos_ScrollbarEx, 8, "位置");
		ATTR(MinPos_ScrollbarEx, 9, "最小位置"); ATTR(MaxPos_ScrollbarEx, 10, "最大位置");
		ATTR(BarSize_ScrollbarEx, 11, "滚动条长"); ATTR(ButtonStep_ScrollbarEx, 12, "按钮步长");
		ATTR(ClickStep_ScrollbarEx, 13, "点击步长"); ATTR(Direction_ScrollbarEx, 16, "滚动条方向");

		ATTR(Skin_ComboboxEx, 7, "皮肤"); ATTR(Content_ComboboxEx, 8, "内容");
		ATTR(Align_ComboboxEx, 9, "对齐方式");  ATTR(CursorColor_ComboboxEx, 13, "光标色");
		ATTR(Font_ComboboxEx, 14, "字体"); ATTR(FontColor_ComboboxEx, 15, "字体色");
		ATTR(SelectFontColor_ComboboxEx, 16, "选中字体色"); ATTR(SelectBackColor_ComboboxEx, 17, "选中背景色");
		ATTR(LeftReservation_ComboboxEx, 18, "左边预留"); ATTR(RightReservation_ComboboxEx, 19, "右边预留");
		ATTR(ListWidth_ComboboxEx, 27, "列表宽度"); ATTR(ListHeight_ComboboxEx, 28, "列表高度");
		ATTR(CurrentItem_ComboboxEx, 29, "当前选中项"); ATTR(IconWidth_ComboboxEx, 30, "图标宽度");
		ATTR(IconHeight_ComboboxEx, 31, "图标高度"); ATTR(ListFont_ComboboxEx, 32, "列表字体");
		ATTR(AlternateColor_ComboboxEx, 33, "隔行换色"); ATTR(ListTransparency_ComboboxEx, 35, "列表透明度");

		ATTR(Skin_SuperbuttonEx, 7, "皮肤"); ATTR(Icon_SuperbuttonEx, 9, "图标");
		ATTR(IconWidth_SuperbuttonEx, 10, "图标宽度"); ATTR(IconHeight_SuperbuttonEx, 11, "图标高度");
		ATTR(IconUp_SuperbuttonEx, 12, "图标居上"); ATTR(Title_SuperbuttonEx, 13, "标题");
		ATTR(Font_SuperbuttonEx, 14, "字体"); ATTR(FontColor_SuperbuttonEx, 15, "字体色");

		ATTR(Skin_ListboxEx, 7, "皮肤"); ATTR(CurrentItem_ListboxEx, 8, "当前选中项");
		ATTR(IconWidth_ListboxEx, 9, "图标宽度"); ATTR(IconHeight_ListboxEx, 10, "图标高度");
		ATTR(Font_ListboxEx, 11, "字体"); ATTR(AlternateColor_ListboxEx, 12, "隔行换色");
		ATTR(ScrollBarMode_ListboxEx, 13, "滚动条模式");

		ATTR(Skin_IcoListboxEx, 7, "皮肤"); ATTR(CurrentItem_IcoListboxEx, 8, "当前选中项");
		ATTR(ItemWidth_IcoListboxEx, 9, "项目宽度"); ATTR(ItemHeight_IcoListboxEx, 10, "项目高度");
		ATTR(HSpace_IcoListboxEx, 11, "横向间距"); ATTR(VSpace_IcoListboxEx, 12, "纵向间距");
		ATTR(IconWidth_IcoListboxEx, 13, "图标宽度"); ATTR(IconHeight_IcoListboxEx, 14, "图标高度");
		ATTR(Font_IcoListboxEx, 15, "字体"); ATTR(IconUp_IcoListboxEx, 17, "图标居上");
		ATTR(ScrollBarMode_IcoListboxEx, 18, "滚动条模式");

		ATTR(Skin_SuperListboxEx, 7, "皮肤"); ATTR(CurrentItem_SuperListboxEx, 8, "当前选中项");
		ATTR(HeadHeight_SuperListboxEx, 9, "表头高度"); ATTR(HeadMode_SuperListboxEx, 10, "表头模式");
		ATTR(AlternateColor_SuperListboxEx, 11, "隔行换色"); ATTR(LineMode_SuperListboxEx, 13, "表格线模式");
		ATTR(ScrollBarMode_SuperListboxEx, 14, "滚动条模式");

		ATTR(Skin_SelectthefolderEx, 7, "皮肤"); ATTR(CurrentItem_SelectthefolderEx, 8, "当前选中项");
		ATTR(ItemHeight_SelectthefolderEx, 9, "项目高度"); ATTR(TabDirection_SelectthefolderEx, 10, "子夹头方向");
		ATTR(Space_SelectthefolderEx, 11, "项目间距"); ATTR(IconWidth_SelectthefolderEx, 14, "图标宽度");
		ATTR(IconHeight_SelectthefolderEx, 15, "图标高度"); ATTR(Font_SelectthefolderEx, 16, "字体");

		ATTR(Skin_CalendarBoxEx, 7, "皮肤"); ATTR(CurrentDate_CalendarBoxEx, 10, "当前日期");
		ATTR(TitleFont_CalendarBoxEx, 11, "标题字体"); ATTR(WeekFont_CalendarBoxEx, 12, "星期字体");
		ATTR(DayFont_CalendarBoxEx, 13, "日期字体"); ATTR(TitleFontColor_CalendarBoxEx, 15, "标题字体色");
		ATTR(WeekFontColor_CalendarBoxEx, 16, "星期字体色"); ATTR(WeekendFontColor_CalendarBoxEx, 17, "双休星期字体色");
		ATTR(DayFontColor_CalendarBoxEx, 18, "日期字体色"); ATTR(WeekendDayFontColor_CalendarBoxEx, 19, "双休日期字体色");
		ATTR(OtherMonthFontColor_CalendarBoxEx, 20, "非本月字体色"); ATTR(OnlyThisMonth_CalendarBoxEx, 22, "只显示本月");
		ATTR(TitleHeight_CalendarBoxEx, 24, "标题高度"); ATTR(WeekHeight_CalendarBoxEx, 25, "星期高度");

		ATTR(Skin_ColorPickEx, 7, "皮肤"); ATTR(Font_ColorPickEx, 8, "字体");
		ATTR(FontColor_ColorPickEx, 9, "字体色"); ATTR(CurrentColor_ColorPickEx, 10, "当前色");
		ATTR(DragTrace_ColorPickEx, 11, "拖拽跟踪"); ATTR(useRGB_ColorPickEx, 12, "RGB色");
		ATTR(RegulatorHeight_ColorPickEx, 15, "调节器高度");

		ATTR(BackColor_DrawPanelEx, 7, "背景色"); ATTR(BroderColor_DrawPanelEx, 8, "边框色");

		CON_EX_END(__Private)

		// 组件类型
		CON_EX_BEGIN(ControlType)
		ATTR(Dialog, 700, "对话框"); ATTR(MsgBox, 750, "信息框");
		ATTR(InputBox, 760, "输入框"); ATTR(Menu, 800, "菜单");
		ATTR(DragList, 900, "下拉列表"); ATTR(Window, 1000, "窗口");
		ATTR(Filter, 1100, "滤镜"); ATTR(Group, 1200, "分组框");
		ATTR(Selector, 1300, "选择夹"); ATTR(Picture, 1400, "图片框");
		ATTR(Label, 1500, "标签"); ATTR(Button, 1600, "按钮");
		ATTR(PictureButton, 1700, "图片按钮"); ATTR(IconButton, 1800, "图标按钮");
		ATTR(UtilButton, 1900, "多功能按钮"); ATTR(Radio, 2000, "单选框");
		ATTR(Choice, 2100, "复选框"); ATTR(Progress, 2200, "进度条");
		ATTR(Slider, 2300, "滑块条"); ATTR(Scroll, 2400, "滚动条");
		ATTR(Edit, 2500, "编辑框"); ATTR(Combo, 2600, "组合框");
		ATTR(ToolBar, 2700, "工具条"); ATTR(List, 2800, "列表框");
		ATTR(IconList, 2900, "图标列表框"); ATTR(SuperList, 3000, "超级列表框");
		ATTR(TreeList, 3100, "树型框"); ATTR(Browser, 3200, "浏览器");
		ATTR(Calendar, 3300, "日历"); ATTR(ColorPick, 3400, "选色板");
		ATTR(MultiEdit, 3500, "富文本框"); ATTR(DIY, 3600, "自绘");
		ATTR(AnimationButton, 3700, "动画按钮"); ATTR(Table, 3800, "表格");
		ATTR(Switch, 3900, "开关"); ATTR(PieDiagram, 4000, "饼状图");
		ATTR(BarDiagram, 4100, "柱状图"); ATTR(ArcDiagram, 4200, "曲线图");
		ATTR(CandleDiagram, 4300, "烛线图"); ATTR(Draw, 4400, "画板");
		CON_EX_END(ControlType)

		// 键盘消息类型
		CON_EX_BEGIN(KeyType)
		ATTR(Up, 256, "键按下"); ATTR(Down, 257, "键弹起");
		CON_EX_END(KeyType)

		// 控制钮(支持位或)
		CON_EX_BEGIN(ControlButton)
		ATTR(Null, 0, "无控制钮"); ATTR(Min, 1, "最小化");
		ATTR(Max, 2, "最大化"); ATTR(Min_Max, 3, "最小化最大化");
		ATTR(Close, 4, "关闭"); ATTR(Min_Close, 5, "最小化关闭");
		ATTR(Max_Close, 6, "最大化关闭"); ATTR(Min_Max_Close, 7, "最小化最大化关闭");
		CON_EX_END(ControlButton)

		// 穿透模式
		CON_EX_BEGIN(PenetrateMode)
		ATTR(Disabled, 0, "禁止穿透"); ATTR(All, 1, "全部穿透");
		ATTR(Transparent, 2, "透明穿透");
		CON_EX_END(PenetrateMode)

		// 拖动模式(支持位或)
		CON_EX_BEGIN(DragMode)
		ATTR(Disabled, 0, "不可拖动"); ATTR(Title, 1, "标题栏拖动");
		ATTR(Client, 2, "客户区拖动"); ATTR(Rectangle, 4, "外形区拖动");
		CON_EX_END(DragMode)

		// 对齐模式
		// Start左/上, Center居中, End右/下, 第一个是横向, 第二个是纵向, Mul多行, Vec纵向
		CON_EX_BEGIN(Align)
#define ALIGN_BASE(h, v) constexpr static Attr h##_##v
#define ALIGNN(h, v, value) ALIGN_BASE(h, v) = value
#define ALIGNM(h, v, value) ALIGN_BASE(h, v)##_Mul = value
#define ALIGNV(h, v, value) ALIGN_BASE(h, v)##_Vec = value
#define ALIGNMV(h, v, value) ALIGN_BASE(h, v)##_Mul_Vec = value
#define ALIGN(f, i) \
f(Start, Start, i * 9 + 0); f(Start, Center, i * 9 + 1); f(Start, End, i * 9 + 2); \
f(Center, Start, i * 9 + 3); f(Center, Center, i * 9 + 4); f(Center, End, i * 9 + 5); \
f(End, Start, i * 9 + 6); f(End, Center, i * 9 + 7); f(End, End, i * 9 + 8)
		ALIGN(ALIGNM, 0);
		ALIGN(ALIGNN, 1);
		ALIGN(ALIGNMV, 2);
		ALIGN(ALIGNV, 3);
#undef ALIGN_BASE
#undef ALIGNN
#undef ALIGNM
#undef ALIGNV
#undef ALIGNMV
#undef ALIGN
		CON_EX_END(Align)

		// 输入模式(支持位或)
		CON_EX_BEGIN(InputMode)
		ATTR(Normal, 0x00000, "普通"); ATTR(Disabled, 0x00001, "禁止输入");
		ATTR(Password, 0x00002, "密码"); ATTR(NoInputMethod, 0x00004, "禁止输入法");
		ATTR(NoMenu, 0x00008, "禁止菜单"); ATTR(NoCtrlA, 0x00010, "禁止Ctrl+A");
		ATTR(NoCtrlZ, 0x00020, "禁止Ctrl+Z"); ATTR(NoCtrlY, 0x00040, "禁止Ctrl+Y");
		ATTR(NoCtrlC, 0x00080, "禁止Ctrl+C"); ATTR(NoCtrlX, 0x00100, "禁止Ctrl+X");
		ATTR(NoCtrlV, 0x00200, "禁止Ctrl+V"); ATTR(NoLowerLetter, 0x00400, "禁止小写字母");
		ATTR(NoUpperLetter, 0x00800, "禁止大写字母"); ATTR(NoNumber, 0x01000, "禁止数字");
		ATTR(OnlyLetterNumber, 0x02000, "仅字母数字"); ATTR(OnlyASCII, 0x04000, "仅ASCII字符");
		ATTR(KeepSelected, 0x08000, "保持被选中"); ATTR(BeginCursorTail, 0x10000, "初始光标置尾部");
		ATTR(SetContentCursorTail, 0x20000, "改变内容时光标置尾部"); ATTR(OpenList, 0x40000, "编辑区弹出菜单");
		CON_EX_END(InputMode)

		// 进度条样式
		CON_EX_BEGIN(ProgressStyle)
		ATTR(Bar, 0, "条状");
		ATTR(Circle_Clock, 1, "顺时针圆形");
		ATTR(Circle_AntiClock, 2, "逆时针圆形");
		CON_EX_END(ProgressStyle)

		// 进度条方向
		CON_EX_BEGIN(ProgressDirection)
		ATTR(Right, 0, "从左至右"); ATTR(Left, 1, "从右至左");
		ATTR(Down, 2, "从上至下"); ATTR(Up, 3, "从下至上");
		CON_EX_END(ProgressDirection)

		// 滚动条模式
		CON_EX_BEGIN(ScrollBarMode)
		ATTR(HorVec, 0, "条形从左至右");
		ATTR(NoVec, 1, "条形从左至右"); ATTR(NoHor, 16, "条形从左至右");
		ATTR(ShowVec, 2, "条形从左至右"); ATTR(ShowHor, 32, "条形从左至右");
		ATTR(HangVec, 4, "条形从左至右"); ATTR(HangHor, 64, "条形从左至右");
		ATTR(HotVec, 8, "条形从左至右"); ATTR(HotHor, 128, "条形从左至右");
		CON_EX_END(ScrollBarMode)

		// 底图模式
		CON_EX_BEGIN(MapMode)
		ATTR(UpperLeft, 0, "左上"); ATTR(Zoom, 1, "缩放");
		ATTR(Center, 2, "居中"); ATTR(Tile, 3, "平铺");
		CON_EX_END(MapMode)

		// 表头模式
		CON_EX_BEGIN(HeadMode)
		ATTR(NoEventNoDrag, 0, "不响应事件不响应拖放");
		ATTR(Event, 1, "响应事件"); ATTR(Drag, 2, "响应拖放");
		CON_EX_END(HeadMode)

		// 表格线模式(支持位或)
		CON_EX_BEGIN(LineMode)
		ATTR(Null, 0, "无表格线"); ATTR(Hor, 1, "横向表格线");
		ATTR(Vec, 2, "纵向表格线"); ATTR(Round, 4, "外围表格线");
		ATTR(HeadHor, 8, "表头横向表格线"); ATTR(HeadVec, 16, "表头纵向表格线");
		CON_EX_END(LineMode)

		// 项目对齐方式
		CON_EX_BEGIN(ItemAlign)
		ATTR(Left, 0, "居左"); ATTR(Center, 1, "居中"); ATTR(Right, 2, "居右");
		CON_EX_END(ItemAlign)

		// 列表事件来源
		CON_EX_BEGIN(ListEventSource)
		ATTR(Head, 1, "表头"); ATTR(Item, 2, "表项"); ATTR(Column, 3, "表列");
		CON_EX_END(ListEventSource)

		// 子夹头方向
		CON_EX_BEGIN(TabDirection)
		ATTR(Null, -1, "无子夹头");
		ATTR(TopHor, 0, "上横向"); ATTR(RightHor, 1, "右横向");
		ATTR(BottomHor, 2, "下横向"); ATTR(LeftHor, 3, "左横向");
		ATTR(TopVec, 8, "上纵向"); ATTR(RightVec, 9, "右纵向");
		ATTR(BottomVec, 10, "下纵向"); ATTR(LeftVec, 11, "左纵向");
		CON_EX_END(TabDirection)

		// 画笔类型
		CON_EX_BEGIN(LineStyle)
		ATTR(Solid, 0, "实线"); ATTR(Dash, 1, "划线");
		ATTR(Dot, 2, "点线"); ATTR(DashDot, 3, "点划线");
		ATTR(DashDotDot, 4, "双点划线");
		CON_EX_END(LineStyle)

		// 画刷类型
		CON_EX_BEGIN(BrushStyle)
		ATTR(Null, 0, "无画刷");
		ATTR(Solid, 100, "纯色"); ATTR(LRChange, 200, "左至右渐变");
		ATTR(TBChange, 201, "上至下渐变"); ATTR(LTRBChange, 202, "左上至右下渐变");
		ATTR(RTLBChange, 203, "右上至左下渐变"); ATTR(ShadowHor, 300, "阴影水平线");
		ATTR(ShadowVec, 301, "阴影垂直线"); ATTR(ShadowLLine, 302, "阴影左斜线");
		ATTR(ShadowRLine, 303, "阴影右斜线"); ATTR(ShadowCross1, 304, "阴影十字线");
		ATTR(ShadowCross2, 305, "阴影交叉线"); ATTR(Shadow5, 306, "阴影5%");
		ATTR(Shadow10, 307, "阴影10%"); ATTR(Shadow20, 308, "阴影20%");
		ATTR(Shadow25, 309, "阴影25%"); ATTR(Shadow30, 310, "阴影30%");
		ATTR(Shadow40, 311, "阴影40%"); ATTR(Shadow50, 312, "阴影50%");
		ATTR(Shadow60, 313, "阴影60%"); ATTR(Shadow70, 314, "阴影70%");
		ATTR(Shadow75, 315, "阴影75%"); ATTR(Shadow80, 316, "阴影80%");
		ATTR(Shadow90, 317, "阴影90%"); ATTR(ShadowTBLine, 318, "阴影细向下对角线");
		ATTR(ShadowTULine, 319, "阴影细向上对角线"); ATTR(ShadowRBLine, 320, "阴影粗向下对角线");
		ATTR(ShadowRULine, 321, "阴影粗向上对角线"); ATTR(ShadowWBLine, 322, "阴影宽向下对角线");
		ATTR(ShadowWULine, 323, "阴影宽向上对角线"); ATTR(ShadowTVec, 324, "阴影细垂直线");
		ATTR(ShadowTHor, 325, "阴影细水平线"); ATTR(ShadowCVec, 326, "阴影密垂直线");
		ATTR(ShadowCHor, 327, "阴影密水平线"); ATTR(ShadowRVec, 328, "阴影粗垂直线");
		ATTR(ShadowRHor, 329, "阴影粗水平线"); ATTR(ShadowRILine, 330, "阴影右斜虚线");
		ATTR(ShadowLILine, 331, "阴影左斜虚线"); ATTR(ShadowHorILine, 332, "阴影水平虚线");
		ATTR(ShadowVecILine, 333, "阴影垂直虚线"); ATTR(ShadowSColor, 334, "阴影小五彩纸屑");
		ATTR(ShadowBColor, 335, "阴影大五彩纸屑"); ATTR(ShadowCurve, 336, "阴影曲线");
		ATTR(ShadowWave, 337, "阴影波浪线"); ATTR(ShadowCrossBrick, 338, "阴影对角砖块");
		ATTR(ShadowHorBrick, 339, "阴影水平砖块"); ATTR(ShadowWeave, 340, "阴影编织");
		ATTR(ShadowPlaid, 341, "阴影花格子"); ATTR(DashTurf, 342, "阴影草皮");
		ATTR(ShadowCrossDot1, 343, "阴影十字点线"); ATTR(ShadowCrossDot2, 344, "阴影交叉点线");
		ATTR(ShadowTile, 345, "阴影瓦片"); ATTR(ShadowGrid, 346, "阴影网格");
		ATTR(ShadowBall, 347, "阴影球形"); ATTR(ShadowSGrid, 348, "阴影小网格");
		ATTR(ShadowSBoard, 349, "阴影小棋盘"); ATTR(ShadowBBoard, 350, "阴影大棋盘");
		ATTR(ShadowLineDiamond, 351, "阴影边线金刚石"); ATTR(ShadowDiamond, 352, "阴影金刚石");
		CON_EX_END(BrushStyle)

		// 平滑模式
		CON_EX_BEGIN(SmoothMode)
		ATTR(Default, 0, "默认"); ATTR(HighPerformance, 1, "高性能");
		ATTR(HighQuality, 2, "高质量"); ATTR(NoAntiSawTooth, 3, "无抗锯齿");
		ATTR(AntiSawTooth, 4, "抗锯齿");
		CON_EX_END(SmoothMode)

		// 算法模式
		CON_EX_BEGIN(AlgorithmMode)
		ATTR(Default, 0, "默认"); ATTR(LowQuality, 1, "低质量");
		ATTR(HighQuality, 2, "高质量"); ATTR(DoubleLinear, 3, "双线性");
		ATTR(ThreeCase, 4, "三次样条"); ATTR(Near, 5, "邻近");
		ATTR(HighQualityDoubleLinear, 6, "高质量双线性"); ATTR(HighQualityThreeCase, 7, "高质量三次样条");
		CON_EX_END(AlgorithmMode)

		// 像素偏移模式
		CON_EX_BEGIN(OffsetMode)
		ATTR(Default, 0, "默认"); ATTR(HighPerformance, 1, "高性能");
		ATTR(HighQuality, 2, "高质量"); ATTR(NoOffset, 3, "无偏移");
		ATTR(Half, 4, "一半");
		CON_EX_END(OffsetMode)
	};
}

#undef ATTR
#undef CON_EX_BEGIN
#undef CON_EX_END