#pragma once

#define USE_CONTROL_PLUS 1 // 使用拓展控件

// win32 x86 编译
#if !defined(_WIN32)
#error please use win32 x86 mode
#endif

// C++
#if !defined(__cplusplus)
#error please use a C++ compiler
#endif

// C++概念支持(C++20以上版本)
#if !defined(__cpp_concepts)
#error please use a C++ compiler at least C++20 standard
#endif

// C++模块支持(C++20以上版本)
#if !defined(__cpp_modules)
#error please use a C++ compiler at least C++20 standard
#endif

#include "winui_def.h"
#include "winui_lib.h"
#include "winui_api.h"
#include "winui_attr.h"
#include "winui_event.h"
#include "winui_base.h"
#include "winui_main.h"
#include "winui_skin.h"
#include "winui_util.h"
#include "winui_control.h"
#include "winui_menu.h"
#include "winui_box.h"
#include "winui_view.h"
#if USE_CONTROL_PLUS
#include "winui_control_plus.h"
#endif
#include "winui_layout.h"
#include "winui_log.h"