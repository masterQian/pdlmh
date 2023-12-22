#pragma once

class Con final {
	Con() = delete;
public:
#define PN(name, value) static constexpr auto PluginNotify_##name = value
	PN(LastWindow, 0); PN(LastSettings, 1);
#undef PN

#define MACRO_Path_Config L"config"
#define MACRO_Path_Plugin L"plugins"
#define MACRO_Path_Config_Settings MACRO_Path_Config L"\\settings.ini"
#define MACRO_Path_Config_Data MACRO_Path_Config L"\\data.ini"
	static constexpr const wchar_t* Path_Config = MACRO_Path_Config;
	static constexpr const wchar_t* Path_Plugin = MACRO_Path_Plugin;
	static constexpr const wchar_t* Path_Config_Settings = MACRO_Path_Config_Settings;
	static constexpr const wchar_t* Path_Config_Data = MACRO_Path_Config_Data;
#undef MACRO_Path_Config
#undef MACRO_Path_Plugin
#undef MACRO_Path_Config_Settings
#undef MACRO_Path_Config_Data
	static constexpr const wchar_t* Path_Plugin_Ini = L"\\info.ini";

	static constexpr const wchar_t* AddSign = L"＋";
};

class LS final {
	LS() = delete;
public:
#define LS(name, value) static constexpr auto name = value
	LS(ListDefaultHeight, 35);
	LS(ListDefaultWaveHeight, 38);

	LS(CSpace, L' ');
	LS(Separator, L'\\');
	LS(Split, L'|');
	LS(SSplit, L"|");
	LS(CTrue, L'1');
	LS(CFalse, L'0');
	LS(True, L"1");
	LS(False, L"0");
	LS(Space, L" ");
	LS(SplitTrue, L"|1|");
	LS(SplitFalse, L"|0|");

	LS(DefaultResourceType, L"R");

	LS(SoftwareName, L"pdlmh3");
	LS(SoftwareNameString, L"潘多拉魔盒3");
	LS(RegAutoStart, L"software\\microsoft\\windows\\CurrentVersion\\Run");

	LS(RenameGroup, L"重命名分组");
	LS(InputNewName, L"输入新名称");

	LS(IniSettings, L"Settings");
	LS(IniData, L"Data");
	LS(IniCount, L"Count");
	LS(IniAutoStart, L"AutoStart");
	LS(IniListWave, L"ListWave");
	LS(IniEffectSpeed, L"EffectSpeed");
	LS(IniBackGroundColor, L"BackGroundColor");
	LS(IniTreeFilter, L"FolderTreeFilter");
	LS(IniSearchEngine, L"SearchEngine");
	LS(IniGroundGlass, L"GroundGlass");

	LS(ButtonTitleOK, L"确定");
	LS(ButtonTitleCancel, L"取消");

	LS(FontMSBlack, L"微软雅黑");

	LS(ToolComputer, L"我的电脑");
	LS(ToolDocument, L"我的文档");
	LS(ToolRecycleBin, L"回收站");
	LS(ToolControl, L"控制面板");
	LS(ToolCmd, L"cmd");
	LS(ToolPowershell, L"powershell");
	LS(ToolTaskmgr, L"任务管理器");
	LS(ToolCalculator, L"计算器");
	LS(ToolNotepad, L"记事本");
	LS(ToolPrinter, L"打印机管理");
	LS(ToolRegedit, L"注册表");
	LS(ToolScanner, L"扫描仪");
	LS(ToolComputerManager, L"计算机管理");
	LS(ToolService, L"服务");
	LS(ToolSecpol, L"本地安全策略");
	LS(ToolGpedit, L"组策略");

	LS(PluginInfo, L"Plugin");
	LS(PluginInfoFile, L"file");
	LS(PluginInfoName, L"name");
	LS(PluginInfoIcon, L"icon");
	LS(PluginInfoVersion, L"version");
	LS(PluginInfoAuthor, L"author");
	LS(PluginInfoComment, L"comment");
	LS(PluginInfoIsUse, L"isUse");
	LS(PluginInfoSettings, L"settings");
	LS(PluginFuncInit, "init");
	LS(PluginFuncDestroy, "destroy");
	LS(PluginFuncRun, "run");
	LS(PluginFuncSettings, "settings");

	LS(Tip_NoThisPath, L"不存在此路径");
	LS(Tip_InputFolderName, L"输入新文件夹名称");
	LS(Tip_InputName, L"输入重命名新名称");
	LS(Tip_FolderExists, L"此目录已存在");
	LS(Tip_PluginError, L"插件执行发生内部错误");
	LS(Tip_PluginNotUse, L"该插件未启用");
	LS(Tip_CopyPathOK, L"复制完整路径到剪贴板成功");
	LS(Tip_EmptyName, L"名称不能为空");
	LS(Tip_OverwriteExists, L"已存在相同文件或目录是否覆盖");
	LS(Tip_FileError, L"文件处理发生异常");
	LS(Tip_NoCopyTarget, L"当前无复制目标");
	LS(Tip_ChooseFolder, L"粘贴目标应是一个目录");
	LS(Tip_ConfirmDelete, L"你真的要删除: ");
	LS(Tip_PluginAlreadyUse, L"插件已处于启用状态");
	LS(Tip_PluginUse, L"插件已启用");
	LS(Tip_PluginAlreadyNoUse, L"插件已处于禁用状态");
	LS(Tip_PluginNoUse, L"插件已禁用");
	LS(Tip_MostSingleFile, L"最多支持同时添加一个文件");
	LS(Tip_FileCache, 
		L"文件池中的文件独立于外界,即使删除源头文件仍然存在,"
		L"菜单操作都是针对池内文件处理,拖动文件到池内以添加,"
		L"池内允许进行模糊搜索快速找到你想要的文件.");

#undef LS
};