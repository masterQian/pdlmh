#pragma once

namespace winui {
	// 逻辑
	using Bool = int;
	// 属性
	using Attr = int;
	// 颜色
	using ARGB = int;
	// 事件
	using Event = int;
	// 参数
	using Arg = int;
	// 结果
	using Result = int;
	// 组件句柄
	using ID = int;

	// 字节流
	using Byte = unsigned char;
	using Bytes = unsigned char*;
	using ConstBytes = const unsigned char*;

	// 字符串
	using Str = wchar_t*;
	using ConstStr = const wchar_t*;

	// 内存
	using Memory = void*;
	using ConstMemory = const void*;

	// Exui内存块
	using PBin = void*;
	using ConstPBin = const void*;

	// Exui位图块
	using PICO = void*;
	using ConstPICO = const void*;

	// Exui结构体
	using Struct = void*;
	using ConstStruct = const void*;

	// 矩形
	struct Rectangle final { int left, top, width, height; };

	// 事件回调
	using Call = Result(__stdcall*)(ID, Event, Arg, Arg, Arg, Arg);

	// 任务回调
	using Task = Result(__stdcall*)(ID, int, ConstMemory, int, int);
}