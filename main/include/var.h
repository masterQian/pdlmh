#pragma once

struct Var final {
	String AppData; // 缓存数据目录
	CLSID GUID_BMP{}; // BMP编码器
	CLSID GUID_JPG{}; // JPG编码器
	CLSID GUID_PNG{}; // PNG编码器
	Bin BackGroundImage; // 背景图片
	Bin NewSkinWindow; // 新窗口皮肤
	ConfigEntry Config; // 配置项
	DataEntry Data; // 数据项
	VDSwitcher vds; // V/D交换机
	std::unordered_map<String, int> TypeMap; // 文件类型图标映射
};