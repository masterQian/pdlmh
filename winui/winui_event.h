#pragma once
#include "winui_def.h"

#define CON_EX_BEGIN(name) class name final { \
name() = delete; \
public:
#define CON_EX_END(name) };

#define EVENT(name, value, comment) constexpr static Event name = value

namespace winui {
	// 事件
	class Events final {
		Events() = delete;
	public:
		EVENT(User, 5201314, "用户自定义消息");

		CON_EX_BEGIN(Control)
		EVENT(LClick, 660, "控件被左键单击(坐标x,坐标y,,)");
		EVENT(RClick, 661, "控件被右键单击(坐标x,坐标y,,)");
		EVENT(LDown, 662, "控件被左键按下(坐标x,坐标y,,)");
		EVENT(RDown, 663, "控件被右键按下(坐标x,坐标y,,)");
		EVENT(LUp, 664, "控件被左键弹起(坐标x,坐标y,,)");
		EVENT(RUp, 665, "控件被右键弹起(坐标x,坐标y,,)");
		EVENT(LDClick, 666, "控件被左键双击(坐标x,坐标y,,)");
		EVENT(RDClick, 667, "控件被右键双击(坐标x,坐标y,,)");
		EVENT(MouseMove, 668, "鼠标移动(坐标x,坐标y,,)");
		EVENT(MouseTrack, 669, "鼠标进入离开(是否进入,,,)");
		EVENT(WheelEvent, 670, "滚轮事件(,,滚动距离,)");
		EVENT(KeyEvent, 671, "键盘事件(事件类型,事件窗口,键代码,)");
		EVENT(CharInput, 672, "字符输入消息(,,,)");
		EVENT(Focus, 673, "焦点信息(焦点状态,因果组件,事件来源,)");
		EVENT(MButtonUp, 1001, "滚轮弹起()");
		EVENT(MButtonDClick, 1002, "滚轮双击()");
		EVENT(MButtonDown, 1003, "滚轮按下()");
		EVENT(SetCursor, 1004, "设置鼠标指针()");
		EVENT(GetMinMaxInfo, 1005, "尺寸控制()");
		EVENT(PositionChange, 1006, "位置改变(左边,顶边,宽度,高度)");
		EVENT(SizeChange, 1007, "尺寸改变(左边,顶边,宽度,高度)");
		EVENT(RequestRepaint, 1008, "请求重画(绘画DC,,,)");
		EVENT(Repaint, 1009, "重画(,绘画DC,,)");
		EVENT(VisualChange, 1010, "可视改变(,,,)");
		EVENT(DisabledChange, 1011, "禁止改变(,,,)");
		EVENT(SetParent, 1014, "控件置父(,,,)");
		EVENT(Create, 7888, "控件创建(父控件id,,,)");
		EVENT(Destroy, 7889, "控件销毁(父控件id,,,)");
		EVENT(Release, 7890, "资源释放(父控件id,win窗口句柄,子控件名称,)");
		CON_EX_END(Control)

		CON_EX_BEGIN(Window)
		EVENT(Create, 0x0001, "窗口创建完毕(,,,)");
		EVENT(CreateRePaint, 10010, "窗口创建完毕且允许重绘(,,,)");
		EVENT(Destroy, 0x0002, "窗口即将销毁(,,,)");
		EVENT(LastMessage, 0x0082, "最后的讯息(,,,)");
		EVENT(Close, 0x0010, "窗口即将关闭(,,,)");
		EVENT(Clock, 0x0113, "时钟事件(时钟标识,,,)");
		EVENT(HotKey, 0x0312, "热键事件(热键标识,,,)");
		EVENT(Tray, 12313, "托盘事件(,子事件,,)");
		EVENT(Drag, 0x0233, "拖放事件(文件数,文件名数组,,)");
		CON_EX_END(Window)

		CON_EX_BEGIN(Edit)
		EVENT(ContentChange, 659, "内容被改变(,,,)");
		CON_EX_END(Edit)

		CON_EX_BEGIN(Switch)
		EVENT(SelectChange, 659, "状态被改变(新状态,,,)");
		CON_EX_END(Switch)

		CON_EX_BEGIN(Slider)
		EVENT(PositionChange, 659, "位置被改变(新位置,,,)");
		CON_EX_END(Slider)

		CON_EX_BEGIN(Scroll)
		EVENT(PositionChange, 659, "位置被改变(新位置,,,)");
		CON_EX_END(Scroll)

		CON_EX_BEGIN(Combo)
		EVENT(ItemSelect, 659, "项目被选择(项目索引,,,)");
		CON_EX_END(Combo)

		CON_EX_BEGIN(List)
		EVENT(ItemLCLick, 650, "项目被左键单击(项目索引,,,)");
		EVENT(ItemRCLick, 651, "项目被右键单击(项目索引,,,)");
		EVENT(ItemLUp, 652, "项目被左键弹起(项目索引,,,)");
		EVENT(ItemRUp, 653, "项目被右键弹起(项目索引,,,)");
		EVENT(ItemLDown, 654, "项目被左键按下(项目索引,,,)");
		EVENT(ItemRDown, 655, "项目被右键按下(项目索引,,,)");
		EVENT(ItemLDCLick, 656, "项目被左键双击(项目索引,,,)");
		EVENT(ItemRDCLick, 657, "项目被左键双击(项目索引,,,)");
		EVENT(ItemMouseIn, 658, "项目鼠标进入(项目索引,,,)");
		EVENT(ItemMouseOut, 659, "项目鼠标离开(项目索引,,,)");
		CON_EX_END(List)

		CON_EX_BEGIN(IconList)
		EVENT(ItemLCLick, 650, "项目被左键单击(项目索引,,,)");
		EVENT(ItemRCLick, 651, "项目被右键单击(项目索引,,,)");
		EVENT(ItemLUp, 652, "项目被左键弹起(项目索引,,,)");
		EVENT(ItemRUp, 653, "项目被右键弹起(项目索引,,,)");
		EVENT(ItemLDown, 654, "项目被左键按下(项目索引,,,)");
		EVENT(ItemRDown, 655, "项目被右键按下(项目索引,,,)");
		EVENT(ItemLDCLick, 656, "项目被左键双击(项目索引,,,)");
		EVENT(ItemRDCLick, 657, "项目被左键双击(项目索引,,,)");
		EVENT(ItemMouseIn, 658, "项目鼠标进入(项目索引,,,)");
		EVENT(ItemMouseOut, 659, "项目鼠标离开(项目索引,,,)");
		CON_EX_END(IconList)

		CON_EX_BEGIN(SuperList)
		EVENT(ItemLCLick, 649, "项目被左键单击(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemRCLick, 650, "项目被右键单击(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemLUp, 651, "项目被左键弹起(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemRUp, 652, "项目被右键弹起(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemLDown, 653, "项目被左键按下(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemRDown, 654, "项目被右键按下(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemLDCLick, 655, "项目被左键双击(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemRDCLick, 656, "项目被左键双击(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemMouseIn, 657, "项目鼠标进入(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemMouseOut, 658, "项目鼠标离开(项目索引,列索引,元素索引,事件来源)");
		EVENT(ItemSizeChange, 659, "列宽被改变(项目索引,列索引,调整类型,新尺寸)");
		CON_EX_END(SuperList)

		CON_EX_BEGIN(Selector)
		EVENT(ItemWillChange, 648, "项目即将被改变(原项目索引,新项目索引,,)");
		EVENT(ItemHasChange, 649, "项目已被改变(新项目索引,,,)");
		EVENT(ItemLCLick, 650, "项目被左键单击(项目索引,,,)");
		EVENT(ItemRCLick, 651, "项目被右键单击(项目索引,,,)");
		EVENT(ItemLUp, 652, "项目被左键弹起(项目索引,,,)");
		EVENT(ItemRUp, 653, "项目被右键弹起(项目索引,,,)");
		EVENT(ItemLDown, 654, "项目被左键按下(项目索引,,,)");
		EVENT(ItemRDown, 655, "项目被右键按下(项目索引,,,)");
		EVENT(ItemLDCLick, 656, "项目被左键双击(项目索引,,,)");
		EVENT(ItemRDCLick, 657, "项目被左键双击(项目索引,,,)");
		EVENT(ItemMouseIn, 658, "项目鼠标进入(项目索引,,,)");
		EVENT(ItemMouseOut, 659, "项目鼠标离开(项目索引,,,)");
		CON_EX_END(Selector)

		CON_EX_BEGIN(Calendar)
		EVENT(ItemLCLick, 650, "项目被左键单击(项目索引,,,)");
		EVENT(ItemRCLick, 651, "项目被右键单击(项目索引,,,)");
		EVENT(ItemLUp, 652, "项目被左键弹起(项目索引,,,)");
		EVENT(ItemRUp, 653, "项目被右键弹起(项目索引,,,)");
		EVENT(ItemLDown, 654, "项目被左键按下(项目索引,,,)");
		EVENT(ItemRDown, 655, "项目被右键按下(项目索引,,,)");
		EVENT(ItemLDCLick, 656, "项目被左键双击(项目索引,,,)");
		EVENT(ItemRDCLick, 657, "项目被左键双击(项目索引,,,)");
		EVENT(ItemMouseIn, 658, "项目鼠标进入(项目索引,,,)");
		EVENT(ItemMouseOut, 659, "项目鼠标离开(项目索引,,,)");
		CON_EX_END(Calendar)

		CON_EX_BEGIN(ColorPick)
		EVENT(ColorChange, 659, "颜色被改变(颜色,,,)");
		CON_EX_END(ColorPick)

		CON_EX_BEGIN(Menu)
		EVENT(WillOpen, 646, "菜单将被打开(,消息)");
		EVENT(Open, 647, "菜单打开完毕(,消息)");
		EVENT(WillClose, 648, "菜单将被关闭(,消息)");
		EVENT(Close, 649, "菜单关闭完毕(,消息)");
		EVENT(ItemLCLick, 650, "项目被左键单击(项目,消息,标记)");
		EVENT(ItemRCLick, 651, "项目被右键单击(项目,消息,标记)");
		EVENT(ItemLUp, 652, "项目被左键弹起(项目,消息,标记)");
		EVENT(ItemRUp, 653, "项目被右键弹起(项目,消息,标记)");
		EVENT(ItemLDown, 654, "项目被左键按下(项目,消息,标记)");
		EVENT(ItemRDown, 655, "项目被右键按下(项目,消息,标记)");
		EVENT(ItemLDCLick, 656, "项目被左键双击(项目,消息,标记)");
		EVENT(ItemRDCLick, 657, "项目被左键双击(项目,消息,标记)");
		EVENT(ItemMouseIn, 658, "项目鼠标进入(项目,消息,标记)");
		EVENT(ItemMouseOut, 659, "项目鼠标离开(项目,消息,标记)");
		CON_EX_END(Menu)

		CON_EX_BEGIN(Tray)
		EVENT(MouseMove, 512, "鼠标移动(,,,)");
		EVENT(LDown, 513, "左键按下(,,,)");
		EVENT(LUp, 514, "左键弹起(,,,)");
		EVENT(LDClick, 515, "左键双击(,,,)");
		EVENT(RDown, 516, "右键按下(,,,)");
		EVENT(RUp, 517, "右键弹起(,,,)");
		EVENT(RDClick, 518, "右键双击(,,,)");
		EVENT(MDown, 519, "中键按下(,,,)");
		EVENT(MUp, 520, "中键弹起(,,,)");
		EVENT(MDClick, 521, "中键双击(,,,)");
		CON_EX_END(Tray)

		CON_EX_BEGIN(Gradient)
		EVENT(Begin, 1, "缓动开始前(缓动序号,缓动结果,缓动进度,附加数值)");
		EVENT(EffectBegin, 2, "计算开始前(缓动序号,缓动结果,缓动进度,附加数值)");
		EVENT(Result, 3, "缓动结果(缓动序号,缓动结果,缓动进度,附加数值)");
		EVENT(EffectEnd, 4, "计算结束后(缓动序号,缓动结果,缓动进度,附加数值)");
		EVENT(End, 5, "缓动结束后(缓动序号,缓动结果,缓动进度,附加数值)");
		CON_EX_END(Gradient)
#undef EVENT
	};
}

#undef EVENT
#undef CON_EX_BEGIN
#undef CON_EX_END