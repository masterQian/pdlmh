#include "environmentDlg.h"

void UpdatePage() {
    static volatile bool mutex_response = true;
    if (mutex_response) {
        mutex_response = false;
        env.list.LockUpdate();
        env.list.ClearItem();
        int pos;
        switch (env.cur) {
        case 0: {
            for (auto& [key, value] : env.data1) {
                pos = env.list.InsertItem();
                env.list.ItemTitle(pos, 0, key);
                env.list.ItemTitle(pos, 1, L" -> ");
                env.list.ItemTitle(pos, 2, value);
                env.list.ItemIcon(pos, 3, env.more);
            }
            break;
        }
        case 1: {
            for (auto& [key, value] : env.data2) {
                pos = env.list.InsertItem();
                env.list.ItemTitle(pos, 0, key);
                env.list.ItemTitle(pos, 1, L" -> ");
                env.list.ItemTitle(pos, 2, value);
                env.list.ItemIcon(pos, 3, env.more);
            }
            break;
        }
        case 2: {
            ConstStr p1 = env.data1[L"Path"].data(), p2 = p1;
            int i = 0;
            for (; *p1 && *p2;) {
                for (p2 = p1; *p2 && *p2 != L';';) ++p2;
                pos = env.list.InsertItem();
                env.list.ItemTitle(pos, 0, ToString(++i));
                env.list.ItemTitle(pos, 1, L" -> ");
                env.list.ItemTitle(pos, 2, String(p1, p2));
                env.list.ItemIcon(pos, 3, env.more);
                p1 = p2 + 1;
            }
            break;
        }
        }
        env.list.ItemFontColor(-1, -1, Color::White);
        env.list.UnlockUpdate();
        mutex_response = true;
    }
}

void AddNewItem(int page, ConstString key) {
    env.list.LockUpdate();
    if (page == 0) {
        if (auto iter = env.data1.find(key); iter == env.data1.cend()) {
            env.data1[key] = {};
            env.reg1.SetStringValue(key, {});
            auto pos = env.list.InsertItem();
            env.list.ItemTitle(pos, 0, key);
            env.list.ItemTitle(pos, 1, L" -> ");
            env.list.ItemTitle(pos, 2, {});
            env.list.ItemIcon(pos, 3, env.more);
            env.list.ItemFontColor(pos, -1, Color::White);
        }
        else res.Function.Toast(2000, L"该键值已经存在");
    }
    else if (page == 1) {
        if (auto iter = env.data2.find(key); iter == env.data2.cend()) {
            env.data2[key] = {};
            env.reg2.SetStringValue(key, {});
            auto pos = env.list.InsertItem();
            env.list.ItemTitle(pos, 0, key);
            env.list.ItemTitle(pos, 1, L" -> ");
            env.list.ItemTitle(pos, 2, {});
            env.list.ItemIcon(pos, 3, env.more);
            env.list.ItemFontColor(pos, -1, Color::White);
        }
        else res.Function.Toast(2000, L"该键值已经存在");
    }
    else if (page == 2) {
        auto& path = env.data1[L"Path"];
        path += key + L";";
        env.reg1.SetStringValue(L"Path", path);
        auto pos = env.list.InsertItem();
        env.list.ItemTitle(pos, 0, ToString(env.list.ItemCount()));
        env.list.ItemTitle(pos, 1, L" -> ");
        env.list.ItemTitle(pos, 2, key);
        env.list.ItemIcon(pos, 3, env.more);
        env.list.ItemFontColor(pos, -1, Color::White);
    }
    env.list.UnlockUpdate();
}

void EditItem(int page, int index, ConstString value) {
    env.list.LockUpdate();
    if (page == 0) {
        auto key = env.list.ItemTitle(index, 0);
        env.data1[key] = value;
        env.reg1.SetStringValue(key, value);
        env.list.ItemTitle(index, 2, value);
    }
    else if (page == 1) {
        auto key = env.list.ItemTitle(index, 0);
        env.data2[key] = value;
        env.reg2.SetStringValue(key, value);
        env.list.ItemTitle(index, 2, value);
    }
    else if (page == 2) {
        auto oldValue = env.list.ItemTitle(index, 2) + L";";
        auto& path = env.data1[L"Path"];
        auto i = path.find(oldValue);
        path = path.substr(0, i) + value + L";" + path.substr(i + oldValue.size());
        env.reg1.SetStringValue(L"Path", path);
        UpdatePage();
    }
    env.list.UnlockUpdate();
}

void Emptyitem(int page, int index) {
    env.list.LockUpdate();
    if (page == 0) {
        auto key = env.list.ItemTitle(index, 0);
        env.data1[key] = {};
        env.reg1.SetStringValue(key, {});
        env.list.ItemTitle(index, 2, {});
    }
    else if (page == 1) {
        auto key = env.list.ItemTitle(index, 0);
        env.data2[key] = {};
        env.reg2.SetStringValue(key, {});
        env.list.ItemTitle(index, 2, {});
    }
    else if (page == 2) {
        auto key = env.list.ItemTitle(index, 2) + L";";
        auto& path = env.data1[L"Path"];
        path.erase(path.find(key), key.size());
        env.reg1.SetStringValue(L"Path", path);
        UpdatePage();
    }
    env.list.UnlockUpdate();
}

void DeleteItem(int page, int index) {
    env.list.LockUpdate();
    if (page == 0) {
        auto key = env.list.ItemTitle(index, 0);
        env.data1.erase(key);
        env.reg1.DeleteKey(key);
        env.list.DeleteItem(index);
    }
    else if (page == 1) {
        auto key = env.list.ItemTitle(index, 0);
        env.data2.erase(key);
        env.reg2.DeleteKey(key);
        env.list.DeleteItem(index);
    }
    else if (page == 2) {
        auto key = env.list.ItemTitle(index, 2) + L";";
        auto& path = env.data1[L"Path"];
        path.erase(path.find(key), key.size());
        env.reg1.SetStringValue(L"Path", path);
        UpdatePage();
    }
    env.list.UnlockUpdate();
}

Result __stdcall ListCallBack(ID id, Event msg, Arg row, Arg col, Arg, Arg source) {
	if (source == Attrs::ListEventSource::Item) {
        switch (msg) {
        case Events::SuperList::ItemLCLick: {
            if (col == 3) {
                env.Visual(false);
                auto str = FileBox::OpenFolder(L"选择添加环境变量的目录");
                env.Visual(true);
                if (!str.empty()) EditItem(env.cur, env.list.CurrentItem(), str);
            }
            break;
        }
        case Events::SuperList::ItemRCLick: {
            if (col != 3) {
                env.list.CurrentItem(row);
                env.menu.Open();
            }
            break;
        }
        }
	}
	return 0;
}

Result __stdcall ButtonCallBack(ID id, Event msg, Arg index, Arg, Arg, Arg) {
    if (msg == Events::IconList::ItemLCLick && env.cur != index) {
        static volatile bool mutex_response = true;
        if (mutex_response) {
            mutex_response = false;
            env.cur = index;
            UpdatePage();
            mutex_response = true;
        }
    }
    return 0;
}

void __stdcall MenuCallBack(Menu::Item item, Event msg, short tag) {
    if (msg == Events::Menu::ItemLCLick) {
        auto index = env.list.CurrentItem();
        switch (tag) {
        case 0: {
            env.Disabled(true);
            String str = InputBox::Start(L"添加新项", L"输入新项目的键名", { L"确定",L"取消" });
            env.Disabled(false);
            if (!str.empty()) AddNewItem(env.cur, str);
            break;
        }
        case 1: {
            ClipBoard::SetString(env.list.ItemTitle(index, 2));
            res.Function.Toast(2000, L"复制成功");
            break;
        }
        case 2: {
            auto oldValue = env.list.ItemTitle(index, 2);
            env.Disabled(true);
            String str = InputBox::Start(L"修改值", L"输入新键值", { L"确定",L"取消" }, {}, {}, {}, oldValue);
            env.Disabled(false);
            if (!str.empty()) EditItem(env.cur, index, str);
            break;
        }
        case 3: Emptyitem(env.cur, index); break;
        case 4: DeleteItem(env.cur, index); break;
        }
    }
}

Result __stdcall EnvCallBack(ID id, Event msg, Arg arg1, Arg arg2, Arg arg3, Arg arg4) {
	switch (msg) {
	case Events::Window::Create: {
		Layout::InflateWindow(env, res.Layout.environment, env.vds);
        Layout::InflateMenu(env.menu, res.Layout.menu, env.vds);
		env.reg1.Open(Reg::LocalMachine, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment");
		env.reg2.Open(Reg::CurrentUser, L"Environment");
		env.reg1.EnumKeyValue([](const std::wstring& key, const std::wstring& value) { env.data1[key] = value; });
		env.reg2.EnumKeyValue([](const std::wstring& key, const std::wstring& value) { env.data2[key] = value; });
		env.list = (SuperList)env(L"list");
		env.list.InsertColumn(-1, {}, Color::White, 220, Attrs::ItemAlign::Center, 0, 0, *res.Font.MSBlack.S16);
		env.list.InsertColumn(-1, {}, Color::White, 40, Attrs::ItemAlign::Center, 0, 0, *res.Font.MSBlack.S16);
		env.list.InsertColumn(-1, {}, Color::White, 500, Attrs::ItemAlign::Center, 0, 0, *res.Font.MSBlack.S16);
		env.list.InsertColumn(-1, {}, 0, 40, Attrs::ItemAlign::Center, 32, 20);
        env.more = ICO(res.more.content, res.more.length);
        env.cur = 0;
        UpdatePage();
		break;
	}
	case Events::Window::Destroy: {
		env.reg1.Close();
		env.reg2.Close();
		Reg::FlushEnvironment();
        env.more = {};
		env.isOpen = false;
		env.Reset();
		break;
	}
	}
	return 0;
}

void EnvDlg::Open() noexcept {
	env.vds = {
        { L"Value.GroundGlass", (Memory)res.GroundGlass },
		{ L"Position.Left", (Memory)((Screen::Width >> 1) - 400) },
		{ L"Position.Top", (Memory)(((Screen::Height - Screen::TaskBarHeight) >> 1) - 275) },
		{ L"Font.MSBlack.S16", *res.Font.MSBlack.S16 },
		{ L"Color.White", (Memory)Color::White },
		{ L"Color.Red", (Memory)Color::Red },
		{ L"Skin.Window", *res.Skin.Window },
		{ L"Skin.Menu", *res.Skin.Menu },
		{ L"Skin.SuperList2", *res.Skin.SuperList2 },
		{ L"Skin.IconList", *res.Skin.IconList },
		{ L"CallBack.List", &ListCallBack },
		{ L"CallBack.Menu", &MenuCallBack },
		{ L"CallBack.Button", &ButtonCallBack },
	};
	env.Start(&EnvCallBack, {}, true, false, true);
}