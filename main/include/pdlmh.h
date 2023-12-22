#pragma once
#include <winui.h>
using namespace winui;
#include "def.h"
#include "con.h"
#include "res.h"
#include "var.h"
#include "main.h"
#include "toast.h"
#include "settings.h"

// 主函数
void WinUIMain() noexcept;
// 资源
inline Res* res;
// 全局变量
inline Var* var;
// 主窗口
inline MainWindow* mainWindow;