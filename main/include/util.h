#pragma once
#include "pdlmh.h"

// HICON转PNG
ByteArray HICON_PNG(HICON hIcon) noexcept;
// 字符串转文件实体
void LoadFileEntry(ConstString str, FileEntry& entry) noexcept;
// 文件实体转字符串
String SaveFileEntry(const FileEntry& entry) noexcept;
// 取文件拓展类型
int GetFileExtraType(ConstString ext) noexcept;
// 取文件拓展类型图标
ICO GetFileExtraTypeIcon(ConstString path, int* rType = nullptr) noexcept;