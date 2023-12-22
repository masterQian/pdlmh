#pragma once

#include "winui_lib.h"

namespace winui::api {
	// 内存相关
	inline PBin(__stdcall* CreateBinEx)(ConstMemory data, int length); // 申请内存
	inline void(__stdcall* DeleteBinEx)(PBin bin); // 释放内存

	// 位图相关
	inline PICO(__stdcall* LoadImageEx)(ConstMemory data, int mode, int width, int height, int angle, int lineColor, int lineWidth, int align); // 载入位图
	inline void(__stdcall* DestroyImageEx)(PICO ico); // 销毁位图
	inline int(__stdcall* GetImageAttributeEx)(PICO ico, int type); // 取位图属性
	inline PBin(__stdcall* GetImageData)(PICO ico); // 取位图数据

	// 结构体相关
	inline Struct(__stdcall* Create_StructEx)(); // 创建结构体
	inline int(__stdcall* InsertMember_StructEx)(Struct, int index, int num); // 插入成员
	inline void(__stdcall* SetMemberBool_StructEx)(Struct, int index, Bool value); // 置成员逻辑值
	inline void(__stdcall* SetMemberInt_StructEx)(Struct, int index, int value); // 置成员整数
	inline void(__stdcall* SetMemberFloat_StructEx)(Struct, int index, float value); // 置成员小数
	inline void(__stdcall* SetMemberDouble_StructEx)(Struct, int index, double value); // 置成员双精度小数
	inline void(__stdcall* SetMemberText_StructEx)(Struct, int index, PBin value); // 置成员文本
	inline void(__stdcall* SetMemberBin_StructEx)(Struct, int index, PBin data); // 置成员字节集
	inline void(__stdcall* Destroy_StructEx)(Struct); // 销毁结构体
	inline PBin(__stdcall* Pack_StructEx)(Struct); // 打包结构体

	// 皮肤相关
	inline PBin(__stdcall* RexcCreateSkinInfo)(); // 创建皮肤包
	inline Bool(__stdcall* RexcDisposeSkinInfo)(PBin skin); // 销毁皮肤包
	inline Bool(__stdcall* RexcUnSkinToSkinInfo)(PBin skin, PBin data); // 皮肤解包
	inline PBin(__stdcall* RexcPackSkinInfo)(PBin skin); // 皮肤打包

	// Win窗口
	inline HWND(__stdcall* Create_WindowBoxEx)(
		int mode, int location, HWND hParent,
		int x, int y, int width, int height,
		__WinCall wndProc, Bool visual, Bool disabled, int icon, PBin title,
		Bool alwaysTop, Bool taskBarShow, Bool escClose, PBin className,
		int classStyle, DWORD exStyle, DWORD style, Memory sign
		); // 创建Win窗口
	inline void(__stdcall* MessageLoop_WindowBoxEx)(HWND); // Win窗口消息循环
	inline void(__stdcall* Destroy_WindowBoxEx)(HWND); // 销毁Win窗口
	inline int(__stdcall* GetLeft_WindowBoxEx)(HWND); // Win窗口取左边
	inline void(__stdcall* SetLeft_WindowBoxEx)(HWND, int); // Win窗口置左边
	inline int(__stdcall* GetTop_WindowBoxEx)(HWND); // Win窗口取顶边
	inline void(__stdcall* SetTop_WindowBoxEx)(HWND, int); // Win窗口置顶边
	inline int(__stdcall* GetWidth_WindowBoxEx)(HWND); // Win窗口取宽度
	inline void(__stdcall* SetWidth_WindowBoxEx)(HWND, int); // Win窗口置宽度
	inline int(__stdcall* GetHeight_WindowBoxEx)(HWND); // Win窗口取高度
	inline void(__stdcall* SetHeight_WindowBoxEx)(HWND, int); // Win窗口置高度
	inline void(__stdcall* GetRect_WindowBoxEx)(HWND, int*, int*, int*, int*); // Win窗口取矩形
	inline void(__stdcall* SetRect_WindowBoxEx)(HWND, int, int, int, int); // Win窗口置矩形
	inline Memory(__stdcall* GetSign_WindowBoxEx)(HWND); // Win窗口取标记
	inline void(__stdcall* SetSign_WindowBoxEx)(HWND, Memory); // Win窗口取标记
	inline PBin(__stdcall* GetTitle_WindowBoxEx)(HWND); // Win窗口取标题
	inline void(__stdcall* SetNotifyIcon_WindowBoxEx)(HWND, PBin, PBin); // 置托盘图标
	inline void(__stdcall* EnableDragDrop_WindowBoxEx)(HWND); // 允许拖放
	inline void(__stdcall* CloseDragDrop_WindowBoxEx)(HWND); // 禁止拖放

	// 组件
	inline int(__stdcall* ControlGetLeft)(ID); // 组件取左边
	inline void(__stdcall* ControlSetLeft)(ID, int); // 组件置左边
	inline int(__stdcall* ControlGetTop)(ID); // 组件取顶边
	inline void(__stdcall* ControlSetTop)(ID, int); // 组件置顶边
	inline int(__stdcall* ControlGetWidth)(ID); // 组件取宽度
	inline void(__stdcall* ControlSetWidth)(ID, int); // 组件置宽度
	inline int(__stdcall* ControlGetHeight)(ID); // 组件取高度
	inline void(__stdcall* ControlSetHeight)(ID, int); // 组件置高度
	inline Bool(__stdcall* ControlGetVisual)(ID); // 组件取可视
	inline void(__stdcall* ControlSetVisual)(ID, Bool); // 组件置可视
	inline Bool(__stdcall* ControlGetDisabled)(ID); // 组件取禁止
	inline void(__stdcall* ControlSetDisabled)(ID, Bool); // 组件置禁止
	inline PBin(__stdcall* ControlGetCursor)(ID); // 组件取鼠标光标
	inline void(__stdcall* ControlSetCursor)(ID, PBin); // 组件置鼠标光标
	inline int(__stdcall* ControlGetPenetrate)(ID); // 组件取鼠标穿透
	inline void(__stdcall* ControlSetPenetrate)(ID, int); // 组件置鼠标穿透
	inline int(__stdcall* ControlGetTransparency)(ID); // 组件取透明度
	inline void(__stdcall* ControlSetTransparency)(ID, int); // 组件置透明度
	inline int(__stdcall* ControlGetFocusWeight)(ID); // 组件取焦点权重
	inline void(__stdcall* ControlSetFocusWeight)(ID, int); // 组件置焦点权重
	inline Bool(__stdcall* ControlGetFocusControl)(ID); // 组件取可聚焦
	inline void(__stdcall* ControlSetFocusControl)(ID, Bool); // 组件置可聚焦
	inline int(__stdcall* ControlGetcontrolType)(ID); // 组件取类型
	inline void(__stdcall* ControlSetcontrolType)(ID, int); // 组件置类型
	inline Memory (__stdcall* ControlGetsign)(ID); // 组件取标记
	inline void(__stdcall* ControlGetRect)(ID, int*, int*, int*, int*); // 组件取矩形
	inline void(__stdcall* ControlSetRect)(ID, int, int, int, int); // 组件置矩形
	inline HWND(__stdcall* ControlGetWindow)(ID); // 组件取Win窗口句柄
	inline void(__stdcall* ControlDestroy)(ID); // 销毁组件
	inline HDC(__stdcall* ControlGetDc)(ID); // 组件取DC
	inline Bool(__stdcall* ControlUpdateCache)(); // 组件更新缓存
	inline void(__stdcall* ControlRefreshWin)(ID); // 组件刷新Win窗口
	inline void(__stdcall* ControlAddRedrawRect)(ID, int, int, int, int); // 组件添加重画区
	inline void(__stdcall* ControlRedraw)(ID); // 组件请求重画
	inline int(__stdcall* ControlLockUpdate)(ID); // 组件禁止重画
	inline int(__stdcall* ControlUnlockUpdate)(ID); // 组件允许重画
	inline ID(__stdcall* ControlGetParentControl)(ID); // 取父组件
	inline Bool(__stdcall* ControlHaveChild)(ID); // 是否有子组件
	inline int(__stdcall* ControlGetChildCount)(ID, Bool); // 取子组件数
	inline Memory (__stdcall* ControlEnumerateChild)(ID, Bool); // 枚举子组件
	inline Result(__stdcall* ControlSendMessage)(ID, Event, Arg, Arg, Arg, Arg); // 组件发送消息
	inline Result(__stdcall* ControlSubmitTask)(ID, int, Task, int, int); // 组件提交任务

	// 窗口
	inline ID(__stdcall* CreateControl_WindowEx)(
		HWND hBase, HWND hParent, int x, int y, int width, int height,
		Call wndProc, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, PBin icon,
		PBin title, PBin font, ARGB fontColor, int layeredTransparency, int dragMode,
		int sizeMode, int maxMode, PBin controlButton, int controlButtonParam,
		PBin extraElement, PBin layout
		); // 创建窗口
	inline PBin(__stdcall* GetAttribute_WindowEx)(ID hwnd, int type); // 取窗口属性
	inline void(__stdcall* SetAttribute_WindowEx)(ID hwnd, int type, PBin attr); // 置窗口属性
	inline void(__stdcall* SetButtonVisual_WindowEx)(ID hwnd, int index, Bool show); // 置控制钮可视
	inline Bool(__stdcall* GetButtonVisual_WindowEx)(ID hwnd, int index); // 取控制钮可视

	// 标签
	inline ID(__stdcall* CreateControl_LabelEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin title, int align,
		ARGB backColor, PBin font, ARGB fontColor, int rotate, PBin extraElement, PBin layout
		); // 创建标签
	inline PBin(__stdcall* GetAttribute_LabelEx)(ID hwnd, int type); // 取标签属性
	inline void(__stdcall* SetAttribute_LabelEx)(ID hwnd, int type, PBin attr); // 置标签属性

	// 编辑框
	inline ID(__stdcall* CreateControl_EditboxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, PBin content,
		int align, int inputMode, int maxLen, PBin pwdSub, ARGB cursorColor, PBin font,
		ARGB fontColor, ARGB selectFontColor, ARGB selectColor, int leftReservation,
		int rightReservation, Bool multiline, Bool autoLine, int scrollBarMode,
		int menuItemWidth, int menuItemHeight, PBin menuFont, ARGB menuFontColor,
		ARGB menuDisabledFontColor, int menuTransparency, int menuLanguage,
		PBin extraElement, PBin layout
		); // 创建编辑框
	inline PBin(__stdcall* GetAttribute_EditboxEx)(ID hwnd, int type); // 取编辑框属性
	inline void(__stdcall* SetAttribute_EditboxEx)(ID hwnd, int type, PBin attr); // 置编辑框属性

	// 按钮
	inline ID(__stdcall* CreateControl_ButtonEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, PBin title,
		PBin font, ARGB fontColor, int animation, PBin extraElement, PBin layout
		); // 创建按钮
	inline PBin(__stdcall* GetAttribute_ButtonEx)(ID hwnd, int type); // 取按钮属性
	inline void(__stdcall* SetAttribute_ButtonEx)(ID hwnd, int type, PBin attr); // 置按钮属性

	// 图片框
	inline ID(__stdcall* CreateControl_PictureBoxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, PBin image,
		int mapMode, int angle, Bool playAnimation, int allFrame, int currentFrame,
		int rotate, PBin extraElement, PBin layout
		); // 创建图片框
	inline PBin(__stdcall* GetAttribute_PictureBoxEx)(ID hwnd, int type); // 取图片框属性
	inline void(__stdcall* SetAttribute_PictureBoxEx)(ID hwnd, int type, PBin attr); // 置图片框属性

	// 分组框
	inline ID(__stdcall* CreateControl_MinutesboxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height, Call callback,
		int* initAttr, Bool visual, Bool disabled, int transparency, int pierced,
		int focusWeight, PBin cursor, Memory sign, PBin skin, PBin icon, int iconWidth,
		int iconHeight, PBin title, int align, PBin font, ARGB fontColor,
		PBin extraElement, PBin layout
		); // 创建分组框
	inline PBin(__stdcall* GetAttribute_MinutesboxEx)(ID hwnd, int type); // 取分组框属性
	inline void(__stdcall* SetAttribute_MinutesboxEx)(ID hwnd, int type, PBin attr); // 置分组框属性

	// 单选框
	inline ID(__stdcall* CreateControl_RadiobuttonEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height, Call callback,
		int* initAttr, Bool visual, Bool disabled, int transparency, int pierced,
		int focusWeight, PBin cursor, Memory sign, PBin skin, Bool select, PBin title,
		PBin font, ARGB fontColor, int animation, PBin extraElement, PBin layout
		); // 创建单选框
	inline PBin(__stdcall* GetAttribute_RadiobuttonEx)(ID hwnd, int type); // 取单选框属性
	inline void(__stdcall* SetAttribute_RadiobuttonEx)(ID hwnd, int type, PBin attr); // 置单选框属性

	// 复选框
	inline ID(__stdcall* CreateControl_ChoiceboxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height, Call callback,
		int* initAttr, Bool visual, Bool disabled, int transparency, int pierced, int focusWeight,
		PBin cursor, Memory sign, PBin skin, Bool select, PBin title, PBin font, ARGB fontColor,
		int animation, int selectMode, Bool selectState, PBin extraElement, PBin layout
		); // 创建复选框
	inline PBin(__stdcall* GetAttribute_ChoiceboxEx)(ID hwnd, int type); // 取复选框属性
	inline void(__stdcall* SetAttribute_ChoiceboxEx)(ID hwnd, int type, PBin attr); // 置复选框属性

	// 开关
	inline ID(__stdcall* CreateControl_SlideButtonEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, Bool select,
		PBin extraElement, PBin layout
		); // 创建开关
	inline PBin(__stdcall* GetAttribute_SlideButtonEx)(ID hwnd, int type); // 取开关属性
	inline void(__stdcall* SetAttribute_SlideButtonEx)(ID hwnd, int type, PBin attr); // 置开关属性

	// 进度条
	inline ID(__stdcall* CreateControl_ProgressbarEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, int pos,
		int minPos, int maxPos, int style, int direction, PBin extraElement, PBin layout
		); // 创建进度条
	inline PBin(__stdcall* GetAttribute_ProgressbarEx)(ID hwnd, int type); // 取进度条属性
	inline void(__stdcall* SetAttribute_ProgressbarEx)(ID hwnd, int type, PBin attr); // 置进度条属性

	// 滑块条
	inline ID(__stdcall* CreateControl_SliderbarEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, int pos,
		int proPos, int minPos, int maxPos, int clickStep, int wheelStep,
		Bool dragTrace, int style, PBin extraElement, PBin layout
		); // 创建滑块条
	inline PBin(__stdcall* GetAttribute_SliderbarEx)(ID hwnd, int type); // 取滑块条属性
	inline void(__stdcall* SetAttribute_SliderbarEx)(ID hwnd, int type, PBin attr); // 置滑块条属性

	// 滚动条
	inline ID(__stdcall* CreateControl_ScrollbarEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, int pos,
		int minPos, int maxPos, int barSize, int buttonStep, int clickStep, int wheelStep,
		Bool dragTrace, int style, PBin extraElement, PBin layout
		); // 创建滚动条
	inline PBin(__stdcall* GetAttribute_ScrollbarEx)(ID hwnd, int type); // 取滚动条属性
	inline void(__stdcall* SetAttribute_ScrollbarEx)(ID hwnd, int type, PBin attr); // 置滚动条属性

	// 组合框
	inline ID(__stdcall* CreateControl_ComboboxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, PBin content,
		int align, int inputMode, int maxLen, PBin pwdSub, ARGB cursorColor, PBin font,
		ARGB fontColor, ARGB selectFontColor, ARGB selectBackColor, int leftReservation,
		int rightReservation, int menuItemWidth, int menuItemHeight, PBin menuFont,
		ARGB menuFontColor, ARGB menuDisabledFontColor, int menuTransparency,
		int menuLanguage, int listWidth, int listHeight, int currentItem,
		int iconWidth, int iconHeight, PBin listFont, Bool alternateColor,
		int scrollBarMode, int listTransparency, PBin data, PBin extraElement, PBin layout
		); // 创建组合框
	inline PBin(__stdcall* GetAttribute_ComboboxEx)(ID hwnd, int type); // 取组合框属性
	inline void(__stdcall* SetAttribute_ComboboxEx)(ID hwnd, int type, PBin attr); // 置组合框属性
	inline Bool(__stdcall* IsPopUp_DownlistEx_ComboboxEx)(ID hwnd); // 组合框列表是否弹出
	inline void(__stdcall* PopUp_DownlistEx_ComboboxEx)(ID hwnd); // 组合框弹出列表
	inline void(__stdcall* Close_DownlistEx_ComboboxEx)(ID hwnd); // 组合框关闭列表
	inline int(__stdcall* InsertItem_DownlistEx_ComboboxEx)(ID hwnd, int index, int num,
		int data, PICO icon, PBin title, ARGB fontColor, int height); // 组合框插入项目
	inline void(__stdcall* DeleteItem_DownlistEx_ComboboxEx)(ID hwnd, int index, int num); // 组合框删除项目
	inline int(__stdcall* GetItemCount_DownlistEx_ComboboxEx)(ID hwnd); // 组合框取项目数
	inline PBin(__stdcall* GetItemTitle_DownlistEx_ComboboxEx)(ID hwnd, int index); // 组合框取项目标题
	inline void(__stdcall* SetItemTitle_DownlistEx_ComboboxEx)(ID hwnd, int index, PBin title); // 组合框置项目标题
	inline PICO(__stdcall* GetItemIco_DownlistEx_ComboboxEx)(ID hwnd, int index); // 组合框取项目图标
	inline void(__stdcall* SetItemIco_DownlistEx_ComboboxEx)(ID hwnd, int index, PICO icon); // 组合框置项目图标
	inline ARGB(__stdcall* GetItemFontColor_DownlistEx_ComboboxEx)(ID hwnd, int index); // 组合框取项目字体色
	inline void(__stdcall* SetItemFontColor_DownlistEx_ComboboxEx)(ID hwnd, int index, ARGB color); // 组合框置项目字体色
	inline int(__stdcall* GetItemSize_DownlistEx_ComboboxEx)(ID hwnd, int index); // 组合框取项目高度
	inline void(__stdcall* SetItemSize_DownlistEx_ComboboxEx)(ID hwnd, int index, int height); // 组合框置项目高度
	inline int(__stdcall* GetItemData_DownlistEx_ComboboxEx)(ID hwnd, int index); // 组合框取项目附加数值
	inline void(__stdcall* SetItemData_DownlistEx_ComboboxEx)(ID hwnd, int index, int data); // 组合框置项目附加数值

	// 图标按钮
	inline ID(__stdcall* CreateControl_SuperbuttonEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, Bool selected,
		PBin icon, int iconWidth, int iconHeight, Bool iconUp, PBin title, PBin font,
		ARGB fontColor, int animation, PBin extraElement, PBin layout
		); // 创建图标按钮
	inline PBin(__stdcall* GetAttribute_SuperbuttonEx)(ID hwnd, int type); // 取图标按钮属性
	inline void(__stdcall* SetAttribute_SuperbuttonEx)(ID hwnd, int type, PBin attr); // 置图标按钮属性

	// 列表框
	inline ID(__stdcall* CreateControl_ListboxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, int currentItem,
		int	iconWidth, int iconHeight, PBin font, Bool alternateColor, int scrollBarMode,
		PBin items, PBin extraElement, PBin layout
		); // 创建列表框
	inline PBin(__stdcall* GetAttribute_ListboxEx)(ID hwnd, int type); // 取列表框属性
	inline void(__stdcall* SetAttribute_ListboxEx)(ID hwnd, int type, PBin attr); // 置列表框属性
	inline int(__stdcall* InsertItem_ListboxEx)(ID hwnd, int index, int num, int data,
		PICO icon, PBin title, ARGB fontColor, int height); // 列表框插入项目
	inline void(__stdcall* DeleteItem_ListboxEx)(ID hwnd, int index, int num); // 列表框删除项目
	inline int(__stdcall* GetItemCount_ListboxEx)(ID hwnd); // 列表框取项目数
	inline PBin(__stdcall* GetItemTitle_ListboxEx)(ID hwnd, int index); // 列表框取项目标题
	inline void(__stdcall* SetItemTitle_ListboxEx)(ID hwnd, int index, PBin title); // 列表框置项目标题
	inline PICO(__stdcall* GetItemIco_ListboxEx)(ID hwnd, int index); // 列表框取项目图标
	inline void(__stdcall* SetItemIco_ListboxEx)(ID hwnd, int index, PICO icon); // 列表框置项目图标
	inline int(__stdcall* GetItemData_ListboxEx)(ID hwnd, int index); // 列表框取项目附加数值
	inline void(__stdcall* SetItemData_ListboxEx)(ID hwnd, int index, int data); // 列表框置项目附加数值
	inline ARGB(__stdcall* GetItemFontColor_ListboxEx)(ID hwnd, int index); // 列表框取项目字体色
	inline void(__stdcall* SetItemFontColor_ListboxEx)(ID hwnd, int index, ARGB color); // 列表框置项目字体色
	inline int(__stdcall* GetItemSize_ListboxEx)(ID hwnd, int index); // 列表框取项目高度
	inline void(__stdcall* SetItemSize_ListboxEx)(ID hwnd, int index, int size); // 列表框置项目高度

	// 图标列表框
	inline ID(__stdcall* CreateControl_IcoListboxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, int currentItem,
		int itemWidth, int itemHeight, int hSpace, int vSpace, int iconWidth, int iconHeight,
		PBin font, int pageLayout, Bool iconUp, int scrollBarMode, PBin items, PBin extraElement, PBin layout
		); // 创建图标列表框
	inline PBin(__stdcall* GetAttribute_IcoListboxEx)(ID hwnd, int type); // 取图标列表框属性
	inline void(__stdcall* SetAttribute_IcoListboxEx)(ID hwnd, int type, PBin attr); // 置图标列表框属性
	inline int(__stdcall* InsertItem_IcoListboxEx)(ID hwnd, int index, int num, int data,
		PICO icon, PBin title, ARGB fontColor); // 图标列表框插入项目
	inline void(__stdcall* DeleteItem_IcoListboxEx)(ID hwnd, int index, int num); // 图标列表框删除项目
	inline int(__stdcall* GetItemCount_IcoListboxEx)(ID hwnd); // 图标列表框取项目数
	inline PBin(__stdcall* GetItemTitle_IcoListboxEx)(ID hwnd, int index); // 图标列表框取项目标题
	inline void(__stdcall* SetItemTitle_IcoListboxEx)(ID hwnd, int index, PBin title); // 图标列表框置项目标题
	inline PICO(__stdcall* GetItemIco_IcoListboxEx)(ID hwnd, int index); // 图标列表框取项目图标
	inline void(__stdcall* SetItemIco_IcoListboxEx)(ID hwnd, int index, PICO icon); // 图标列表框置项目图标
	inline int(__stdcall* GetItemData_IcoListboxEx)(ID hwnd, int index); // 图标列表框取项目附加数值
	inline void(__stdcall* SetItemData_IcoListboxEx)(ID hwnd, int index, int data); // 图标列表框置项目附加数值
	inline ARGB(__stdcall* GetItemFontColor_IcoListboxEx)(ID hwnd, int index); // 图标列表框取项目字体色
	inline void(__stdcall* SetItemFontColor_IcoListboxEx)(ID hwnd, int index, ARGB color); // 图标列表框置项目字体色

	// 超级列表框
	inline ID(__stdcall* CreateControl_SuperListboxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, int currentItem,
		int	headHeight, int headMode, Bool alternateColor, Bool eventFilter,
		int lineMode, int scrollBarMode, PBin items, PBin extraElement, PBin layout
		); // 创建超级列表框
	inline PBin(__stdcall* GetAttribute_SuperListboxEx)(ID hwnd, int type); // 取超级列表框属性
	inline void(__stdcall* SetAttribute_SuperListboxEx)(ID hwnd, int type, PBin attr); // 置超级列表框属性
	inline int(__stdcall* InsertColumn_SuperListboxEx)(
		ID hwnd, int index, int num, PBin icon, PBin title, ARGB fontColor,
		int width, int minWidth, int maxWidth, PBin font, int iconWidth, int iconHeight,
		int align, PBin itemFont, int itemIconWidth, int itemIconHeight, int itemAlign
		); // 超级列表框插入列
	inline void(__stdcall* DeleteColumn_SuperListboxEx)(ID hwnd, int index, int num); // 超级列表框删除列
	inline int(__stdcall* GetColumnCount_SuperListboxEx)(ID hwnd); // 超级列表框取列数量
	inline int(__stdcall* InsertItem_SuperListboxEx)(ID hwnd, int index, int num, int data, int size); // 超级列表框插入项目
	inline void(__stdcall* DeleteItem_SuperListboxEx)(ID hwnd, int index, int num); // 超级列表框删除项目
	inline int(__stdcall* GetItemCount_SuperListboxEx)(ID hwnd); // 超级列表框取项目数量
	inline PBin(__stdcall* GetItemTitle_SuperListboxEx)(ID hwnd, int index, int col); // 超级列表框取项目标题
	inline void(__stdcall* SetItemTitle_SuperListboxEx)(ID hwnd, int index, int col, PBin title); // 超级列表框置项目标题
	inline PICO(__stdcall* GetItemIco_SuperListboxEx)(ID hwnd, int index, int col); // 超级列表框取项目图标
	inline void(__stdcall* SetItemIco_SuperListboxEx)(ID hwnd, int index, int col, PICO icon); // 超级列表框置项目图标
	inline int(__stdcall* GetItemData_SuperListboxEx)(ID hwnd, int index); // 超级列表框取项目附加数值
	inline void(__stdcall* SetItemData_SuperListboxEx)(ID hwnd, int index, int data); // 超级列表框置项目附加数值
	inline ARGB(__stdcall* GetItemFontColor_SuperListboxEx)(ID hwnd, int index, int col); // 超级列表框取项目字体色
	inline void(__stdcall* SetItemFontColor_SuperListboxEx)(ID hwnd, int index, int col, ARGB color); // 超级列表框置项目字体色
	inline int(__stdcall* GetItemSize_SuperListboxEx)(ID hwnd, int index); // 超级列表框取项目高度
	inline void(__stdcall* SetItemSize_SuperListboxEx)(ID hwnd, int index, int size); // 超级列表框置项目高度

	// 选择夹
	inline ID(__stdcall* CreateControl_SelectthefolderEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, int currentItem,
		int ItemHeight, int direction, int space, int style, int unused,
		int iconWidth, int iconHeight, PBin font, PBin data, PBin extraElement, PBin layout
		); // 创建选择夹
	inline PBin(__stdcall* GetAttribute_SelectthefolderEx)(ID hwnd, int type); // 取选择夹属性
	inline void(__stdcall* SetAttribute_SelectthefolderEx)(ID hwnd, int type, PBin attr); // 置选择夹属性
	inline int(__stdcall* InsertTab_SelectthefolderEx)(ID hwnd, int index, int data,
		PICO icon, PBin title, ARGB fontColor, int width); // 插入子夹
	inline void(__stdcall* DeleteTab_SelectthefolderEx)(ID hwnd, int index); // 删除子夹
	inline int(__stdcall* GetTabCount_SelectthefolderEx)(ID hwnd); // 取子夹数
	inline PBin(__stdcall* GetTabTitle_SelectthefolderEx)(ID hwnd, int index); // 取子夹标题
	inline void(__stdcall* SetTabTitle_SelectthefolderEx)(ID hwnd, int index, PBin title); // 置子夹标题
	inline PICO(__stdcall* GetTabIco_SelectthefolderEx)(ID hwnd, int index); // 取子夹图标
	inline void(__stdcall* SetTabIco_SelectthefolderEx)(ID hwnd, int index, PICO icon); // 置子夹图标
	inline int(__stdcall* GetTabData_SelectthefolderEx)(ID hwnd, int index); // 取子夹附加数值
	inline void(__stdcall* SetTabData_SelectthefolderEx)(ID hwnd, int index, int data); // 置子夹附加数值
	inline ARGB(__stdcall* GetTabFontColor_SelectthefolderEx)(ID hwnd, int index); // 取子夹字体色
	inline void(__stdcall* SetTabFontColor_SelectthefolderEx)(ID hwnd, int index, ARGB color); // 置子夹字体色
	inline int(__stdcall* GetTabSize_SelectthefolderEx)(ID hwnd, int index); // 取子夹宽度
	inline void(__stdcall* SetTabSize_SelectthefolderEx)(ID hwnd, int index, int width); // 置子夹宽度
	inline Bool(__stdcall* InsertControl_SelectthefolderEx)(ID hwnd, int index, ID control, int left, int top); // 添加组件

	// 日历框
	inline ID(__stdcall* CreateControl_CalendarBoxEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin,
		PBin minDate, PBin maxDate, PBin selectDate, PBin titleFont, PBin weekFont,
		PBin dayFont, PBin timeFont, ARGB titleColor, ARGB weekColor, ARGB weekendColor,
		ARGB dayColor, ARGB weekendDayColor, ARGB otherMonthColor, ARGB timeColor,
		Bool onlyThisMonth, int timeMode, int titleHeight, int weekHeight,
		int timeRegulatorHeight, int partnerHeight, int language, PBin data, PBin extraElement, PBin layout
		); // 创建日历
	inline PBin(__stdcall* GetAttribute_CalendarBoxEx)(ID hwnd, int type); // 取日历属性
	inline void(__stdcall* SetAttribute_CalendarBoxEx)(ID hwnd, int type, PBin attr); // 置日历属性

	// 选色板
	inline ID(__stdcall* CreateControl_ColorPickEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency,
		int pierced, int focusWeight, PBin cursor, Memory sign, PBin skin, PBin font,
		ARGB fontColor, ARGB currentColor, Bool dragTrace, int useRGB, PBin quicks,
		int style, int regulatorHeight, int quickSize, int partnerHeight, PBin extraElement, PBin layout
		); // 创建选色板
	inline PBin(__stdcall* GetAttribute_ColorPickEx)(ID hwnd, int type); // 取选色板属性
	inline void(__stdcall* SetAttribute_ColorPickEx)(ID hwnd, int type, PBin attr); // 置选色板属性

	// 画板
	inline ID(__stdcall* CreateControl_DrawPanelEx)(
		ID hBase, HWND hParent, int x, int y, int width, int height, Call callback,
		int* initAttr, Bool visual, Bool disabled, int transparency, int pierced, int focusWeight,
		PBin cursor, Memory sign, ARGB backColor, ARGB borderColor, PBin extraElement, PBin layout
		); // 创建画板
	inline PBin(__stdcall* GetAttribute_DrawPanelEx)(ID hwnd, int type); // 取画板属性
	inline void(__stdcall* SetAttribute_DrawPanelEx)(ID hwnd, int type, PBin attr); // 置画板属性
	inline void(__stdcall* DrawImage_DrawPanelEx)(ID hwnd, PICO icon, float left, float top, float width, float height,
		float srcLeft, float srcTop, float srcWidth, float srcHeight, int transparency); // 画图片
	inline void(__stdcall* DrawString_DrawPanelEx)(ID hwnd, PBin content, float left, float top, float width, float height,
		PBin font, int align, int type, int effect, ARGB color1, ARGB color2); // 画文本
	inline void(__stdcall* DrawLine_DrawPanelEx)(ID hwnd, float x1, float y1, float x2, float y2,
		int type, int effect, ARGB color1, ARGB color2); // 画直线
	inline void(__stdcall* DrawArc_DrawPanelEx)(ID hwnd, float x1, float y1, float x2, float y2,
		float start, float end, int type, int effect, ARGB color1, ARGB color2); // 画弧线
	inline void(__stdcall* DrawRect_DrawPanelEx)(ID hwnd, float x1, float y1, float x2, float y2,
		int type, int effect, ARGB color1, ARGB color2); // 画矩形
	inline void(__stdcall* DrawEllipse_DrawPanelEx)(ID hwnd, float x1, float y1, float x2, float y2,
		float d, int type, int effect, ARGB color1, ARGB color2); // 画圆
	inline void(__stdcall* DrawPie_DrawPanelEx)(ID hwnd, float x1, float y1, float x2, float y2,
		float start, float end, int type, int effect, ARGB color1, ARGB color2); // 画饼
	inline void(__stdcall* Clear_DrawPanelEx)(ID hwnd, ARGB color, float x1, float y1, float x2, float y2, Bool mode); // 清除画板
	inline void(__stdcall* Update_DrawPanelEx)(ID hwnd, float x1, float y1, float x2, float y2, Bool mode); // 更新画板
	inline void(__stdcall* SetGraphicsquality_DrawPanelEx)(ID hwnd, int smooth, int algorithm, int offset); // 置绘画算法

	// 自绘
	inline ID(__stdcall* CreateControl_ExtendEx)(ID hBase, HWND hParent, int x, int y, int width, int height,
		Call callback, int* initAttr, Bool visual, Bool disabled, int transparency, int pierced, int focusWeight,
		PBin cursor, Memory sign, PBin extraProperty, PBin extraElement, PBin layout); // 创建自绘

	// 菜单
	inline ID(__stdcall* Create_MenuEx)(int iconWidth, int iconHeight, PBin skin, PBin font,
		PBin cursor, int transparency, Call callback, Memory sign); // 创建菜单
	inline void(__stdcall* SetAttribute_MenuEx)(ID hwnd, int id, int iconWidth, int iconHeight,
		PBin skin, PBin font, PBin cursor, int transparency, Call callback, Memory sign); // 置菜单属性
	inline PBin(__stdcall* GetAttribute_MenuEx)(ID hwnd, int id); // 取菜单属性
	inline void(__stdcall* Destroy_MenuEx)(ID hwnd); // 销毁菜单
	inline Bool(__stdcall* IsPopUp_MenuEx)(ID hwnd, ID item); // 菜单是否弹出
	inline void(__stdcall* PopUp_MenuEx)(ID hwnd, ID item, int left, int top,
		ID hParent, Bool mode, int other); // 弹出菜单
	inline void(__stdcall* Close_MenuEx)(ID hwnd, ID item, Bool mode); // 关闭菜单
	inline ID(__stdcall* InsertItem_MenuEx)(ID hwnd, ID item, int index,
		int data, PICO icon, PBin title, ARGB fontColor, ARGB disabledFontColor,
		int width, int height, int type, Bool disabled); // 菜单插入项目
	inline void(__stdcall* DeleteItem_MenuEx)(ID hwnd, ID item); // 菜单删除项目
	inline int(__stdcall* GetItemCount_MenuEx)(ID hwnd); // 取菜单项数
	inline PICO(__stdcall* GetItemIco_MenuEx)(ID hwnd, ID item); // 取菜单项图标
	inline void(__stdcall* SetItemIco_MenuEx)(ID hwnd, ID item, PICO icon); // 置菜单项图标
	inline PBin(__stdcall* GetItemTitle_MenuEx)(ID hwnd, ID item); // 取菜单项标题
	inline void(__stdcall* SetItemTitle_MenuEx)(ID hwnd, ID item, PBin title); // 置菜单项标题
	inline ARGB(__stdcall* GetItemFontColor_MenuEx)(ID hwnd, ID item); // 取菜单项字体色
	inline void(__stdcall* SetItemFontColor_MenuEx)(ID hwnd, ID item, ARGB color); // 置菜单项字体色
	inline ARGB(__stdcall* GetItemDisabledFontColor_MenuEx)(ID hwnd, ID item); // 取菜单项禁止字体色
	inline void(__stdcall* SetItemDisabledFontColor_MenuEx)(ID hwnd, ID item, ARGB color); // 置菜单项禁止字体色
	inline int(__stdcall* GetItemHeight_MenuEx)(ID hwnd, ID item); // 取菜单项高度
	inline void(__stdcall* SetItemHeight_MenuEx)(ID hwnd, ID item, int height); // 置菜单项高度
	inline Bool(__stdcall* GetItemDisabled_MenuEx)(ID hwnd, ID item); // 取菜单项禁止
	inline void(__stdcall* SetItemDisabled_MenuEx)(ID hwnd, ID item, Bool disabled); // 置菜单项禁止
	inline int(__stdcall* GetItemData_MenuEx)(ID hwnd, ID item); // 取菜单项附加数值
	inline void(__stdcall* SetItemData_MenuEx)(ID hwnd, ID item, int data); // 置菜单项附加数值
	inline int(__stdcall* GetItemType_MenuEx)(ID hwnd, ID item); // 取菜单项类型
	inline int(__stdcall* GetSubItemCount_MenuEx)(ID hwnd, ID item); // 取子菜单数
	inline ID(__stdcall* GetSubItem_MenuEx)(ID hwnd, ID item, int index); // 取子菜单

	// 对话框
	inline int(__stdcall* MsgBox_Ex)(PBin ico, PBin title, PBin image, PBin content, PBin buttons,
		int defaultButton, ID hParent, int style, PBin skin, ConstMemory callback, int arg); // 信息框
	inline int(__stdcall* InputBox_Ex)(PBin ico, PBin title, PBin image, PBin content, PBin buttons,
		int defaultButton, PBin hInt, int inputMode, PBin pwdSub, int maxLen, Bool multiLine,
		int result, ID hParent, int style, PBin skin, ConstMemory callback, int arg); // 输入框
	inline int(__stdcall* PopUpTipBoxEx)(PICO icon, PBin content, int mode, int x, int y,
		int width, int height, int time, int angle, ARGB backColor, ARGB borderColor,
		int borderWidth, PBin font, ARGB fontColor, int align, int transparency); // 弹出提示框
	inline void(__stdcall* CloseTipBoxEx)(); // 关闭提示框
	inline PBin(__stdcall* PopUpItemInputEx)(ID id, int row, int col, int unused, int mode,
		PBin content, int inputMode, int maxLen, PBin pwdSub, int align, Bool multiLine, Bool autoLine,
		PBin skin, PBin cursor, PBin font, ARGB fontColor, ARGB selectFontColor, ARGB selectColor,
		ARGB cursorColor, int scrollBarMode, int menuWidth, int menuHeight, PBin menuFont, ARGB menuFontColor,
		ARGB menuDisabledFontColor, int menuTransparency, int menuLanguage); // 项目标题编辑框

	// 缓动特效
	inline int(__stdcall* CreateSlowMotionTaskEx)(int num, int mode, int start, int end,
		int delay, int step, Call callback, int arg, Bool wait, Bool autoDestroy); // 创建缓动任务
	inline void(__stdcall* SetSlowMotionTaskConfigEx)(int object, int id, int mode, int start, int end); // 置缓动任务配置
}