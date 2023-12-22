#pragma once

// 配置
struct ConfigEntry final {
	bool AutoStart{}; // 开机自启
	int EffectSpeed{}; // 特效速率
	int BackGroundColor{}; // 背景颜色
	bool ListWave{}; // 悬浮动效
	int FolderTreeFilter{}; // 目录树过滤器
	int SearchEngine{}; // 搜索引擎
	bool GroundGlass{}; // 毛玻璃特效
};

// 文件实体
struct FileEntry final {
	String name; // 名称
	String path; // 路径
	bool admin = false; // 以管理员运行
	String arg; // 运行参数
	// 0exe 1文件 2文件夹 3压缩文件 4txt
	// 5word 6excel 7ppt 8pdf 9picture
	// 10music 11video 12webpage 13xml 14apk
	int type = 0; // 类型
	ICO ico; // 图标
};

// 分组实体
struct GroupEntry final {
	String name; // 分组名
	std::vector<FileEntry> files; // 文件
};

// 数据实体
using DataEntry = std::vector<GroupEntry>;

// 系统工具结构
struct SysTool final {
	ICO ico;
	String name;
	String path;
	String arg;
};

// 插件回调
using PluginCall = bool(__stdcall*)(int, int, int, int);

// 插件结构
struct Plugin final {
	String path, file, name, version, author, comment;
	ICO ico;
	bool isUse = false;
	HMODULE hPlugin = nullptr;
	PluginCall hRun = nullptr, hDestroy = nullptr, hSettings = nullptr;
};

// 系统调用
using SystemCall = std::unordered_map<String, ConstMemory>;