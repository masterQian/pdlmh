#pragma once

struct Res final {
	struct {
		String Main, Toast, Settings;
		String MenuGroup, MenuItem, MenuTree, MenuPlugin, MenuTray, MenuTreeDisk, MenuFile;
		String pageProgram, pageSystem, pageTree, pagePlugin, pageFile;
	}Layout; // 布局
	struct {
		String About, Update, Version, PreviewMap, TypeMap;
		ByteArray DefaultSettings;
	}Data; // 数据
	struct {
		Bin Icon, Search, Settings, Close, Info;
		Bin Drive[7];
	}Image; // 图片
	struct {
		struct {
			ICO Start, Tool, Folder, Plugin, File;
		}Tab;
		struct {
			ICO Return, NewFolder, Desktop;
		}Tree;
		ICO Settings;
		struct {
			ICO Off, On;
		}Choice;
		ICO Default[15];
		struct {
			ICO Admin, Delete, Edit, Folder, Path, Exit;
			ICO Able, Disable, Move, Copy, Cut, Paste;
			ICO Property, Left, Right, Rename, Preview;
			ICO Save;
		}Menu;
		ICO Drive[7];
	}Ico; // 图标
	struct {
		Bin Edit;
		Bin Group;
		Bin IconButton, IconButton2;
		Bin Picture;
		Bin SuperList, SuperList2;
		Bin Menu;
		Bin Button;
		Bin Choice;
		Bin Slider;
		Bin ColorPick;
		Bin IconList, IconList2;
		Bin Progress;
	}Skin; // 皮肤
	std::vector<SysTool> SystemTools; // 系统工具
	struct {
		struct {
			Bin S12, S14, S16;
			Bin SB14, SB16;
			Bin SL14, SL16;
		}MSBlack;
	}Font; // 字体
};